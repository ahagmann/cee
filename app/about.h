#ifndef ABOUT_H
#define ABOUT_H

#include <QDialog>

namespace Ui {
    class About;
}

class About : public QDialog {
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

private slots:
	void on_pushButton_released();

	void on_label_linkActivated(const QString &link);

private:
    Ui::About *ui;
};

#endif
