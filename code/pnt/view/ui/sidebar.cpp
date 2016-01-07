#include "sidebar.h"
#include "ui_sidebar.h"

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sidebar)
{
    ui->setupUi(this);

    // Don't know if this works... but we will see when we add it.
    ui->sidebarUiLayout->setAlignment(Qt::AlignTop);
}

Sidebar::~Sidebar()
{
    delete ui;
}
