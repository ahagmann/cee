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

#include "settings.h"
#include <QSettings>
#include <QDebug>

Settings *Settings::getInstance() {
	if (!m_object) {
		m_object = new Settings();
	}

	return m_object;
}

void Settings::destroy() {
	delete m_object;
}

Settings::Settings(QObject *parent) : QObject(parent) {
	QSettings s("cee", "cee");

	backgroundColor = s.value("console/backgroundcolor", Qt::black).value<QColor>();
	fontColor = s.value("console/fontcolor", Qt::white).value<QColor>();
	errorColor = s.value("console/errorcolor", Qt::red).value<QColor>();
	resultColor = s.value("console/resultcolor", Qt::yellow).value<QColor>();
	assignmentColor = s.value("console/assignmentcolor", Qt::blue).value<QColor>();
	commandColor = s.value("console/commandcolor", Qt::cyan).value<QColor>();
	consoleOpacity = s.value("console/opacity", 210).toInt();
	fontSize = s.value("console/fontsize", 10).toInt();
	windowWidth = s.value("window/width", 300).toInt();
	windowHeight = s.value("window/height", 200).toInt();
	format = (output_format_t)s.value("calc/format", DEC).toInt();
}

Settings::~Settings() {
	QSettings s("cee", "cee");

	s.setValue("console/backgroundcolor", backgroundColor);
	s.setValue("console/fontcolor", fontColor);
	s.setValue("console/errorcolor", errorColor);
	s.setValue("console/resultcolor", resultColor);
	s.setValue("console/assignmentcolor", assignmentColor);
	s.setValue("console/commandcolor", commandColor);
	s.setValue("console/opacity", consoleOpacity);
	s.setValue("console/fontsize", fontSize);
	s.setValue("window/width", windowWidth);
	s.setValue("window/height", windowHeight);
	s.setValue("calc/format", format);
}

Settings *Settings::m_object = 0;

