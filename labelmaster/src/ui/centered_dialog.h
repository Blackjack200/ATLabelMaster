#include <qdialog.h>
#include <qwidget.h>
#pragma once
namespace ui {
class CenteredDialog : public QDialog {
public:
    CenteredDialog(QWidget* parent = nullptr);
    void centerOnParent();
};
} // namespace ui