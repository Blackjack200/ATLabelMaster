
#include "ui_settings_dialog.h"
#include <qdialog.h>
#include <qfiledialog.h>
#include <qobject.h>
#include <qobjectdefs.h>
#include <qtmetamacros.h>
#include <qwidget.h>
namespace ui {
class SettingsDialog : public QDialog {
        Q_OBJECT
    public:
        SettingsDialog(QWidget* parent = nullptr);
        

    private:
        Ui::SettingsDialog* ui_;
    private slots:
        void accept() { this->done(1); }
        void reject() { this->done(1); }
    public slots:
        // void saveSettings();
        void setLastImageDir(); //上次图片目录
        void setSaveDir();//Label保存目录
        void setAutoSave(bool isAutoSave);//自动保存
        void setFixedRoi(bool isFixedRoi); //设置固定ROI
        void setRoiH();
        void setRoiW();
    };

} // namespace ui