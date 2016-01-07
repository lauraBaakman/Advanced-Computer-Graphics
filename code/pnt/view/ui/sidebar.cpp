#include "sidebar.h"
#include "ui_sidebar.h"

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sidebar)
{
    ui->setupUi(this);
    ui->sidebarUiLayout->setAlignment(Qt::AlignTop);
}

Sidebar::~Sidebar()
{
    delete ui;
}
