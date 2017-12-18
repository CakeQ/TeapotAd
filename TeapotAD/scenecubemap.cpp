#include "stdafx.h"
#include "scenecubemap.h"

void imat3111::SceneCubeMap::initScene(QuatCamera camera)
{
	compileAndLinkShader();
	gl::Enable(gl::DEPTH_TEST);

	setLightParams(camera);

	glm::mat4 lid = glm::mat4(1.0);

	teapot = new VBOTeapot(16, lid);

	skyboxCube = new VBOCube(50.0f);
}
