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

    connectUiToSettings();
}

MainWindow::~MainWindow()
{
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

void MainWindow::connectUiToSettings()
{
    QObject::connect(this->sidebar, SIGNAL(renderModeChanged(Settings::Render::Mode)),
                     this->settings, SLOT(onRenderModeChanged(Settings::Render::Mode)));

    QObject::connect(this->sidebar, SIGNAL(modelChanged(QString)),
                     this->settings, SLOT(onModelChanged(QString)));
}

