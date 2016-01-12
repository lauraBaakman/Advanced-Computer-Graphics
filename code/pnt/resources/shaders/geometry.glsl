#version 410 core

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

//Definitions
subroutine void interpolationModelType();

//Variable in
layout(location = 0) in vec3 tesNormal[];

uniform subroutine interpolationModelType interpolationModel;

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

subroutine(interpolationModelType)
void flatInterpolation(){
	faceNormal();
	for(int i = 0; i < 3; i++) {
		gsPosition = gl_in[i].gl_Position.xyz;    
		gl_Position = gl_in[i].gl_Position;
		EmitVertex();
	}
	EndPrimitive();		
}

subroutine(interpolationModelType)
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

void main() {
	// flatInterpolation();
	// smoothInterpolation();
	interpolationModel();
}