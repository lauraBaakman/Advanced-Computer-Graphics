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

public slots:
    void onTessellationLevelsChanged(float inner, float outer);
    void onNormalCalculationChanged(int index);
    void onRenderUiChanged(int renderIndex, int shadingIndex, int illuminationIndex, bool visualizeNormals);

signals:
    void renderModeChanged(int index);
    void modelChanged(QString modelKey);
    void rotationDialChanged(int axis, int value);
    void shadingModeChanged(int index);
    void illuminationModeChanged(int index);
    void visualizeNormalsChanged(bool toggle);
    void innerTessellationLevelChanged(float value);
    void outerTessellationLevelChanged(float value);
    void visualizeGeometryChanged(bool toggle);
    void renderPnTrianglesChanged(bool toggle);
    void normalsChanged(int index);

private slots:
    void on_renderModeComboBox_currentIndexChanged(int index);
    void on_loadModelButton_clicked();
    void on_xDial_valueChanged(int value);
    void on_yDial_valueChanged(int value);
    void on_zDial_valueChanged(int value);

    void on_visualizeNormalsCheckBox_clicked(bool checked);
    void on_innerTessellationSlider_valueChanged(int value);
    void on_outerTessellationSlider_valueChanged(int value);

    void on_shadingModeComboBox_currentIndexChanged(int index);
    void on_illuminationModeComboBox_currentIndexChanged(int index);
    void on_pnTrianglesUi_toggled(bool arg1);
    void on_visualizeGeometricCompCheckBox_clicked(bool checked);

    void on_normalComboBox_currentIndexChanged(int index);

private:
    Ui::Sidebar *ui;

    void fixLayout();
    void fillModelComboBox();

    void toggleShaderAndIlluminationUI(bool toggle);

    int innerTessellationMin, innerTessellationMax;
    int outerTessellationMin, outerTessellationMax;
    float mapToRange(int value, QPair<int, int> sourceRange, QPair<float, float> targetRange);
    int mapToRange(float value, QPair<float, float> sourceRange, QPair<int, int> targetRange);

};

#endif // SIDEBAR_H
