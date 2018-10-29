#pragma once

#include <GL/glew.h>

struct BallComponent {
	GLboolean stuck;
	GLboolean sticky, passThrough;

	BallComponent() : stuck(GL_FALSE), sticky(GL_FALSE), passThrough(GL_FALSE) {}
};