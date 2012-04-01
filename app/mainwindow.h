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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "calc.h"
#include "settings.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
	explicit MainWindow(Calc &c, QWidget *parent = 0);
    ~MainWindow();

public slots:
	void command(QString command);
	void print(QString text, result_type_t type);

private slots:
	void on_actionPreferences_triggered();

	void on_actionHex_hex_triggered();

	void on_actionBinary_bin_triggered();

	void on_actionDecimal_dec_triggered();

	void on_actionEngineering_eng_triggered();

	void on_actionSI_Units_siu_triggered();

	void on_actionOcatal_oct_triggered();

	void on_actionExit_triggered();

	void on_actionAbout_triggered();

	void on_actionDocumentaion_triggered();

private:
    Ui::MainWindow *ui;
	Calc &m_c;

	void reloadSettings();
	void changeFormat(output_format_t format);
};

#endif
