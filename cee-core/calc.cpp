/*
cee - Commandline calculator for enginEErs
A small calculating tool with a commandline like interface.

Copyright (C) 2012 Andreas Hagmann <cee@hagmann.name>

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include "calc.h"
#include <QDebug>
#include "syntaxtree.h"
#include "calcexception.h"
#include "valuetable.h"
#include "commandnode.h"
#include <iostream>
#include "functionassignmentnode.h"
#include <QRegExp>
#include <cmath>

using namespace std;

Calc::Calc() : m_format(DEC), m_result(0), m_quit(false) {
	ValueTable::setConstant("pi", M_PI);
	ValueTable::setVariable("ans", 0);
}

void Calc::executeCommand(QString command) {
	if (command == "bin" || command == "0b") {
		setFormat(BIN);
	}
	else if (command == "oct") {
		setFormat(OCT);
	}
	else if (command == "dec" || command == "d") {
		setFormat(DEC);
	}
	else if (command == "hex" || command == "0x") {
		setFormat(HEX);
	}
	else if (command == "eng") {
		setFormat(ENG);
	}
	else if (command == "siu") {
		setFormat(SIU);
	}
	else if (command == "quit" || command == "q" || command == "exit") {
		m_quit = true;
	}
	else {
		throw new CalcException("Unknown Command '" + command + "'", 0);
	}
}

void Calc::executeOverride(QString command) {
	if (command == "bin" || command == "0b") {
		m_formatOverride = BIN;
	}
	else if (command == "oct") {
		m_formatOverride = OCT;
	}
	else if (command == "dec" || command == "d") {
		m_formatOverride = DEC;
	}
	else if (command == "hex" || command == "0x") {
		m_formatOverride = HEX;
	}
	else if (command == "eng") {
		m_formatOverride = ENG;
	}
	else if (command == "siu") {
		m_formatOverride = SIU;
	}
	else {
		throw new CalcException("Unknown Override '" + command + "'", 0);
	}
}

void Calc::calc(QString input, result_t *result) {
	SyntaxTree t;
	const TreeNode *root;
	bool showErrorPos = true;

	// todo: cleanup this method

	int open = input.count('(');
	int close = input.count(')');

	for (int i=0; i<(open-close); i++) {
		input.append(')');
	}

	m_formatOverride = m_format;
	result->type = RESULT_INPUT;

	try {
		root = t.parse(input);

		//root->print();

		if (root->metaObject()->className() == QString("CommandNode")) {
			if ((qobject_cast<const CommandNode*>(root))->m_override) {
				executeOverride((qobject_cast<const CommandNode*>(root))->m_command);
				root = root->m_childNodes[0];
			}
			else {
				executeCommand((qobject_cast<const CommandNode*>(root))->m_command);
				root = NULL;
				//result->type = RESULT_COMMAND;
			}
		}
		else if (root->metaObject()->className() == QString("FunctionAssignmentNode")) {
			(qobject_cast<const FunctionAssignmentNode*>(root))->execute();
			root = NULL;
		}

		if (root != NULL) {
			m_result = root->evaluate("");
			ValueTable::setVariable("ans", m_result);
		}
	}
	catch (CalcException *e) {
		QString err;

		if (showErrorPos) {
			for (int i=0; i<e->position-1; i++) {
				err += " ";
			}
			err += "^\n";
		}
		err += e->message;

		m_error = err;
		result->type = RESULT_ERROR;
	}

	if (result->type == RESULT_ERROR) {
		result->resultString = m_error;		// todo: m_error is not required as member any more

	}
	else {
		result->type = getResultType(input);
		result->resultString = getResult();
	}
	result->input = input;
	result->result = m_result;
	result->quit = m_quit;
	result->format = m_format;
}

QString Calc::getResult() const {
	QString res;
	int pot;
	number_t div;
	char si = ' ';

	res += " = ";
	switch(m_formatOverride) {
	case BIN:
		res += QString::fromAscii("0b") + QString::number((int)m_result, 2);
		break;
	case OCT:
		res += QString::fromAscii("0") + QString::number((int)m_result, 8);
		break;
	case DEC:
		res += QString::number(m_result);
		break;
	case HEX:
		res += QString::fromAscii("0x") + QString::number((int)m_result, 16);
		break;
	case ENG:
		pot = 0;
		div = 1;
		if (fabs(m_result) >= 1) {
			while (fabs(m_result) >= (div*1000)) {
				div *= 1000;
				pot++;
			}
			res += QString::number(m_result/div) + "e" + QString::number(pot*3);
		}
		else if (m_result == 0) {
			res += QString::number(m_result)+ "e0";
		}
		else {
			while (fabs(m_result) < div) {
				div /= 1000;
				pot++;
			}
			res += QString::number(m_result/div) + "e-" + QString::number(pot*3);
		}
		break;
	case SIU:
		pot = 0;
		div = 1;
		if (fabs(m_result) >= 1000) {
			while (fabs(m_result) >= (div*1000)) {
				if (pot == 8) break;
				div *= 1000;
				pot++;
			}

			switch (pot) {
			case 1:
				si = 'k';
				break;
			case 2:
				si = 'M';
				break;
			case 3:
				si = 'G';
				break;
			case 4:
				si = 'T';
				break;
			case 5:
				si = 'P';
				break;
			case 6:
				si = 'E';
				break;
			case 7:
				si = 'Z';
				break;
			case 8:
				si = 'Y';
				break;
			}

			res += QString::number(m_result/div) + si;
		}
		else if (m_result >= 0) {
			res += QString::number(m_result);
		}
		else {
			while (fabs(m_result) < div) {
				if (pot == 8) break;
				div /= 1000;
				pot++;
			}

			switch (pot) {
			case 1:
				si = 'm';
				break;
			case 2:
				si = 'u';
				break;
			case 3:
				si = 'n';
				break;
			case 4:
				si = 'p';
				break;
			case 5:
				si = 'f';
				break;
			case 6:
				si = 'a';
				break;
			case 7:
				si = 'z';
				break;
			case 8:
				si = 'y';
				break;
			}

			res += QString::number(m_result/div) + si;
		}
		break;
	}

	return res;
}

result_type_t Calc::getResultType(const QString &input) const {
	QRegExp regex(" *:.*");
	if (regex.exactMatch(input)) {	// commands
		return RESULT_COMMAND;
	}

	QRegExp regex2(".+(=|:=).+");
	if (regex2.exactMatch(input)) {	// definitions
		return RESULT_DEFINITION;
	}

	return RESULT_RESULT;
}

void Calc::setFormat(output_format_t format) {
	m_format = format;
	m_formatOverride = format;
}

output_format_t Calc::format() {
	return m_format;
}
