#version 410

in vec3 vNormal;

out vec4 fColor;

void main(void)
{
    fColor = vec4(vNormal, 1.0);
}

