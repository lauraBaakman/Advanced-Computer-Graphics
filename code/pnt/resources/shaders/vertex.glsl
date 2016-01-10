#version 410 core

// Variable in
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputNormal;

// Variable out
layout(location = 0) out vec3 vsNormals;

// Uniform in
uniform mat4 mvpMatrix;

void passThroughToFragmentShader()
{
//    vsNormals = inputNormal;
    vec4 temp = mvpMatrix * vec4(inputNormal, 1.0);
    vsNormals = temp.xyz;
}

void setVertexPosition() {
    gl_Position = mvpMatrix * vec4(inputPosition, 1.0);
}

void main(void)
{
    passThroughToFragmentShader();
    setVertexPosition();
}

