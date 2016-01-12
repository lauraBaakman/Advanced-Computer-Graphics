#version 410 core

//Variable in
layout(location = 0) in vec3 gsPosition;
layout(location = 1) in vec3 gsNormal;

//Variable out
out vec4 fColor;

void main(void)
{
    // fColor = vec4(vec3(1.0, 0.5, 0.0), 1.0);
    // fColor = vec4((gsNormal + vec3(1)) / 2.0, 1.0);
    fColor = vec4(gsNormal, 1.0);
}