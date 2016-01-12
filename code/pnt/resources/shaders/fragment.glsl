#version 410 core

//Definitions
struct MaterialInfo {
    float specularReflectionConstant;
    float diffuseReflectionConstant;
    float ambientReflectionConstant;
    float alfa;
    vec3 color;
};

struct LightInfo {
    vec3 position;
    vec3 ambientLightIntensity;
    vec3 diffuseLightIntensity;
    vec3 specularLightIntensity;
};

subroutine void reflectionModelType();

//Variable in
layout(location = 0) in vec3 gsPosition;
layout(location = 1) in vec3 gsNormal;

uniform LightInfo light;
uniform MaterialInfo material;
uniform subroutine reflectionModelType reflectionModel;

//Variable out
out vec4 fColor;

//globals
vec3 eye = vec3(2.0, 5.0, -10.0);

vec3 makeUnitVectorAColor(vec3 vector){
	return (gsNormal + vec3(1)) / 2.0;
}

//Set the correct function pointer with: 
//functionIndex = glGetSubroutineIndex(ShaderProgam->programId(), GL_FRAGMENT_SHADER, "phongReflection");
//glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &functionIndex);

vec3 frontLightMaterial(float reflectionConstant, vec3 color, vec3 light)
{
    return clamp(light * (reflectionConstant * color), 0, 1);
}

subroutine(reflectionModelType)
void phongReflection(){
    vec3 viewVector = normalize(eye - gsPosition);
    vec3 lightVector = normalize(light.position - gsPosition);
    vec3 reflectionVector = normalize(reflect(-lightVector, gsNormal));	

    vec3 ambient = frontLightMaterial(
                material.ambientReflectionConstant,
                material.color,
                light.ambientLightIntensity);    

    float diffuseDotProduct = dot(gsNormal, lightVector);
    vec3 diffuse = frontLightMaterial(
                material.diffuseReflectionConstant,
                material.color,
                light.diffuseLightIntensity)
            * max(diffuseDotProduct, 0.0);    

    //TODO werk if eruit        
    vec3 specular;
    if(diffuseDotProduct > 0){
        specular = frontLightMaterial(
                    material.specularReflectionConstant,
                    material.color,
                    light.specularLightIntensity)
                * pow( max(dot(reflectionVector, viewVector), 0.0 ), material.alfa);
    }
    vec3 phongColor = clamp(ambient + diffuse + specular, 0, 1);         
    fColor = vec4(phongColor, 1.0);
}

subroutine(reflectionModelType)
void visualizeNormals(){
    fColor = vec4(makeUnitVectorAColor(normalize(gsNormal)), 1.0);	
}

subroutine(reflectionModelType)
void noShading(){
	fColor = vec4(1.0, 0.0, 0.0, 1.0);
}

void main(void)
{
    // phongReflection();
    // visualizeNormals();
    // noShading();
    reflectionModel();
}