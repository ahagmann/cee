#include "about.h"
#include "ui_about.h"
#include "version.h"
#include <QDesktopServices>
#include <QUrl>

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

void About::on_label_linkActivated(const QString &link) {
	QDesktopServices::openUrl(QUrl("http://code.google.com/p/cee"));
}
