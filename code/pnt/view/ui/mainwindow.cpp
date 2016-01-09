#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fixLayout();
    fixWindowSize();

    this->settings = new Settings();
    this->sidebar = ui->sideBarWidget;
    this->canvas = ui->openGLWidget;
    this->controller = new MeshController();

    connectUiToSettings();
    connectUiToCanvas();
    connectUiToModelController();
    connectModelControllerToCanvas();
    connectSettingsToCanvas();
}

MainWindow::~MainWindow()
{
    delete controller;
    delete settings;
    delete ui;
}

Settings *MainWindow::getSettings() const
{
    return settings;
}

void MainWindow::setSettings(Settings *value)
{
    settings = value;
}

void MainWindow::fixLayout()
{
    ui->centralWidgetLayout->setAlignment(Qt::AlignLeft);
    ui->centralWidgetLayout->setAlignment(Qt::AlignTop);
}

/*
 * This are magical numbers, but I have no idea
 *   how to get the size of the other ui elements
 *   inside the MainWindow.
*/
void MainWindow::fixWindowSize()
{
    this->setFixedSize(1210, 824);
}

void MainWindow::connectUiToModelController()
{
    QObject::connect(this->settings, SIGNAL(modelChanged(QString)),
                     this->controller, SLOT(onModelChanged(QString)));
}

void MainWindow::connectModelControllerToCanvas()
{
    QObject::connect(this->controller, SIGNAL(modelChanged(Mesh*)),
                     this->canvas, SLOT(onModelChanged(Mesh*)));
}

void MainWindow::connectUiToSettings()
{
    QObject::connect(this->sidebar, SIGNAL(renderModeChanged(int)),
                     this->settings, SLOT(onRenderModeChanged(int)));

    QObject::connect(this->sidebar, SIGNAL(modelChanged(QString)),
                     this->settings, SLOT(onModelChanged(QString)));
}

void MainWindow::connectUiToCanvas()
{
    QObject::connect(this->sidebar, SIGNAL(rotationDialChanged(int,int)),
                     this->canvas, SLOT(onRotationDialChanged(int,int)));
}

void MainWindow::connectSettingsToCanvas()
{
    QObject::connect(this->settings, SIGNAL(renderModeChanged(Settings::Render::Mode)),
                     this->canvas, SLOT(onRenderModeChanged(Settings::Render::Mode)));
}

