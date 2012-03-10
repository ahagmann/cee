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

#ifndef VALUETABLE_H
#define VALUETABLE_H

#include <QObject>
#include <QHash>
#include "numbers.h"

class ValueTable : public QObject {
	Q_OBJECT
public:
	static number_t getValue(QString id);
	static void setVariable(QString id, number_t value);
	static void setConstant(QString id, number_t value);
	static bool contains(QString id);

signals:

public slots:

protected:
	static QHash<QString, number_t> variables;
	static QHash<QString, number_t> constants;

private:
	ValueTable(QObject *parent = 0);
};

#endif
