#include "controller/settings.hpp"
#include "detector/smart_detector.hpp"
#include "logger/core.hpp"
#include "service/file.hpp"
#include "types.hpp"
#include "ui/image_canvas.hpp"
#include "ui/info_dialog.h"
#include "ui/mainwindow.hpp"
#include <QApplication>
#include <QFile>
#include <pthread.h>
#include <qapplication.h>
#include <qglobal.h>
#include <qobject.h>
#include <qtmetamacros.h>

#define ASSETS_PATH "/home/developer/ws/assets"

int main(int argc, char* argv[]) {
    // 1) 初始化应用配置系统(在 QApplication 之前，否则会Unknown Organization)
    // 2) 安装 Qt 的全局消息处理器，尽早捕获日志
    controller::AppSettings::initOrgApp("LabelMaster.org", "LabelMasterOrg", "LabelMasterApp");
    QApplication app(argc, argv);
    logger::Logger::installQtHandler();
    ui::MainWindow w;
    FileService files;
    rm_auto_aim::Detector::LightParams lp;
    rm_auto_aim::Detector::ArmorParams ap;
    SmartDetector detector{&w};
    // if (QFile::exists(assets_dir)) {
    //     QString model_path = assets_dir + "/models/mlp.onnx";
    //     QString label_path = assets_dir + "/models/label.txt";
    //     controller::AppSettings::instance();
    //     detector.resetNumberClassifier(
    //         model_path, label_path,
    //         controller::AppSettings::instance().numberClassifierThreshold());
    // } else {
    //     qWarning() << "Assets directory not found: " << assets_dir;
    // }

    // MainWindow <-> FileService 其他连接保持
    QObject::connect(&w, &ui::MainWindow::sigOpenFolderRequested, &files, [&]() {
        files.openFolderDialog(DataSet::LabelMaster);
    });
    QObject::connect(
        &w, &ui::MainWindow::sigImportFolderRequested, &files, &FileService::importFrom);
    QObject::connect(&w, &ui::MainWindow::sigFileActivated, &files, &FileService::openIndex);
    QObject::connect(&w, &ui::MainWindow::sigDroppedPaths, &files, &FileService::openPaths);
    QObject::connect(&w, &ui::MainWindow::sigNextRequested, &files, &FileService::next);
    QObject::connect(&w, &ui::MainWindow::sigPrevRequested, &files, &FileService::prev);
    QObject::connect(&w, &ui::MainWindow::sigDeleteRequested, &files, &FileService::deleteCurrent);
    QObject::connect(&w, &ui::MainWindow::sigGetStasRequested, &files, &FileService::getStas);
    QObject::connect(
        &w, &ui::MainWindow::sigSettingsRequested, &w, &ui::MainWindow::showSettingDialog);
    QObject::connect(&files, &FileService::modelReady, &w, &ui::MainWindow::setFileModel);
    QObject::connect(&files, &FileService::rootChanged, &w, &ui::MainWindow::setRoot); // ★ 新增
    QObject::connect(
        &files, &FileService::currentIndexChanged, &w, &ui::MainWindow::setCurrentIndex);
    QObject::connect(&files, &FileService::imageReady, &w, &ui::MainWindow::showImage);
    QObject::connect(&files, &FileService::status, &w, &ui::MainWindow::setStatus);
    QObject::connect(&files, &FileService::busy, &w, &ui::MainWindow::setBusy);
    QObject::connect(&files, &FileService::StasGetted, &w, &ui::MainWindow::sigStasUpdateRequested);
    QObject::connect(
        &w, &ui::MainWindow::sigHistEqRequested, w.ui()->label, &ImageCanvas::histEqualize);
    // ImageCanvas <-> SmartDetector 连接 检测和检测结果
    QObject::connect(
        w.ui()->label, &ImageCanvas::detectRequested, &detector, &SmartDetector::detect);
    QObject::connect(
        &detector, &SmartDetector::detected, w.ui()->label, &ImageCanvas::setDetections);
    QObject::connect(
        &files, &FileService::labelsLoaded, w.ui()->label, &ImageCanvas::setDetections);
    QObject::connect(
        w.ui()->label, &ImageCanvas::annotationsPublished, &files, &FileService::saveData);
    files.exposeModel();
    w.enableDragDrop(true);
    w.show();
    LOGI("App started");
    return app.exec();
}
