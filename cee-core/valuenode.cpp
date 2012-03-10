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

#include "valuenode.h"
#include "valuetable.h"
#include "valueexception.h"
#include "calcexception.h"

ValueNode::ValueNode(const QString &id, int pos, QObject *parent) : m_id(id), TreeNode(id, pos, parent) {

}

number_t ValueNode::evaluate(const QString &environment) const {
	number_t result;

	// check environment
	if (ValueTable::contains(environment + m_id)) {
		result =  ValueTable::getValue(environment + m_id);
	}
	else {
		try {
			result =  ValueTable::getValue(m_id);
		}
		catch (ValueException *e) {
			throw new CalcException(e->message, m_pos);
		}
	}

	return result;
}
