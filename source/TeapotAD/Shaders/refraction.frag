#version 430

in vec3 vertPos;
in vec3 N;

uniform vec3 cameraPos;
uniform samplerCube cubemap;



layout (location = 0) out vec4 FragColour;

void main()
{
   vec3 refractionVector = refract(normalize(vertPos - cameraPos), normalize(N), 0.5);
   FragColour = texture(cubemap, refractionVector);
}