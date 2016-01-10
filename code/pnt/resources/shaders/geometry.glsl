#version 410 core
//Variable in
layout( triangles ) in;
layout(location = 0) in vec3 tcsNormals[];

//Variable out
layout(location = 0) out vec3 gsNormal[3];
layout( line_strip, max_vertices = 6) out;

void passThrough(){
    gsNormal[0] = tcsNormals[0];
    gsNormal[1] = tcsNormals[1];
    gsNormal[2] = tcsNormals[2];
}

void main(void){
    passThrough();

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();
}
