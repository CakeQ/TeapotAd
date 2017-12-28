#version 430

layout (location = 0) in vec3 VertexPosition;

out vec3 TexCoords;



uniform mat4 M, V, P;

void main()
{
	gl_Position = P * V * M * vec4(VertexPosition, 1.0f); 
	TexCoords = vec3(inverse(M*V) * vec4(vec3(M * V* vec4(VertexPosition,1.0)), 0.0));
}
