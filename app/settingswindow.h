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

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include "settings.h"

namespace Ui {
    class settingswindow;
}

class settingswindow : public QDialog
{
    Q_OBJECT

public:
	explicit settingswindow(QWidget *parent = 0);
    ~settingswindow();

private slots:
	void on_fontColorButton_released();

	void on_backgroundColorButton_released();

	void on_errorColorButton_released();

	void on_assignmentColorButton_released();

	void on_resultColorButton_released();

	void on_commandColorButton_released();

	void on_close_released();

	void on_opacitySlider_valueChanged(int value);

	void on_fontSizeSlider_valueChanged(int value);

private:
    Ui::settingswindow *ui;
	void refreshButtonColors();

};

#endif
