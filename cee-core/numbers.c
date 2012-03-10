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

#include "numbers.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>

number_t fromDec(char *str) {
	int count = 0;
	char dp;

	setlocale(LC_NUMERIC, "C");

	while (str[count]) {
		if (str[count] == ',' || str[count] == '.') str[count] = '.';
		count++;
	}

	return atof(str);
}

number_t fromBin(char *str) {
	return (number_t)strtol(str, NULL, 2);
}

number_t fromHex(char *str) {
	return (number_t)strtol(str, NULL, 16);
}

number_t fromOct(char *str) {
	return (number_t)strtol(str, NULL, 8);
}

number_t fromSi(char *str) {
	char unit;
	number_t ret, a;
	int len;

	len = strlen(str);
	unit = str[len-1];
	str[len-1] = 0;

	a = fromDec(str);

	switch (unit) {
	case 'y':
		ret = a/1000000000000000000000000.0;
		break;
	case 'z':
		ret = a/1000000000000000000000.0;
		break;
	case 'a':
		ret = a/1000000000000000000.0;
		break;
	case 'f':
		ret = a/1000000000000000.0;
		break;
	case 'p':
		ret = a/1000000000000.0;
		break;
	case 'n':
		ret = a/1000000000.0;
		break;
	case 'u':
		ret = a/1000000.0;
		break;
	case 'm':
		ret = a/1000.0;
		break;
	case 'k':
		ret = a*1000.0;
		break;
	case 'M':
		ret = a*1000000.0;
		break;
	case 'G':
		ret = a*1000000000.0;
		break;
	case 'T':
		ret = a*1000000000000.0;
		break;
	case 'P':
		ret = a*1000000000000000.0;
		break;
	case 'E':
		ret = a*1000000000000000000.0;
		break;
	case 'Z':
		ret = a*1000000000000000000.0;
		break;
	case 'Y':
		ret = a*1000000000000000000000.0;
		break;
	}

	return ret;
}
