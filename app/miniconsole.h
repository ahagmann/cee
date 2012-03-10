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

#ifndef MINICONSOLE_H
#define MINICONSOLE_H

#include <QPlainTextEdit>
#include <QStringList>
#include <QString>

class MiniConsole : public QPlainTextEdit {
    Q_OBJECT
public:
    explicit MiniConsole(QWidget *parent = 0);

protected:
	void keyPressEvent(QKeyEvent *e);
	QString getInput();
	bool cursorInLastLine();
	void insertFromMimeData(const QMimeData *source);
	QString replaceLastLine(QString line);
	void historyUp();
	void historyDown();

	QStringList m_history;
	int m_history_index;
	QString m_current;

signals:
	void command(QString command);

public slots:
	void cut();
};

#endif
