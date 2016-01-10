#version 410 core
//Variable in
layout( triangles ) in;
layout(location = 0) in vec3 tesNormals[];

//Variable out
//layout(location = 0) out vec3 gsNormal[6];
layout( line_strip, max_vertices = 12) out;
layout( location = 0) out vec3 vertexColor;

// Uniform in
uniform mat4 mvpMatrix;

void passThrough(){
//    gsNormal[0] = tesNormals[0];
//    gsNormal[1] = tesNormals[1];
//    gsNormal[2] = tesNormals[2];
}

void emitTriangle(){
    vertexColor = vec3(1.0, 0.5, 0.0);
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();

    EndPrimitive();

    gl_Position = gl_in[1].gl_Position;
    EmitVertex();
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();

    EndPrimitive();

    gl_Position = gl_in[2].gl_Position;
    EmitVertex();
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    EndPrimitive();
}

void main(void){
    passThrough();

    vec4 point;
    vec3 normal;

    vertexColor = vec3(0.0, 0.0, 1.0);
    for(int i = 0; i < gl_in.length(); i++){
        point = gl_in[i].gl_Position;
        normal = tesNormals[i];

        gl_Position = point;
        EmitVertex();

        gl_Position = vec4(point.xyz + 0.1 * normalize(normal), 1.0);
        EmitVertex();

        EndPrimitive();


    }

    emitTriangle();
}
