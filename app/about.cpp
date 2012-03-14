#include "about.h"
#include "ui_about.h"
#include "version.h"

About::About(QWidget *parent) : QDialog(parent), ui(new Ui::About) {
    ui->setupUi(this);

	ui->versionLabel->setText(QString("Version ") + VERSION_STRING);
}

About::~About() {
    delete ui;
}

void About::on_pushButton_released() {
	close();
}
