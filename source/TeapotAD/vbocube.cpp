#include "stdafx.h"
#include "vbocube.h"

#include <iostream>
#include <string>

#include "gl_core_4_3.hpp"
#include "Bitmap.h"

VBOCube::VBOCube(float fvert)
{
	faces = 6;

	float v[] =
	{
		-fvert, -fvert, -fvert,
		-fvert, fvert, -fvert,
		fvert, fvert, -fvert,
		fvert, -fvert, -fvert,

		-fvert, -fvert, fvert,
		-fvert, fvert, fvert,
		fvert, fvert, fvert,
		fvert, -fvert, fvert
	};

	unsigned int el[] = {
		0,1,2,
		0,2,3,
		0,4,1,
		4,5,1,
		4,5,6,
		4,6,7,
		3,2,6,
		3,6,7,
		1,2,5,
		2,5,6,
		0,7,3,
		0,7,4
	};

	GLuint handle[2];
	gl::GenBuffers(2, handle);
	gl::GenVertexArrays(1, &vaoHandle);
	gl::BindVertexArray(vaoHandle);
	gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
	gl::BufferData(gl::ARRAY_BUFFER, sizeof(v), v, gl::STATIC_DRAW);
	gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
	gl::EnableVertexAttribArray(0);
	gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, handle[1]);
	gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, sizeof(el), el, gl::STATIC_DRAW);
	gl::BindVertexArray(0);
	gl::GenTextures(1, &textureID);
	gl::BindTexture(gl::TEXTURE_CUBE_MAP, textureID);

	GLuint CubeMapFaces[6] =
	{
		gl::TEXTURE_CUBE_MAP_POSITIVE_X,
		gl::TEXTURE_CUBE_MAP_NEGATIVE_X,
		gl::TEXTURE_CUBE_MAP_POSITIVE_Y,
		gl::TEXTURE_CUBE_MAP_NEGATIVE_Y,
		gl::TEXTURE_CUBE_MAP_POSITIVE_Z,
		gl::TEXTURE_CUBE_MAP_NEGATIVE_Z,
	};

	for (GLint i = 0; i < faces; i++)
	{
		std::string TextureDir = "Images/cubemap" + std::to_string(i) + ".jpg";
		Bitmap bmp = Bitmap::bitmapFromFile(TextureDir);
		gl::TexImage2D
		(
			CubeMapFaces[i],
			0,
			gl::RGB,
			bmp.width(),
			bmp.height(),
			0,
			gl::RGB,
			gl::UNSIGNED_BYTE,
			bmp.pixelBuffer()
		);
	}

	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MAG_FILTER, gl::LINEAR);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_MIN_FILTER, gl::LINEAR);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_S, gl::CLAMP_TO_EDGE);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_T, gl::CLAMP_TO_EDGE);
	gl::TexParameterf(gl::TEXTURE_CUBE_MAP, gl::TEXTURE_WRAP_R, gl::CLAMP_TO_EDGE);
}

void VBOCube::render() const
{
	gl::BindVertexArray(vaoHandle);
	gl::DrawElements(gl::TRIANGLES, 6 * faces, gl::UNSIGNED_INT, ((GLubyte *)NULL + (0)));
}
