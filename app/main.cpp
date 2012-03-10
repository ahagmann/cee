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

#include <QtGui/QApplication>
#include <QDebug>
#include <QFile>
#include "mainwindow.h"
#include "scanner.h"
#include "calc.h"
#include "miniconsole.h"
#include "commandline.h"
#include "settings.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
	result_t result;
	int ret;
	Calc c;

#ifndef GUI_ONLY
	bool gui = false;
	bool interactive = false;
	QStringList immediateInput;

	QCoreApplication *a = 0;

	a = new QCoreApplication(argc, argv);

	QStringListIterator i(a->arguments());
	i.next();																// skip program name
	while (i.hasNext()) {														// parse options
		if (i.peekNext() == "-g" || i.peekNext() == "--gui") {					// option
			gui = true;
			i.next();
		}
		else if (i.peekNext() == "-i" || i.peekNext() == "--interactive") {		// option
			interactive = true;
			i.next();
		}
		else {
			break;
		}
	}

	while (i.hasNext()) {														// parse arguments
		immediateInput.append(i.peekNext());
		i.next();
	}

	delete a;

	if (immediateInput.length() == 0 && gui == false) {						// no input
		interactive = true;													// read from stdin
	}

	//qDebug() << "gui: " << gui;
	//qDebug() << "interactive: " << interactive;
	//qDebug() << "immediate input:" << immediateInput;

	if (gui == false) {														// cli only
		commandLine cmd(c);

		if (immediateInput.count() > 0) {										// process immediate input
			QString input(immediateInput.join(" ").toAscii().data());
			std::cout << qPrintable(input) << std::endl;
			c.calc(input.toAscii().data(), &result);
			std::cout << qPrintable(result.resultString) << std::endl;
		}

		if (interactive) {													// process stdin
			cmd.exec();
			ret = 0;
		}
	}
	else {																	// gui mode
#endif
		QApplication g(argc, argv);
		MainWindow w(c);
#ifndef GUI_ONLY
		if (immediateInput.count() > 0) {										// process immediate input
			c.calc(immediateInput.join(" ").toAscii().data(), &result);
			std::cout << qPrintable(result.resultString) << std::endl;
			w.print(result.resultString, result.type);
		}

		if (interactive) {													// process stdin
			commandLine cmd(c);
			cmd.exec();
			c.calc("", &result);
			w.print(result.resultString, result.type);							// dirty get ans
		}
#endif
		w.show();
		ret = g.exec();
#ifndef GUI_ONLY
	}
#endif

error:
	return ret;
}
