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

#include "commandline.h"
#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>
#include <QDebug>

#define BLACK	"\33[22;30m"
#define GRAY		"\33[01;30m"
#define RED		"\33[22;31m"
#define LRED		"\33[01;21m"
#define GREEN	"\33[22;32m"
#define LGREEN	"\33[01;32m"
#define BLUE		"\33[22;34m"
#define LBLUE	"\33[01;34m"
#define BROWN	"\33[22;33m"
#define YELLOW	"\33[01;33m"
#define CYAN		"\33[22;36m"
#define LCYAN	"\33[22;36m
#define MAGENTA	"\33[22;35m"
#define LMAGENTA	"\33[01;35m"
#define DEFAULT	"\33[0m"

commandLine::commandLine(Calc &c, QObject *parent) : m_c(c), QObject(parent) {

}

void commandLine::print(QString text, result_type_t type) {
	switch (type) {
	case RESULT_COMMAND:
		std::cout << CYAN;
		break;

	case RESULT_RESULT:
		std::cout << YELLOW;
		break;

	case RESULT_DEFINITION:
		std::cout << BLUE;
		break;

	case RESULT_INPUT:
		std::cout << DEFAULT;
		break;

	case RESULT_ERROR:
		std::cout << RED;
		break;
	}

	std::cout << qPrintable(text) << std::endl;
	std::cout << DEFAULT;
}

void commandLine::exec() {
	char *line = 0;
	result_t result;

	while(true) {
		line = readline (NULL);
		printf("\033[A\033[2K");		// clear the line
		if (line && *line) {
			add_history (line);
		}
		if (line == NULL) {
			break;
		}

		m_c.calc(line, &result);
		free(line);
		line = 0;

		switch (result.type) {
		case RESULT_COMMAND:
			print(result.input, RESULT_COMMAND);
			print(result.resultString, RESULT_RESULT);
			break;

		case RESULT_RESULT:
			print(result.input, RESULT_INPUT);
			print(result.resultString, RESULT_RESULT);
			break;

		case RESULT_DEFINITION:
			print(result.input, RESULT_DEFINITION);
			break;

		case RESULT_ERROR:
		default:
			print(result.input, RESULT_INPUT);
			print(result.resultString, RESULT_ERROR);
			break;
		}

		if (result.quit) break;
	};
	rl_free_line_state();
}
