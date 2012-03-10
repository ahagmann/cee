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

#include "settingswindow.h"
#include "ui_settingswindow.h"
#include <QColorDialog>

// todo: signale changes -> trigger slot to reload settings in mainwindow

settingswindow::settingswindow(QWidget *parent) : QDialog(parent), ui(new Ui::settingswindow) {
    ui->setupUi(this);

	Settings *settings = Settings::getInstance();
	refreshButtonColors();
	ui->opacitySlider->setValue(settings->consoleOpacity);
	ui->fontSizeSlider->setValue(settings->fontSize);

#ifndef __APPLE__
	ui->opacitySlider->setVisible(false);
	ui->label_6->setVisible(false);
#endif
}

settingswindow::~settingswindow() {
    delete ui;
}

void settingswindow::on_fontColorButton_released() {
	Settings *settings = Settings::getInstance();
	settings->fontColor = QColorDialog::getColor(settings->fontColor);
	refreshButtonColors();
}

void settingswindow::on_backgroundColorButton_released() {
	Settings *settings = Settings::getInstance();
	settings->backgroundColor = QColorDialog::getColor(settings->backgroundColor);
	refreshButtonColors();
}

void settingswindow::on_errorColorButton_released() {
	Settings *settings = Settings::getInstance();
	settings->errorColor = QColorDialog::getColor(settings->errorColor);
	refreshButtonColors();
}

void settingswindow::on_assignmentColorButton_released() {
	Settings *settings = Settings::getInstance();
	settings->assignmentColor = QColorDialog::getColor(settings->assignmentColor);
	refreshButtonColors();
}

void settingswindow::on_resultColorButton_released() {
	Settings *settings = Settings::getInstance();
	settings->resultColor = QColorDialog::getColor(settings->resultColor);
	refreshButtonColors();
}

void settingswindow::on_commandColorButton_released() {
	Settings *settings = Settings::getInstance();
	settings->commandColor = QColorDialog::getColor(settings->commandColor);
	refreshButtonColors();
}

void settingswindow::refreshButtonColors() {
	Settings *settings = Settings::getInstance();
	ui->fontColorButton->setStyleSheet("color: " + settings->fontColor.name());
	ui->backgroundColorButton->setStyleSheet("color: " + settings->backgroundColor.name());
	ui->errorColorButton->setStyleSheet("color: " + settings->errorColor.name());
	ui->assignmentColorButton->setStyleSheet("color: " + settings->assignmentColor.name());
	ui->resultColorButton->setStyleSheet("color: " + settings->resultColor.name());
	ui->commandColorButton->setStyleSheet("color: " + settings->commandColor.name());
}

void settingswindow::on_close_released() {
	close();
}

void settingswindow::on_opacitySlider_valueChanged(int value) {
	Settings *settings = Settings::getInstance();
	settings->consoleOpacity = value;
}

void settingswindow::on_fontSizeSlider_valueChanged(int value) {
	Settings *settings = Settings::getInstance();
	settings->fontSize = value;
}
