#version 430

in vec3 TexCoords;

out vec4 color;



uniform samplerCube cubemap;

void main(){
	color = texture(cubemap, TexCoords); 
}
