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

		VBOCube *skyboxCube;
		GLSLProgram SkyShader;

		VBOTeapot *teapot1;
		//VBOTeapot *teapot2;

		GLSLProgram Teapot1Shader;
		//GLSLProgram Teapot2Shader;

		int width, height;

		mat4 model; //Model matrix

		Texture* gTexture;
		GLuint programHandle;

		void setMatrices(QuatCamera camera, GLSLProgram* Shader); //Set the camera matrices

		void compileAndLinkShader(); //Compile and link the shader

	public:
		static bool reflection;

		SceneCubeMap() {};

		void setLightParams(QuatCamera camera); //Setup the lighting

		void initScene(QuatCamera camera); //Initialise the scene

		void update(float t) {}; //Update the scene

		void render(QuatCamera camera);	//Render the scene

		void resize(QuatCamera camera, int w, int h); //Resize

		void swapReflection()
		{
			if (reflection)
			{
				reflection = false;
			}
			else
			{
				reflection = true;
			}

			compileAndLinkShader();
		};
	};
}

#endif // SCENECUBEMAP_H
