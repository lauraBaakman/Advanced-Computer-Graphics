#include "sidebar.h"
#include "ui_sidebar.h"

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sidebar)
{
    ui->setupUi(this);

    fillModelComboBox();

    fixLayout();
}

Sidebar::~Sidebar()
{
    delete ui;
}

void Sidebar::fixLayout()
{
    ui->sidebarUiLayout->setAlignment(Qt::AlignTop);
}

void Sidebar::on_renderModeComboBox_currentIndexChanged(int index)
{   // Note that the order of the combo box needs to be the same as the enum.
    emit renderModeChanged(static_cast<Settings::Render::Mode>(index));
}

void Sidebar::on_loadModelButton_clicked()
{
    emit modelChanged(ui->modelComboBox->currentText());
}

void Sidebar::fillModelComboBox()
{
    QList<QString> modelKeys = Settings::modelMap().keys();
    for (int i = 0; i < modelKeys.size(); i++)
    {
        ui->modelComboBox->addItem(modelKeys.at(i));
    }
}

void Sidebar::on_xDial_valueChanged(int value)
{
    emit rotationDialChanged(0, value);
}

void Sidebar::on_yDial_valueChanged(int value)
{
    emit rotationDialChanged(1, value);
}

void Sidebar::on_zDial_valueChanged(int value)
{
    emit rotationDialChanged(2, value);
}
