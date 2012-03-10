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

#ifndef SYNTAX_TREE_WRAPPER_H
#define SYNTAX_TREE_WRAPPER_H

#include "numbers.h"
#include "functionnode.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	char *string;
	void *node;
	int pos;
} yy_type_t;

#define YYSTYPE  yy_type_t

extern void *root;

void *newNode(char *name, int pos);
void *newNumber(number_t number, int pos);
void *newValue(char *id, int pos);
void *newFunction(char *name, int pos);
void *newCommand(char *name, int override, int pos);
void *newValueAssignment(char *id, int constant, int pos);
void *newFunctionAssignment(char *id, int pos);
void addChild(void *node, void *child);
void copyChilds(void *node, void *parent);
void error(char *message, int position);

#ifdef __cplusplus
}
#endif

#endif
