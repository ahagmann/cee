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

#ifndef NUMBERS_H
#define NUMBERS_H

typedef double number_t;

typedef enum {
	SUCCESS,
	ERROR,
} error_t;

typedef struct {
	number_t value;
	void *next;
} param_list_t;

typedef struct {
	char *id;
	void *next;
} arg_list_t;

typedef struct {
	int argCount;
	char *id;
	void *args;
} function_t;

number_t fromDec(char *str);
number_t fromHex(char *str);
number_t fromBin(char *str);
number_t fromOct(char *str);
number_t fromSi(char *str);
void print(number_t val);

#endif
