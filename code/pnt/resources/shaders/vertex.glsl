#version 410

// Variable in
in vec3 iPosition;
in vec3 iNormal;

// Variable out
out vec3 vNormal;

// Uniform in
uniform mat4 mvpMatrix;

void passToFragment()
{
    vNormal = iNormal;
}

void setVertexPosition() {
    gl_Position = mvpMatrix * vec4(iPosition, 1.0);
}

void main(void)
{
    passToFragment();
    setVertexPosition();
}

