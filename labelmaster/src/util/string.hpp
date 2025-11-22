#pragma once
#include <QBuffer>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QFileSystemModel>
#include <QImage>
#include <QImageReader>
#include <QQueue>
#include <QSettings>
#include <QSortFilterProxyModel>
#include <QTextStream>
#include <QTimer>
#include <QUrl>
#include <cmath>
#include <qabstractitemmodel.h>
#include <qbuffer.h>
#include <qdebug.h>
#include <qdir.h>
#include <qglobal.h>
#include <qhashfunctions.h>
#include <qiodevicebase.h>
#include <qlist.h>
#include <qmath.h>
#include <qnamespace.h>
#include <qpointer.h>
#include <qsettings.h>
#include <qsortfilterproxymodel.h>
#include <qstringalgorithms.h>
#include <qtmetamacros.h>
namespace StringProcess {
inline bool processLabelString(QString raw, QStringList& result) {
    int hash = raw.indexOf('#');
    if (hash >= 0)
        raw = raw.left(hash);
    const QString line = raw.trimmed();
    if (line.isEmpty())
        return false;
    const QStringList list = line.simplified().split(' ');
    if (list.size() != 10)
        return false;
    result = list;
    return true;
}
} // namespace StringProcess