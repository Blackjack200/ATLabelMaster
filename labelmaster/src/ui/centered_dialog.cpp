#include "centered_dialog.h"
#include <qdebug.h>
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
CenteredDialog::CenteredDialog(QWidget* parent)
    : QDialog(parent) {
    centerOnParent();
}
void CenteredDialog::centerOnParent() {
    QPoint dest;
    QWidget* parent = this->parentWidget();
    if (parent != nullptr) {
        auto hostRect = parent->rect();
        if (parent->parentWidget() != nullptr) {
            dest = parent->mapToGlobal(QPoint(0, 0)) + hostRect.center() - this->rect().center();
        } else {
            dest = parent->mapToGlobal(hostRect.center()) - this->rect().center();
        }
    } else {
        QRect screenGeometry = QGuiApplication::screens()[0]->geometry();
        int x                = (screenGeometry.width() - this->width()) / 2;
        int y                = (screenGeometry.height() - this->height()) / 2;
        dest                 = QPoint(x, y);
    }
    // this->move(dest);
}