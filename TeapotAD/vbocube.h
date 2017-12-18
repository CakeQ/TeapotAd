#ifndef VBOCUBE_H
#define VBOCUBE_H

#include "drawable.h"
#include "gl_core_4_3.hpp"

class VBOCube : public Drawable
{
private:
	unsigned int vaoHandle;
	int faces;
	GLuint textureID;

public:
	VBOCube(float fvert);

	void render() const;
};

#endif // VBOPLANE_H
