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

#include "highlight.h"
#include <QDebug>
#include <QRegExpValidator>

Highlight::Highlight(QTextDocument *parent) : QSyntaxHighlighter(parent) {

}

void Highlight::highlightBlock(const QString &text) {
	int dummy;
	QString input(text);
	QTextCharFormat format;

	// todo: improve this ...

	QRegExp regex(" *:.*");
	QRegExpValidator val(regex, this);
	if (val.validate(input, dummy) == QValidator::Acceptable) {		// commands
		format.setForeground(Qt::lightGray);
		setFormat(0, text.length(), format);
	}

	QRegExp regex2(".+(=|:=).+");
	QRegExpValidator val2(regex2, this);
	if (val2.validate(input, dummy) == QValidator::Acceptable) {	// definitions
		format.setForeground(Qt::cyan);
		setFormat(0, text.length(), format);
	}

	QRegExp regex1(" = .*");
	QRegExpValidator val1(regex1, this);
	if (val1.validate(input, dummy) == QValidator::Acceptable) {	// results
		format.setForeground(Qt::yellow);
		setFormat(0, text.length(), format);
	}
}
