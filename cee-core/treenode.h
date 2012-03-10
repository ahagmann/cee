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

#ifndef TREENODE_H
#define TREENODE_H

#include <QObject>
#include <QList>
#include <QString>
#include "numbers.h"
#include <QHash>

class TreeNode : public QObject {
    Q_OBJECT
public:
	explicit TreeNode(const QString &name, int pos, QObject *parent = 0);
	void addChild(const TreeNode *child);
	void copyChilds(const TreeNode *parent);
	void print(int deph = 0) const;
	virtual number_t evaluate(const QString &environment) const;

public:
	const QString m_name;
	QList<const TreeNode*> m_childNodes;
	const int m_pos;
};

#endif // TREENODE_H
