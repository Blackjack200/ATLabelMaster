#include "settings_dialog.hpp"
#include "controller/settings.hpp"
#include "ui_settings_dialog.h"
#include <qdialog.h>
#include <qfiledialog.h>
#include <qnamespace.h>
#include <qobject.h>
#include <qwidget.h>
using namespace ui;
SettingsDialog::SettingsDialog(QWidget* parent)
    : QDialog(parent)
    , ui_(new Ui::SettingsDialog) {
    ui_->setupUi(this);
    this->setWindowTitle("Settings");
    this->ui_->dataset_dir_edit->setText(controller::AppSettings::instance().saveDir());
    this->ui_->last_img_dir_edit->setText(controller::AppSettings::instance().lastImageDir());
    this->ui_->auto_save_checkbox->setChecked(controller::AppSettings::instance().autoSave());
    this->ui_->fix_roi_checkbox->setChecked(controller::AppSettings::instance().fixedRoi());
    this->ui_->roi_h_spin->setValue(controller::AppSettings::instance().roiH());
    this->ui_->roi_w_spin->setValue(controller::AppSettings::instance().roiW());
}
void SettingsDialog::setSaveDir() {
    const QString str = QFileDialog::getExistingDirectory();
    controller::AppSettings::instance().setsaveDir(str);
    update();
}
void SettingsDialog::setLastImageDir() {
    const QString str = QFileDialog::getExistingDirectory();
    controller::AppSettings::instance().setsaveDir(str);
    update();
}
void SettingsDialog::setAutoSave(bool isAutoSave) {
    controller::AppSettings::instance().setautoSave(isAutoSave);
    update();
}
void SettingsDialog::setFixedRoi(bool isFixedRoi) {
    controller::AppSettings::instance().setfixedRoi(isFixedRoi);
    update();
}
void SettingsDialog::setRoiH() {
    controller::AppSettings::instance().setroiH(this->ui_->roi_h_spin->value());
    update();
}
void SettingsDialog::setRoiW() {
    controller::AppSettings::instance().setroiW(this->ui_->roi_w_spin->value());
    update();
}
