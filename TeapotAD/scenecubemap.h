#ifndef SCENEDIFFUSE_H
#define SCENEDIFFUSE_H

#include "gl_core_4_3.hpp"

#include <glfw3.h>
#include "scene.h"
#include "glslprogram.h"

#include "vboteapot.h"
#include "vboplane.h"
#include "vbocube.h"

#include "Texture.h"

#include <glm.hpp>

using glm::mat4;


namespace imat3111
{
	class SceneCubeMap : public Scene
	{
	private:
		GLSLProgram prog;

		int width, height;

		VBOTeapot *teapot;  //Teapot VBO
		VBOCube *skyboxCube;

		VBOPlane *plane;  //Plane VBO

		mat4 model; //Model matrix

		Texture* gTexture;
		GLuint programHandle;

		void setMatrices(QuatCamera camera); //Set the camera matrices

		void compileAndLinkShader() {}; //Compile and link the shader

	public:
		SceneCubeMap(); //Constructor

		void setLightParams(QuatCamera camera) {}; //Setup the lighting

		void initScene(QuatCamera camera); //Initialise the scene

		void update(float t); //Update the scene

		void render(QuatCamera camera);	//Render the scene

		void resize(QuatCamera camera, int, int); //Resize
	};

}

#endif // SCENEDIFFUSE_H
