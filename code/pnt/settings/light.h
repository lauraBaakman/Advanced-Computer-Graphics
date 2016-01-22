#ifndef LIGHT
#define LIGHT

#include <QVector3D>

class Light {
public:
    QVector3D ambientIntensity;
    QVector3D diffuseIntensity;
    QVector3D specularIntensity;
    QVector3D position;

    Light(
            QVector3D ambientIntensity = QVector3D(1.0, 1.0, 1.0),
            QVector3D diffuseIntensity = QVector3D(1.0, 1.0, 1.0),
            QVector3D specularIntensity = QVector3D(1.0, 1.0, 1.0),
            QVector3D position = QVector3D(-2.0, 5.0, -10.0)
    );
};


inline Light::Light(QVector3D ambientIntensity, QVector3D diffuseIntensity, QVector3D specularIntensity, QVector3D position):
    ambientIntensity(ambientIntensity),
    diffuseIntensity(diffuseIntensity),
    specularIntensity(specularIntensity),
    position(position)
{
    //constructor body
}

#endif // LIGHT

