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

#include "treenode.h"
#include <QDebug>
#include <iostream>

using namespace std;

TreeNode::TreeNode(const QString &name, int pos, QObject *parent) : m_name(name), m_pos(pos), QObject(parent) {

}

void TreeNode::addChild(const TreeNode *child) {
	m_childNodes.append(child);
}

void TreeNode::copyChilds(const TreeNode *parent) {
	m_childNodes.append(parent->m_childNodes);
}

void TreeNode::print(int deph) const {
	for (int i=0; i<deph-1; i++) {
		cout << "|  ";
	}
	if (deph > 0)
		cout << "|--";
	cout << qPrintable(m_name) << endl;

	foreach(const TreeNode *child, m_childNodes) {
		child->print(deph+1);
	}
}

number_t TreeNode::evaluate(const QString &environment) const {

}
