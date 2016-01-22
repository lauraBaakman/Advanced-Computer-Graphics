#ifndef MATERIAL_H
#define MATERIAL_H

#include <QVector3D>

class Material {
public:
    float specularReflectionConstant;
    float diffuseReflectionConstant;
    float ambientReflectionConstant;
    float alfa;
    QVector3D color;

    Material(
            float specularReflectionConstant = 0.3,
            float diffuseReflectionConstant = 0.5,
            float ambientReflectionConstant = 0.4,
            float alfa = 150.0,
            QVector3D color = QVector3D(252.0/255.0, 0.0, 109.0/255.0)
    );
};


inline Material::Material(
        float specularReflectionConstant,
        float diffuseReflectionConstant,
        float ambientReflectionConstant,
        float alfa,
        QVector3D color
        ):
    specularReflectionConstant(specularReflectionConstant),
    diffuseReflectionConstant(diffuseReflectionConstant),
    ambientReflectionConstant(ambientReflectionConstant),
    alfa(alfa),
    color(color)
{
    //constructor body
}

#endif // MATERIAL_H

