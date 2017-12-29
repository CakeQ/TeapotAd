#ifndef SCENECUBEMAP_H
#define SCENECUBEMAP_H

#include "gl_core_4_3.hpp"

#include <glfw/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "scene.h"
#include "glslprogram.h"

#include "vboteapot.h"
#include "vboplane.h"
#include "vbocube.h"

#include "Texture.h"

#include <glm/glm.hpp>

using glm::mat4;


namespace imat3111
{
	class SceneCubeMap : public Scene
	{
	private:

		VBOCube *skyboxCube;										//Cube Map object.
		GLSLProgram SkyShader;										//Shader used for cube map.
		VBOTeapot *teapot;											//Teapot object.
		GLSLProgram Teapot1Shader;									//Reflection shader for teapot.
		GLSLProgram Teapot2Shader;									//Refraction shader for teapot.
		static bool UsingReflection;								//Boolean for using reflection or refraction.
		int width, height;											//Camera sizes.
		mat4 model;													//Model matrix.
		void setMatrices(QuatCamera camera, GLSLProgram* Shader);	//Set the camera matrices.
		void compileAndLinkShader();								//Compile and link the shader.

	public:
		SceneCubeMap() { UsingReflection = true; };					//Initialise boolean.
		void setLightParams(QuatCamera camera);						//Setup the lighting.
		void initScene(QuatCamera camera);							//Initialise the scene.
		void update(float t) {};									//Update the scene.
		void render(QuatCamera camera);								//Render the scene.
		void resize(QuatCamera camera, int w, int h);				//Resize the camera.
		void swapReflection()										//Swap between reflection and refraction.
		{
			if (UsingReflection)
			{
				UsingReflection = false;
			}
			else
			{
				UsingReflection = true;
			}
		};
	};
}

#endif // SCENECUBEMAP_H
