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
    this->canvas->setSettings(this->settings);
    this->controller = new MeshController();

    connectUiToSettings();
    connectUiToCanvas();
    connectUiToModelController();
    connectModelControllerToCanvas();
    connectSettingsToCanvas();
    connectSettingsToUi();
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

    QObject::connect(this->sidebar, SIGNAL(shadingModeChanged(int)),
                     this->settings, SLOT(onShadingModeChanged(int)));

    QObject::connect(this->sidebar, SIGNAL(illuminationModeChanged(int)),
                     this->settings, SLOT(onIlluminationModeChanged(int)));

    QObject::connect(this->sidebar, SIGNAL(visualizeNormalsChanged(bool)),
                     this->settings, SLOT(onVisualizeNormalsChanged(bool)));

    QObject::connect(this->sidebar, SIGNAL(visualizeGeometryChanged(bool)),
                     this->settings, SLOT(onVisualizeGeometryChanged(bool)));

    QObject::connect(this->sidebar, SIGNAL(innerTessellationLevelChanged(float)),
                     this->settings, SLOT(onInnerTessellationLevelChanged(float)));

    QObject::connect(this->sidebar, SIGNAL(outerTessellationLevelChanged(float)),
                     this->settings, SLOT(onOuterTessellationLevelChanged(float)));

    QObject::connect(this->sidebar, SIGNAL(renderPnTrianglesChanged(bool)),
                     this->settings, SLOT(onRenderPnTrianglesChanged(bool)));

    QObject::connect(this->sidebar, SIGNAL(normalsChanged(int)),
                     this->settings, SLOT(onNormalsChanged(int)));
}

void MainWindow::connectUiToCanvas()
{
    QObject::connect(this->sidebar, SIGNAL(rotationDialChanged(int,int)),
                     this->canvas, SLOT(onRotationDialChanged(int,int)));
}

void MainWindow::connectSettingsToUi()
{
    QObject::connect(this->settings, SIGNAL(tessellationLevelsChanged(float,float)),
                     this->sidebar, SLOT(onTessellationLevelsChanged(float,float)));

    QObject::connect(this->settings, SIGNAL(normalCalculationChanged(int)),
                     this->sidebar, SLOT(onNormalCalculationChanged(int)));
}

void MainWindow::connectSettingsToCanvas()
{
    QObject::connect(this->settings, SIGNAL(settingsChanged()),
                     this->canvas, SLOT(onSettingsChanged()));
}

