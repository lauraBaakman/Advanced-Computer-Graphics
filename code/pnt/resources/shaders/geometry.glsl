#version 410 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

//Variable in
layout(location = 0) in vec3 tesNormal[];

//Variable out
layout(location = 0) out vec3 gsPosition;
layout(location = 1) out vec3 gsNormal;

void passThrough(){
  for(int i = 0; i < 3; i++) {
    gsNormal = tesNormal[i];
	gsPosition = gl_in[i].gl_Position.xyz;    
    gl_Position = gl_in[i].gl_Position;
    EmitVertex();
  }
  EndPrimitive();	
}

void main() {
	passThrough();
}