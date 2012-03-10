/*cee - Commandline calculator for enginEErs
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

#ifndef CALC_H
#define CALC_H

#include "numbers.h"
#include <QString>
#include "treenode.h"

using namespace std;

typedef enum {
	BIN,
	OCT,
	DEC,
	HEX,
	ENG,
	SIU,
} output_format_t;

typedef enum {
	RESULT_COMMAND,
	RESULT_RESULT,
	RESULT_DEFINITION,
	RESULT_INPUT,
	RESULT_ERROR,
} result_type_t;

typedef struct {
	result_type_t type;
	number_t result;
	QString resultString;
	QString input;
	bool quit;
	output_format_t format;
} result_t;

class Calc {
public:
	Calc();
	void calc(QString input, result_t *result);
	void setFormat(const output_format_t format);
	output_format_t format();

protected:
	void executeCommand(const QString command);
	void executeOverride(const QString command);
	result_type_t getResultType(const QString &input) const;
	QString getResult() const;

	output_format_t m_format;
	output_format_t m_formatOverride;
	number_t m_result;
	QString m_error;
	bool m_quit;
};

#endif
