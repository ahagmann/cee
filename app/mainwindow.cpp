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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "settingswindow.h"

MainWindow::MainWindow(Calc &c, QWidget *parent) : m_c(c), QMainWindow(parent), ui(new Ui::MainWindow) {
	ui->setupUi(this);

#ifdef __APPLE__
    setAttribute(Qt::WA_TranslucentBackground);
#endif
	Settings *settings = Settings::getInstance();
	resize(settings->windowWidth, settings->windowHeight);

	c.setFormat(settings->format);

	connect(ui->console, SIGNAL(command(QString)), this, SLOT(command(QString)));

	reloadSettings();
}

void MainWindow::command(QString command) {
	result_t result;

	m_c.calc(command, &result);

	changeFormat(result.format);
	if (result.quit) close();

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
}

void MainWindow::print(QString text, result_type_t type) {
	QTextCursor c(ui->console->textCursor());
	QTextCharFormat f(c.charFormat());
	Settings *settings = Settings::getInstance();

	switch (type) {
	case RESULT_COMMAND:
		f.setForeground(QBrush(settings->commandColor));
		break;

	case RESULT_RESULT:
		f.setForeground(QBrush(settings->resultColor));
		break;

	case RESULT_DEFINITION:
		f.setForeground(QBrush(settings->assignmentColor));
		break;

	case RESULT_INPUT:
		f.setForeground(QBrush(settings->fontColor));
		break;

	case RESULT_ERROR:
		f.setForeground(QBrush(settings->errorColor));
		break;
	}

	c.setCharFormat(f);
	ui->console->setTextCursor(c);

	ui->console->insertPlainText(text + "\n");

	f.setForeground(QBrush(settings->fontColor));
	c.setCharFormat(f);
	ui->console->setTextCursor(c);
}

void MainWindow::reloadSettings() {
	Settings *settings = Settings::getInstance();
	// todo: is there a better way ???
	// font color
	QPalette p(ui->console->palette());
	p.setColor(QPalette::Text, settings->fontColor);
	ui->console->setPalette(p);

	// font size
	QFont font(ui->console->font());
	font.setPointSize(settings->fontSize);
	ui->console->setFont(font);

	// backgrouond color
	ui->console->setStyleSheet("QPlainTextEdit {background-color: rgba(" +
							   QString::number(settings->backgroundColor.red())	+ "," +
							   QString::number(settings->backgroundColor.green())	+ "," +
							   QString::number(settings->backgroundColor.blue())	+ "," +
#ifdef __APPLE__
							   QString::number(settings->consoleOpacity)			+ ");}");
#else
                               QString::number(255)			+ ");}");
#endif

#ifdef __APPLE__
	ui->statusBar->setStyleSheet("background-color: rgba(" +
							   QString::number(settings->backgroundColor.red())	+ "," +
							   QString::number(settings->backgroundColor.green())	+ "," +
							   QString::number(settings->backgroundColor.blue())	+ "," +
							   QString::number(settings->consoleOpacity)			+ ");");
#endif
	changeFormat(m_c.format());
}

MainWindow::~MainWindow() {
	Settings *settings = Settings::getInstance();
	settings->windowWidth = size().width();
	settings->windowHeight = size().height();
	settings->format = m_c.format();
	Settings::destroy();

	delete ui;
}

void MainWindow::on_actionPreferences_triggered() {
	settingswindow w(this);

	w.exec();
	reloadSettings();
}

void MainWindow::changeFormat(output_format_t format) {
	ui->actionBinary_bin->setChecked(false);
	ui->actionDecimal_dec->setChecked(false);
	ui->actionEngineering_eng->setChecked(false);
	ui->actionHex_hex->setChecked(false);
	ui->actionOcatal_oct->setChecked(false);
	ui->actionSI_Units_siu->setChecked(false);

	switch (format) {
	case BIN:
		ui->actionBinary_bin->setChecked(true);
		break;
	case OCT:
		ui->actionOcatal_oct->setChecked(true);
		break;
	case DEC:
		ui->actionDecimal_dec->setChecked(true);
		break;
	case HEX:
		ui->actionHex_hex->setChecked(true);
		break;
	case ENG:
		ui->actionEngineering_eng->setChecked(true);
		break;
	case SIU:
		ui->actionSI_Units_siu->setChecked(true);
		break;
	}
}

void MainWindow::on_actionHex_hex_triggered() {
	m_c.setFormat(HEX);
	changeFormat(HEX);
}

void MainWindow::on_actionBinary_bin_triggered() {
	m_c.setFormat(BIN);
	changeFormat(BIN);
}

void MainWindow::on_actionDecimal_dec_triggered() {
	m_c.setFormat(DEC);
	changeFormat(DEC);
}

void MainWindow::on_actionEngineering_eng_triggered() {
	m_c.setFormat(ENG);
	changeFormat(ENG);
}

void MainWindow::on_actionSI_Units_siu_triggered() {
	m_c.setFormat(SIU);
	changeFormat(SIU);
}

void MainWindow::on_actionOcatal_oct_triggered() {
	m_c.setFormat(OCT);
	changeFormat(OCT);
}
