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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QColor>
#include "calc.h"

class Settings : public QObject {
    Q_OBJECT
public:
	static Settings *getInstance();
	static void destroy();

signals:

public slots:

private:
	explicit Settings(QObject *parent = 0);
	~Settings();
	static Settings *m_object;

public:
	QColor backgroundColor;
	QColor fontColor;
	QColor errorColor;
	QColor commandColor;
	QColor resultColor;
	QColor assignmentColor;
	int consoleOpacity;
	int fontSize;
	int windowWidth;
	int windowHeight;
	output_format_t format;
};

#endif
