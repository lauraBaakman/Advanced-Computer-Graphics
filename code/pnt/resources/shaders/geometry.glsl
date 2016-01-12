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
layout(triangle_strip, max_vertices = 3) out;

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
    if(dot(meanNormal, gsNormal) < 0) gsNormal = normalize(cross(edge2, edge1));
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

void showGeometricComponent(){
    smoothInterpolation();
}

void main() {
    // if(interpolationMode == 1) smoothInterpolation();
    // if(interpolationMode == 2) flatInterpolation();
//    if(interpolationMode == 3) //gouraud
    showGeometricComponent();
}
