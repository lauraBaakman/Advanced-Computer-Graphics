#version 410

// Variable in
layout(location = 0) in vec3 iPosition;
layout(location = 1) in vec3 iNormal;

// Variable out
//out vec3 vColor;

// Uniform in
uniform mat4 mvpMatrix;

//void passToFragment()
//{
//    vColor = iNormal;
//}

void setVertexPosition() {
    gl_Position = mvpMatrix * vec4(iPosition, 1.0);
}

void main(void)
{
//    passToFragment();
    setVertexPosition();
}

