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

%option noyywrap never-interactive nounistd
%option yylineno

%{

//%option bison-bridge

#include "numbers.h"
#include <stdio.h>
#include "syntax_tree_wrapper.h"
#include "scanner.h"
#include "parser.h"

int first_column, last_column;

#define lexme() yylval.string=strcpy(malloc(yyleng+1), yytext);yylval.pos=last_column

#define YY_USER_ACTION if (yytext[0] != ' ' && yytext[0] != '\t') first_column = last_column+1; last_column += yyleng;

%}

%%
[ \t]+				{ ; }
[0-9]*[\.\,]?[0-9]+			{ yylval.node = newNumber(fromDec(yytext), last_column); return NUM; }
[0-9]*[\.\,]?[0-9]+E[\+\-]?[0-9]	{ yylval.node = newNumber(fromDec(yytext), last_column); return NUM; }
0b[01]+					{ yylval.node = newNumber(fromBin(yytext+2), last_column); return NUM; }
0x[0123456789ABCDEFabcdef]+		{ yylval.node = newNumber(fromHex(yytext+2), last_column); return NUM; }
[0-9]*[\.\,]?[0-9]+[yzafpnumkMGTPEZY]	{ yylval.node = newNumber(fromSi(yytext), last_column); return NUM; }
\+				{ return '+'; }
-				{ return '-'; }
\*				{ return '*'; }
\/				{ return '/'; }
%				{ return '%'; }
\^				{ return '^'; }
\|				{ return OR; }
&				{ return AND; }
~				{ return NOT; }
\(				{ return '('; }
\)				{ return ')'; }
ans|#				{ return ANS; }
[a-zA-Z_][a-zA-Z0-9_]*		{ lexme(); return ID; }
=				{ return ASS; }
:=				{ return CONST; }
;				{ return ';'; }
,				{ return ','; }
:				{ return COM; }
\.				{ return OVERRIDE; }
.				{ return ERR; }
%%

//int yyparse();

int scanLine(char *string) {
	int ret;
	YY_BUFFER_STATE buffer;

	first_column = 0;
	last_column = 0;

	buffer = yy_scan_string(string);
	ret = yyparse();
	yy_delete_buffer(buffer);

	return ret;
}

