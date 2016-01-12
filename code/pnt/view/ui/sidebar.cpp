#include "sidebar.h"
#include "ui_sidebar.h"

Sidebar::Sidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sidebar)
{
    ui->setupUi(this);

    fillModelComboBox();
    fixLayout();

    this->innerTessellationMin = ui->innerTessellationSlider->minimum();
    this->innerTessellationMax = ui->innerTessellationSlider->maximum();

    this->outerTessellationMin = ui->outerTessellationSlider->minimum();
    this->outerTessellationMax = ui->outerTessellationSlider->maximum();
}

Sidebar::~Sidebar()
{
    delete ui;
}

void Sidebar::onTessellationLevelsChanged(float inner, float outer)
{
    ui->innerTessellationSlider->setValue(mapToRange(inner, Settings::innerTessellationRange, QPair<int, int>(this->innerTessellationMin, this->innerTessellationMax)));
    ui->innerTessellationSliderLabel->setText(QString::number(inner, 'g', 2));

    ui->outerTessellationSlider->setValue(mapToRange(outer, Settings::outerTessellationRange, QPair<int, int>(this->outerTessellationMin, this->outerTessellationMax)));
    ui->outerTessellationSliderLabel->setText(QString::number(outer, 'g', 2));
}

void Sidebar::fixLayout()
{
    ui->sidebarUiLayout->setAlignment(Qt::AlignTop);
}

void Sidebar::fillModelComboBox()
{
    QList<QString> modelKeys = Settings::modelMap().keys();
    for (int i = 0; i < modelKeys.size(); i++)
    {
        ui->modelComboBox->addItem(modelKeys.at(i));
    }
}

void Sidebar::on_renderModeComboBox_currentIndexChanged(int index)
{
    emit renderModeChanged(index);
}

void Sidebar::on_loadModelButton_clicked()
{
    emit modelChanged(ui->modelComboBox->currentText());
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

void Sidebar::on_visualizeNormalsCheckBox_clicked(bool checked)
{
    toggleShaderAndIlluminationUI(checked);
    emit visualizeNormalsChanged(checked);
}

void Sidebar::toggleShaderAndIlluminationUI(bool toggle)
{
    toggle = !toggle;
    ui->illuminationModeComboBox->setEnabled(toggle);
    ui->illuminationModeComboBoxLabel->setEnabled(toggle);
    ui->shadingModeComboBox->setEnabled(toggle);
    ui->ShadingModeComboBoxLabel->setEnabled(toggle);
}

float Sidebar::mapToRange(int value, QPair<int, int> sourceRange, QPair<float, float> targetRange)
{
    float sourceRatio = static_cast<float>(sourceRange.second - sourceRange.first);
    float targetRatio = targetRange.second - targetRange.first;

    return (((static_cast<float>(value) - sourceRange.first) * targetRatio) / sourceRatio) + targetRange.first;
}

int Sidebar::mapToRange(float value, QPair<float, float> sourceRange, QPair<int, int> targetRange)
{
    float sourceRatio = sourceRange.second - sourceRange.first;
    float targetRatio = static_cast<float>(targetRange.second - targetRange.first);

    return static_cast<int>((((value - sourceRange.first) * targetRatio) / sourceRatio) + static_cast<float>(targetRange.first));
}

void Sidebar::on_innerTessellationSlider_valueChanged(int position)
{
    float sliderValue = mapToRange(position,
            QPair<int, int>(this->outerTessellationMin, this->outerTessellationMax),
            Settings::outerTessellationRange);
    ui->innerTessellationSliderLabel->setText(QString::number(sliderValue, 'g', 2));

    emit outerTessellationLevelChanged(sliderValue);
}

void Sidebar::on_outerTessellationSlider_valueChanged(int position)
{
    float sliderValue = mapToRange(position,
            QPair<int, int>(this->innerTessellationMin, this->innerTessellationMax),
            Settings::innerTessellationRange);
    ui->outerTessellationSliderLabel->setText(QString::number(sliderValue, 'g', 2));

    emit innerTessellationLevelChanged(sliderValue);
}

void Sidebar::on_shadingModeComboBox_currentIndexChanged(int index)
{
    emit shadingModeChanged(index);
}

void Sidebar::on_illuminationModeComboBox_currentIndexChanged(int index)
{
    emit illuminationModeChanged(index);
}

void Sidebar::on_pnTrianglesUi_toggled(bool toggle)
{
    emit renderPnTrianglesChanged(toggle);
}

void Sidebar::on_visualizeGeometricCompCheckBox_clicked(bool checked)
{
    bool toggle = !checked;
    ui->tesselationLevelLabel->setEnabled(toggle);

    // Inner tessellation ui
    ui->innerTessellationLevelLabel->setEnabled(toggle);
    ui->innerTessellationSlider->setEnabled(toggle);
    ui->innerTessellationSliderLabel->setEnabled(toggle);

    // Outer tessellation ui
    ui->outerTessellationLevelLabel->setEnabled(toggle);
    ui->outerTessellationSlider->setEnabled(toggle);
    ui->outerTessellationSliderLabel->setEnabled(toggle);

    emit visualizeGeometryChanged(checked);
}
