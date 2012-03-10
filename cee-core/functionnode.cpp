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

#include "functionnode.h"
#include "calcexception.h"
#include <math.h>
#include "functiontable.h"
#include "valueexception.h"
#include "valuetable.h"
#include "valuenode.h"

FunctionNode::FunctionNode(const QString &id, int pos, QObject *parent) : m_id(id), TreeNode("f: " + id, pos, parent) {

}

number_t FunctionNode::evaluate(const QString &environment) const {
	number_t result = 0;
	const FunctionAssignmentNode *f;

	f = FunctionTable::get(m_id, m_childNodes.count());

	if (f != 0) {
		// todo: check for recursions (store all called functions in a QHash and check...)

		QString newEnvironment(FunctionTable::mangledId(m_id, m_childNodes.count()));
		// add arguments to environment
		for (int i=0; i<m_childNodes.count(); i++) {
			ValueTable::setVariable(newEnvironment + qobject_cast<const ValueNode*>(f->m_childNodes[0]->m_childNodes[i])->m_id, m_childNodes[i]->evaluate(environment));
		}
		result = f->m_childNodes[1]->evaluate(newEnvironment);

		// todo: delete environment
	}
	else if (m_id == "add") {
		foreach (const TreeNode *arg, m_childNodes) {
			result += arg->evaluate(environment);
		}
	}
	else if (m_id == "sub") {
		if (m_childNodes.count() != 2) throw new CalcException("sub awaits 2 arguments", m_pos);

		result = m_childNodes[0]->evaluate(environment) - m_childNodes[1]->evaluate(environment);
	}
	else if (m_id == "mul") {
		if (m_childNodes.count() != 2) throw new CalcException("mul awaits 2 arguments", m_pos);

		result = m_childNodes[0]->evaluate(environment) * m_childNodes[1]->evaluate(environment);
	}
	else if (m_id == "div") {
		if (m_childNodes.count() != 2) throw new CalcException("div awaits 2 arguments", m_pos);

		result = m_childNodes[0]->evaluate(environment) / m_childNodes[1]->evaluate(environment);
	}
	else if (m_id == "mod") {
		if (m_childNodes.count() != 2) throw new CalcException("div awaits 2 arguments", m_pos);

		result = (int)m_childNodes[0]->evaluate(environment) % (int)m_childNodes[1]->evaluate(environment);
	}
	else if (m_id == "max") {
		if (m_childNodes.count() < 1) throw new CalcException("max awaits at least 1 argument", m_pos);

		QList<const TreeNode*>::const_iterator i;
		i = m_childNodes.constBegin();
		result = (*i)->evaluate(environment);

		for (; i != m_childNodes.constEnd(); ++i) {
			number_t r;

			r = (*i)->evaluate(environment);
			if (r > result) result = r;
		}
	}
	else if (m_id == "min") {
		if (m_childNodes.count() < 1) throw new CalcException("min awaits at least 1 argument", m_pos);

		QList<const TreeNode*>::const_iterator i;
		i = m_childNodes.constBegin();
		result = (*i)->evaluate(environment);

		for (; i != m_childNodes.constEnd(); ++i) {
			number_t r;

			r = (*i)->evaluate(environment);
			if (r < result) result = r;
		}
	}
	else if (m_id == "avg") {
		if (m_childNodes.count() < 1) throw new CalcException("avg awaits at least 1 argument", m_pos);

		foreach (const TreeNode *arg, m_childNodes) {
			result += arg->evaluate(environment);
		}

		result /= m_childNodes.count();
	}
	else if (m_id == "sin") {
		if (m_childNodes.count() != 1) throw new CalcException("sin awaits 1 argument", m_pos);

		result = sin(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "cos") {
		if (m_childNodes.count() != 1) throw new CalcException("cos awaits 1 argument", m_pos);

		result = cos(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "tan") {
		if (m_childNodes.count() != 1) throw new CalcException("tan awaits 1 argument", m_pos);

		result = tan(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "asin") {
		if (m_childNodes.count() != 1) throw new CalcException("asin awaits 1 argument", m_pos);

		result = asin(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "acos") {
		if (m_childNodes.count() != 1) throw new CalcException("acos awaits 1 argument", m_pos);

		result = acos(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "atan") {
		if (m_childNodes.count() != 1) throw new CalcException("atan awaits 1 argument", m_pos);

		result = atan(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "sinh") {
		if (m_childNodes.count() != 1) throw new CalcException("sinh awaits 1 argument", m_pos);

		result = sinh(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "cosh") {
		if (m_childNodes.count() != 1) throw new CalcException("cosh awaits 1 argument", m_pos);

		result = cosh(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "tanh") {
		if (m_childNodes.count() != 1) throw new CalcException("tanh awaits 1 argument", m_pos);

		result = tanh(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "round") {
		if (m_childNodes.count() != 1) throw new CalcException("round awaits 1 argument", m_pos);

		result = round(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "floor") {
		if (m_childNodes.count() != 1) throw new CalcException("floor awaits 1 argument", m_pos);

		result = floor(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "ceil") {
		if (m_childNodes.count() != 1) throw new CalcException("ceil awaits 1 argument", m_pos);

		result = ceil(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "ln") {
		if (m_childNodes.count() != 1) throw new CalcException("ln awaits 1 argument", m_pos);

		result = log(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "log") {
		if (m_childNodes.count() != 1) throw new CalcException("log awaits 1 argument", m_pos);

		result = log10(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "sqrt") {
		if (m_childNodes.count() != 1) throw new CalcException("sqrt awaits 1 argument", m_pos);

		result = sqrt(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "root") {

	}
	else if (m_id == "and") {
		if (m_childNodes.count() != 2) throw new CalcException("and awaits 2 arguments", m_pos);

		result = (int)m_childNodes[0]->evaluate(environment) & (int)m_childNodes[1]->evaluate(environment);
	}
	else if (m_id == "or") {
		if (m_childNodes.count() != 2) throw new CalcException("mul awaits 2 arguments", m_pos);

		result = (int)m_childNodes[0]->evaluate(environment) | (int)m_childNodes[1]->evaluate(environment);
	}
	else if (m_id == "xor") {
		if (m_childNodes.count() != 2) throw new CalcException("mul awaits 2 arguments", m_pos);

		result = (int)m_childNodes[0]->evaluate(environment) ^ (int)m_childNodes[1]->evaluate(environment);
	}
	else if (m_id == "not") {
		if (m_childNodes.count() != 1) throw new CalcException("not awaits 1 argument", m_pos);

		return ~(int)m_childNodes[0]->evaluate(environment);
	}
	else if (m_id == "abs") {
		if (m_childNodes.count() != 1) throw new CalcException("abs awaits 1 argument", m_pos);

		result = fabs(m_childNodes[0]->evaluate(environment));
	}
	else if (m_id == "pow") {
		if (m_childNodes.count() != 2) throw new CalcException("pow awaits 2 argument", m_pos);

		result = pow(m_childNodes[0]->evaluate(environment), m_childNodes[1]->evaluate(environment));
	}
	else {
		throw new CalcException("'" + m_id + "' not defined", m_pos);
	}

	return result;
}
