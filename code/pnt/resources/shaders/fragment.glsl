#version 410 core

//Variable in
layout(location = 0) in vec3 tesNormal;

//Variable out
out vec4 fColor;

void main(void)
{
    // fColor = vec4(vec3(1.0, 0.5, 0.0), 1.0);
    fColor = vec4((tesNormal + vec3(1)) / 2.0, 1.0);
}

