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

#include "valuetable.h"
#include "valueexception.h"

ValueTable::ValueTable(QObject *parent) : QObject(parent) {

}

bool ValueTable::contains(QString id) {
	return constants.contains(id) || variables.contains(id);
}

number_t ValueTable::getValue(QString id) {
	if (constants.contains(id) == true) {
		return constants[id];
	}
	else if (variables.contains(id) == true) {
		return variables[id];
	}

	throw new ValueException("'" + id + "' not defined");
}

void ValueTable::setVariable(QString id, number_t value) {
	if (constants.contains(id) == true) throw new ValueException("'" + id + "' is a constant");

	variables[id] = value;
}

void ValueTable::setConstant(QString id, number_t value) {
	if (constants.contains(id) == true) throw new ValueException("'" + id + "' is already defined");

	constants[id] = value;
}

QHash<QString, number_t> ValueTable::variables;

QHash<QString, number_t> ValueTable::constants;
