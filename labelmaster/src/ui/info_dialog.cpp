#include "info_dialog.h"
#include "ui_info_dialog.h"
#include <qdialog.h>
#include <qglobal.h>
#include <qguiapplication_platform.h>
#include <qobject.h>
#include <qpoint.h>
#include <qscreen.h>
#include <qtmetamacros.h>
#include <qtransform.h>
#include <qwidget.h>
using namespace ui;
InfoDialog::InfoDialog(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::InfoDialog) {
    ui->setupUi(this);
    this->setWindowTitle("Edit Info");
};

InfoDialog::~InfoDialog() { delete this->ui; }
// 取消
void InfoDialog::reject() { this->done(1); }
// 确定
void InfoDialog::accept() {
    QString text = ui->comboBox->currentText();
    if (text == "Red") {
        text = "R";
    } else if (text == "Blue") {
        text = "B";
    } else if (text == "Purple") {
        text = "P";
    } else {
        text = "G";
    }
    emit InfoGetted(this->ui->lineEdit->text(), text, _isCurrent);
    this->done(1);
}
void InfoDialog::updateInfo(
    bool isCurrent, const QString& defaultClass, const QString& defaultColor) {
    QString Color;
    if (defaultColor == "R") {
        Color = "Red";
    } else if (defaultColor == "B") {
        Color = "Blue";
    } else if (defaultColor == "P") {
        Color = "Purple";
    } else {
        Color = "Gray";
    }
    _isCurrent = isCurrent;
    ui->comboBox->setCurrentText(Color);
    ui->lineEdit->setText(defaultClass);
}
