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

#include "functiontable.h"
#include "calcexception.h"
#include <QDebug>

FunctionTable::FunctionTable(QObject *parent) : QObject(parent) {

}

void FunctionTable::add(const FunctionAssignmentNode *function) {
	const FunctionNode *f;

	f = qobject_cast<const FunctionNode*>(function->m_childNodes[0]);

	// check if all arguments are ids
	foreach (const TreeNode *arg, f->m_childNodes) {
		if (arg->metaObject()->className() != QString("ValueNode"))
			throw new CalcException("Invalid argument in function definition", function->m_pos);
	}

	// todo: check if args have different names ???

	m_functions.insert(mangledId(f->m_id, f->m_childNodes.count()), function);
}

const FunctionAssignmentNode *FunctionTable::get(const QString id, const int argc) {
	QString mangledName(mangledId(id, argc));

	if (m_functions.contains(mangledName) == false) return NULL;

	return m_functions[mangledName];
}

QString FunctionTable::mangledId(const QString id, const int argc) {
	return id + " " + QString::number(argc);
}

QHash<QString, const FunctionAssignmentNode*> FunctionTable::m_functions;
