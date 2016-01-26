#version 410 core

//Definitions
struct ControlNet {
    vec3 b210;
    vec3 b120;
    vec3 b021;
    vec3 b012;
    vec3 b102;
    vec3 b201;
    vec3 b111;
};


//Settings
layout(triangles) in;
layout(triangle_strip, max_vertices = 27) out;

//Uniform
uniform int interpolationMode;

//Variable in
layout(location = 0) in vec3 tesNormal[];
in ControlNet controlNet[];

//Variable out
layout(location = 0) out vec3 gsPosition;
layout(location = 1) out vec3 gsNormal;

void faceNormal(){
    vec3 edge1 = gl_in[1].gl_Position.xyz - gl_in[0].gl_Position.xyz;
    vec3 edge2 = gl_in[2].gl_Position.xyz - gl_in[0].gl_Position.xyz;

    vec3 meanNormal = (tesNormal[0] + tesNormal[1] + tesNormal[2]) / 3.0;
    gsNormal = normalize(cross(edge1, edge2));
//    if(dot(meanNormal, gsNormal) < 0) gsNormal = -1 * gsNormal;
//    if(dot(vec3(0, 0, -1), gsNormal) < 0) gsNormal = -1 * gsNormal;
}

void flatInterpolation(){
    faceNormal();
    for(int i = 0; i < 3; i++) {
    gsPosition = gl_in[i].gl_Position.xyz;
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
    }
    EndPrimitive();
}

//i.e. phongInterpolation
void smoothInterpolation(){
  for(int i = 0; i < 3; i++) {
        gsNormal = tesNormal[i];
        gsPosition = gl_in[i].gl_Position.xyz;
        gl_Position = gl_in[i].gl_Position;
        EmitVertex();
  }
  EndPrimitive();
}

void emitTriangle(vec3 vertexA, vec3 vertexB, vec3 vertexC){
    gl_Position = vec4(vertexA, 1.0);
    EmitVertex();

    gl_Position = vec4(vertexB, 1.0);
    EmitVertex();

    gl_Position = vec4(vertexC, 1.0);
    gsNormal = vertexC;
    EmitVertex();

    EndPrimitive();
}

void showGeometricComponent(){
    //No need to set gsPosition, or gsNormal per emitted vertex, since functions that use those are disabled if geometric component is shown
    gsPosition = vec3(1.0);
    gsNormal = vec3(1.0);
    emitTriangle(gl_in[0].gl_Position.xyz, controlNet[0].b201, controlNet[0].b210);
    emitTriangle(controlNet[0].b210, controlNet[0].b201, controlNet[0].b111);
    emitTriangle(controlNet[0].b210, controlNet[0].b111, controlNet[0].b120);
    emitTriangle(controlNet[0].b201, controlNet[0].b102, controlNet[0].b111);
    emitTriangle(controlNet[0].b120, controlNet[0].b111, controlNet[0].b021);
    emitTriangle(controlNet[0].b120, controlNet[0].b021, gl_in[1].gl_Position.xyz);
    emitTriangle(controlNet[0].b111, controlNet[0].b012, controlNet[0].b021);
    emitTriangle(controlNet[0].b111, controlNet[0].b102, controlNet[0].b012);
    emitTriangle(controlNet[0].b102, gl_in[2].gl_Position.xyz, controlNet[0].b012);
}

void main() {
    if(interpolationMode == 1) smoothInterpolation();
    if(interpolationMode == 2) flatInterpolation();
    if(interpolationMode == 3) showGeometricComponent();
    //if(interpolationMode == 4) //gouraud
}
