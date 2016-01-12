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
    void renderModeChanged(int index);
    void modelChanged(QString modelKey);
    void rotationDialChanged(int axis, int value);

private slots:
    void on_renderModeComboBox_currentIndexChanged(int index);
    void on_loadModelButton_clicked();
    void on_xDial_valueChanged(int value);
    void on_yDial_valueChanged(int value);
    void on_zDial_valueChanged(int value);

    void on_visualizeNormalsCheckBox_clicked(bool checked);
    void on_outerTessellationSlider_sliderMoved(int position);
    void on_innerTessellationSlider_sliderMoved(int position);

    void on_shadingModeComboBox_currentIndexChanged(int index);

    void on_illuminationModeComboBox_currentIndexChanged(int index);

    void on_pnTrianglesUi_toggled(bool arg1);

private:
    Ui::Sidebar *ui;

    void fixLayout();
    void fillModelComboBox();

    void toggleShaderAndIlluminationUI(bool toggle);

    float innerTessellationMin, innerTessellationMax;
    float outerTessellationMin, outerTessellationMax;
    float mapToRange(int value, QPair<int, int> sourceRange, QPair<float, float> targetRange);

};

#endif // SIDEBAR_H
