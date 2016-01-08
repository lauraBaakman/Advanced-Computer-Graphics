#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include "settings/settings.h"

namespace Ui {
class Sidebar;
}

class Sidebar : public QWidget
{
    Q_OBJECT

public:
    explicit Sidebar(QWidget *parent = 0);
    ~Sidebar();

signals:
    void renderModeChanged(Settings::Render::Mode mode);

private slots:
    void on_renderModeComboBox_currentIndexChanged(int index);

private:
    Ui::Sidebar *ui;

    void fixLayout();

    void fillRenderUi();
};

#endif // SIDEBAR_H
