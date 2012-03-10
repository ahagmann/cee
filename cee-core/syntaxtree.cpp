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

#include "syntaxtree.h"
#include "syntax_tree_wrapper.h"
#include "scanner.h"
#include "numbernode.h"
#include "valuenode.h"
#include "functionnode.h"
#include "valueassignmentnode.h"
#include "commandnode.h"
#include "functionassignmentnode.h"
#include "calcexception.h"
#include <QDebug>

void *root;
SyntaxTree *syntaxTree = 0;

SyntaxTree::SyntaxTree(QObject *parent) : QObject(parent), m_root(0) {

}

TreeNode *SyntaxTree::parse(QString line) {
	//syntaxTree = this;

	if (scanLine(line.toAscii().data()) != 0) {
	}
	else {
		m_root = ((TreeNode*)root);
	}
	return m_root;
}

void *newNode(char *name, int pos) {
	return new TreeNode(name, pos, syntaxTree);
}

void *newNumber(number_t number, int pos) {
	return new NumberNode(number, pos, syntaxTree);
}

void *newValue(char *id, int pos) {
	return new ValueNode(id, pos, syntaxTree);
}

void *newValueAssignment(char *id, int constant, int pos) {
	return new ValueAssignmentNode(id, constant, pos, syntaxTree);
}

void *newFunction(char *name, int pos) {
	return new FunctionNode(name, pos, syntaxTree);
}

void *newCommand(char *command, int override, int pos) {
	return new CommandNode(command, override, pos, syntaxTree);
}

void *newFunctionAssignment(char *id, int pos) {
	return new FunctionAssignmentNode(id, pos, syntaxTree);
}

void error(char *message, int postition) {
	throw new CalcException(message, postition);
}

void addChild(void *node, void *child) {
	((TreeNode*)node)->addChild((TreeNode*)child);
}

void copyChilds(void *node, void *parent) {
	((TreeNode*)node)->copyChilds((TreeNode*)parent);
}
