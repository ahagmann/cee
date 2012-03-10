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

#include "valueassignmentnode.h"
#include "valuetable.h"
#include "calcexception.h"
#include "valueexception.h"

ValueAssignmentNode::ValueAssignmentNode(const QString &id, bool constant, int pos, QObject *parent) : m_id(id), m_constant(constant), TreeNode("id: " + id, pos, parent) {

}

number_t ValueAssignmentNode::evaluate(const QString &environment) const {
	number_t result;

	result = m_childNodes[0]->evaluate(environment);

	try {
		if (m_constant)
			ValueTable::setConstant(m_id, result);
		else
			ValueTable::setVariable(m_id, result);
	}
	catch (ValueException *e) {
		throw new CalcException(e->message, m_pos);
	}

	return result;
}
