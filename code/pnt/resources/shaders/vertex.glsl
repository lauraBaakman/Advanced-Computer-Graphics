#version 410 core

// Variable in
layout(location = 0) in vec3 inputPosition;
layout(location = 1) in vec3 inputNormal;

// Variable out
layout(location = 0) out vec3 vsNormals;

// Uniform in
uniform mat4 mvpMatrix;
uniform mat3 normalMatrix;

void passThroughToFragmentShader()
{
//    vsNormals = inputNormal;
    vsNormals = normalize(normalMatrix * inputNormal);
}

void setVertexPosition() {
    gl_Position = mvpMatrix * vec4(inputPosition, 1.0);
}

void main(void)
{
    passThroughToFragmentShader();
    setVertexPosition();
}

