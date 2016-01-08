#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings/settings.h"
#include "view/ui/sidebar.h"
#include "view/canvas.h"
#include "controller/meshcontroller.h"
#include "model/mesh.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Settings *getSettings() const;
    void setSettings(Settings *value);

private:
    Ui::MainWindow *ui;
    Settings *settings;
    Sidebar *sidebar;
    Canvas *canvas;
    MeshController *controller;

    void fixLayout();
    void fixWindowSize();

    void connectUiToSettings();
    void connectUiToCanvas();
    void connectUiToModelController();
};

#endif // MAINWINDOW_H
