#version 430

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 vertPos;
out vec3 N;



uniform mat4 M, V, P;

void main()
{
   vertPos = vec3( M * vec4(VertexPosition,1.0));
   N = mat3(transpose(inverse(M))) * VertexNormal;
   gl_Position = P * V * M * vec4(VertexPosition,1.0);
}
