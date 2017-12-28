#include "stdafx.h"
#include "scenecubemap.h"

void imat3111::SceneCubeMap::setMatrices(QuatCamera camera, GLSLProgram * Shader)
{
	mat4 mv = camera.view() * model;
	Shader->setUniform("ModelViewMatrix", mv);
	Shader->setUniform("NormalMatrix", mat3(mv));
	Shader->setUniform("MVP", camera.projection() * mv);
	Shader->setUniform("M", model);
	Shader->setUniform("V", camera.view());
	Shader->setUniform("P", camera.projection());
	Shader->setUniform("cameraPos", camera.position());
}

void imat3111::SceneCubeMap::compileAndLinkShader()
{
	try {
		SkyShader.compileShader("Shaders/skybox.vert");
		SkyShader.compileShader("Shaders/skybox.frag");
		SkyShader.link();
		SkyShader.validate();
	}
	catch (GLSLProgramException & e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}

	try {
		Teapot1Shader.compileShader("Shaders/Teapot.vert");
		Teapot1Shader.compileShader("Shaders/reflection.frag");
		Teapot1Shader.link();
		Teapot1Shader.validate();
	}
	catch (GLSLProgramException & e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	/*
	try {
		Teapot2Shader.compileShader("Shaders/Teapot.vert");
		Teapot2Shader.compileShader("Shaders/refraction.frag");
		Teapot2Shader.link();
		Teapot2Shader.validate();
	}

	catch (GLSLProgramException & e) {
		std::cerr << e.what() << std::endl;
		exit(EXIT_FAILURE);
	}
	*/
}

void imat3111::SceneCubeMap::initScene(QuatCamera camera)
{
	compileAndLinkShader();
	gl::Enable(gl::DEPTH_TEST);

	setLightParams(camera);

	glm::mat4 lid = glm::mat4(1.0);

	teapot1 = new VBOTeapot(16, lid);
	//teapot2 = new VBOTeapot(16, lid);

	skyboxCube = new VBOCube(50.0f);
}

void imat3111::SceneCubeMap::setLightParams(QuatCamera camera)
{
	vec3 worldLight = vec3(10.0f, 10.0f, 10.0f);
}

void imat3111::SceneCubeMap::render(QuatCamera camera)
{
	gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);

	SkyShader.use();
	model = mat4(1.0f);
	setMatrices(camera, &SkyShader);
	skyboxCube->render();

	Teapot1Shader.use();
	model = mat4(1.0f);
	setMatrices(camera, &Teapot1Shader);
	teapot1->render();

	//Teapot2Shader.use();
	//model = mat4(1.0f);
	//setMatrices(camera, &Teapot2Shader);
	//teapot2->render();
}

void imat3111::SceneCubeMap::resize(QuatCamera camera, int w, int h)
{
	gl::Viewport(0, 0, w, h);
	width = w;
	height = h;
	camera.setAspectRatio((float)w / h);
}