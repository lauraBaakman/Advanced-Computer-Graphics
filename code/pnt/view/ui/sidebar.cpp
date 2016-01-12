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
    // emit visualizeNormalsChanged(checked);
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

void Sidebar::on_outerTessellationSlider_sliderMoved(int position)
{
    float sliderValue = mapToRange(position,
            QPair<int, int>(this->innerTessellationMin, this->innerTessellationMax),
            Settings::innerTessellationRange);
    qDebug() << "Inner tessellation: " << sliderValue;
    ui->outerTessellationSliderLabel->setText(QString::number(sliderValue, 'g', 2));
}

void Sidebar::on_innerTessellationSlider_sliderMoved(int position)
{
    float sliderValue = mapToRange(position,
            QPair<int, int>(this->outerTessellationMin, this->outerTessellationMax),
            Settings::outerTessellationRange);
    qDebug() << "Outer tessellation: " << sliderValue;
    ui->innerTessellationSliderLabel->setText(QString::number(sliderValue, 'g', 2));
}

void Sidebar::on_shadingModeComboBox_currentIndexChanged(int index)
{ // To settings
//    emit shadingModeChanged(index);
}

void Sidebar::on_illuminationModeComboBox_currentIndexChanged(int index)
{ // To settings
//    emit illuminationModeChanged(index);
}

void Sidebar::on_pnTrianglesUi_toggled(bool toggle)
{
    qDebug() << "Toggle";
}
