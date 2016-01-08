attribute vec3 vertex;
attribute vec3 normal;

uniform mat4 mvpMatrix;

void main(void)
{
    gl_Position = mvpMatrix * vec4(vertex, 1.0);
}

