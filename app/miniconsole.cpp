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

#include "miniconsole.h"
#include <QDebug>
#include <QTextBlock>
#include "settings.h"

// inspired by qconsole (http://sourceforge.net/projects/qconsole)

// todo: process pasted text and dropped files

MiniConsole::MiniConsole(QWidget *parent) : QPlainTextEdit(parent), m_history_index(0) {
	setUndoRedoEnabled(false);
	setMaximumBlockCount(1000);
	setContextMenuPolicy(Qt::NoContextMenu);

#ifdef __APPLE__
	setFont(QFont("Monaco"));
#else
	QFont f;
	f.setFamily("Courier");
	setFont(f);
#endif
}

void MiniConsole::historyUp() {
	if (m_history_index > 0) {
		if (m_history_index == m_history.count()) {
			m_history_index--;
			m_current = replaceLastLine(m_history[m_history_index]);
		}
		else {
			m_history_index--;
			replaceLastLine(m_history[m_history_index]);
		}
	}
}

void MiniConsole::historyDown() {
	if (m_history_index < (m_history.count() - 1)) {
		m_history_index++;
		replaceLastLine(m_history[m_history_index]);
	}
	else if (m_history_index < (m_history.count())) {
		m_history_index++;
		replaceLastLine(m_current);
	}
}

void MiniConsole::keyPressEvent(QKeyEvent *e) {
	bool forward = true;
	bool moveToInput = true;

	switch (e->key()) {
	case Qt::Key_Tab:
		forward = false;
		break;
	case Qt::Key_Up:
		forward = false;
		historyUp();
		break;
	case Qt::Key_Down:
		forward = false;
		historyDown();
		break;
	case Qt::Key_Left:						// allow navigation in the whole text
	case Qt::Key_Right:
		moveToInput = false;
		break;
	case Qt::Key_Backspace:					// only in the command line
		if (textCursor().positionInBlock() == 0) {
			forward = false;
		}
		break;
	case Qt::Key_C:
#ifdef __APPLE__
		if (e->modifiers() & Qt::META) {
#else
		if (e->modifiers() & Qt::CTRL) {
#endif
			replaceLastLine("");
			m_history_index = m_history.count();
		}
		break;
	case Qt::Key_Escape:
		replaceLastLine("");
		m_history_index = m_history.count();
		break;
	case Qt::Key_Enter:
	case Qt::Key_Return:
		forward = false;
		QString com(getInput());
		m_history.append(com);
		m_history_index = m_history.count();
		emit command(com);
		ensureCursorVisible();
		break;
	}

	if (e->matches(QKeySequence::Cut)) {
		forward = false;
		cut();
	}

	if (moveToInput) {
		if (cursorInLastLine() == false) {
			moveCursor(QTextCursor::End);
		}
	}

	if (forward) {
		Settings *settings = Settings::getInstance();

		QTextCursor c(textCursor());
		QTextCharFormat f(c.charFormat());
		f.setForeground(QBrush(settings->fontColor));
		c.setCharFormat(f);
		setTextCursor(c);
		QPlainTextEdit::keyPressEvent(e);
	}
}

QString MiniConsole::getInput() {
	moveCursor(QTextCursor::End, QTextCursor::MoveAnchor);
	QString str(textCursor().block().text());

	if (blockCount() > 1) {
		moveCursor(QTextCursor::StartOfLine, QTextCursor::MoveAnchor);
		moveCursor(QTextCursor::End, QTextCursor::KeepAnchor);
		textCursor().removeSelectedText();
	}
	else {
		moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);
		clear();
	}

	return str;
}

bool MiniConsole::cursorInLastLine() {
	return textCursor().blockNumber() == (blockCount() - 1);
}

void MiniConsole::insertFromMimeData(const QMimeData *source) {
	if (cursorInLastLine() == false) {
		moveCursor((QTextCursor::End));
	}
	QPlainTextEdit::insertFromMimeData(source);
}

QString MiniConsole::replaceLastLine(QString line) {
	QString ret(getInput());
	Settings *settings = Settings::getInstance();

	QTextCursor c(textCursor());
	QTextCharFormat f(c.charFormat());
	f.setForeground(QBrush(settings->fontColor));
	c.setCharFormat(f);
	setTextCursor(c);

	insertPlainText(line);
	return ret;
}

void MiniConsole::cut() {
	if (cursorInLastLine()) {
		QPlainTextEdit::cut();
	}
	else {
		QPlainTextEdit::copy();
	}
}
