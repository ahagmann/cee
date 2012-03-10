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
%{
#include "numbers.h"
#include "syntax_tree_wrapper.h"
#include <stdarg.h>

%}

%defines

%token NUM ANS
%token NOT AND OR COM ERR
%token ID UNIT
%token '+' '-' '*' '/' '%' '^' '(' ')'
%token ASS ';' CONST OVERRIDE ',' DEF

%left ASS
%left '+' '-'
%left '*' '/'
%left '%'
%right '^'
%left AND OR XOR
%right NOT

%{

void yyerror(const char* err);
extern int first_column, last_column;

%}

%%

root:	ans				{ root = $1.node; }
		;

ans:	line				{ $$.node = $1.node; }
		| ID ASS expr		{ $$.node = newValueAssignment($1.string, 0, last_column); free($1.string); addChild($$.node, $3.node); }
		| ID CONST expr		{ $$.node = newValueAssignment($1.string, 1, last_column); free($1.string); addChild($$.node, $3.node); }
		| function ASS expr	{ $$.node = newFunctionAssignment($1.node, last_column); addChild($$.node, $1.node); addChild($$.node, $3.node); }
		| COM ID		{ $$.node = newCommand($2.string, 0, last_column); }
		| OVERRIDE ID line	{ $$.node = newCommand($2.string, 1, last_column); addChild($$.node, $3.node); }
		;

line:	expr				{ $$.node = $1.node; }
		| '+' expr		{ $$.node = newFunction("add", last_column); addChild($$.node, newValue("ans", last_column)); addChild($$.node, $2.node); }
		| '-' expr		{ $$.node = newFunction("sub", last_column); addChild($$.node, newValue("ans", last_column)); addChild($$.node, $2.node); }
		| '*' expr		{ $$.node = newFunction("mul", last_column); addChild($$.node, newValue("ans", last_column)); addChild($$.node, $2.node); }
		| '/' expr		{ $$.node = newFunction("div", last_column); addChild($$.node, newValue("ans", last_column)); addChild($$.node, $2.node); }
		| '%' expr		{ $$.node = newFunction("mod", last_column); addChild($$.node, newValue("ans", last_column)); addChild($$.node, $2.node); }
		| '^' expr		{ $$.node = newFunction("pow", last_column); addChild($$.node, newValue("ans", last_column)); addChild($$.node, $2.node); }
		| AND expr		{ $$.node = newFunction("and", last_column); addChild($$.node, newValue("ans", last_column)); addChild($$.node, $2.node); }
		| OR expr		{ $$.node = newFunction("or", last_column); addChild($$.node, newValue("ans", last_column)); addChild($$.node, $2.node); }
		| XOR expr		{ $$.node = newFunction("xor", last_column); addChild($$.node, newValue("ans", last_column)); addChild($$.node, $2.node); }
		|			{ $$.node = newValue("ans", last_column); }
		;

function:	ID '(' args ')'		{ $$.node = newFunction($1.string, $1.pos); copyChilds($$.node, $3.node); }
		| ID '(' ')'		{ $$.node = newFunction($1.string, $1.pos); free($1.string); }
		;

args:		expr			{ $$.node = newNode("args", last_column); addChild($$.node, $1.node); }
		| args ';' expr		{ $$.node = $1.node; addChild($$.node, $3.node); }
		;

expr:		ID			{ $$.node = newValue($1.string, $1.pos); free($1.string); }
		| NUM			{ $$.node = $1.node; }
		| ANS			{ $$.node = newValue("ans", last_column); }
		| '-' NUM		{ $$.node = newFunction("sub", last_column); addChild($$.node, newNumber(0, last_column)); addChild($$.node, $2.node); }
		| '(' expr ')'		{ $$.node = $2.node; }
		| function		{ $$.node = $1.node; }
		| expr '+' expr		{ $$.node = newFunction("add", last_column); addChild($$.node, $1.node); addChild($$.node, $3.node); }
		| expr '-' expr		{ $$.node = newFunction("sub", last_column); addChild($$.node, $1.node); addChild($$.node, $3.node); }
		| expr '*' expr		{ $$.node = newFunction("mul", last_column); addChild($$.node, $1.node); addChild($$.node, $3.node); }
		| expr '/' expr		{ $$.node = newFunction("div", last_column); addChild($$.node, $1.node); addChild($$.node, $3.node); }
		| expr '%' expr		{ $$.node = newFunction("mod", last_column); addChild($$.node, $1.node); addChild($$.node, $3.node); }
		| expr '^' expr		{ $$.node = newFunction("pow", last_column); addChild($$.node, $1.node); addChild($$.node, $3.node); }
		| expr AND expr		{ $$.node = newFunction("and", last_column); addChild($$.node, $1.node); addChild($$.node, $3.node); }
		| expr OR expr		{ $$.node = newFunction("or", last_column); addChild($$.node, $1.node); addChild($$.node, $3.node); }
		| expr XOR expr		{ $$.node = newFunction("xor", last_column); addChild($$.node, $1.node); addChild($$.node, $3.node); }
		| NOT expr		{ $$.node = newFunction("not", last_column); addChild($$.node, $2.node); }
		;

%%

void yyerror(const char* err) {
	error(err, last_column);
}

