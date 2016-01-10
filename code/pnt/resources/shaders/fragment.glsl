#version 410 core

//Variable in
layout(location = 0) in vec3 vertexColor;

//Variable out
out vec4 fColor;

void main(void)
{
     fColor = vec4(vertexColor, 1.0);
//    fColor = vec4(gsNormal, 1.0);
}

