#include "sidebar.h"
#include "ui_sidebar.h"

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sidebar)
{
    ui->setupUi(this);
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

