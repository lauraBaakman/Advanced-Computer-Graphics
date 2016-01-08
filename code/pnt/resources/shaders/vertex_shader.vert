#version 410

in vec3 vertex;
in vec3 normal;

//uniform mat4 mvpMatrix;
out vec4 vPosition;

void main(void)
{
    vPosition = vec4(vertex, 1.0);
}

