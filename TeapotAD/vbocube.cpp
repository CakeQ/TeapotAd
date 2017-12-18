#include "stdafx.h"
#include "vbocube.h"

#include <iostream>
#include <string>

#include "gl_core_4_3.hpp"
#include "Bitmap.h"

VBOCube::VBOCube(float fvert)
{
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

}
