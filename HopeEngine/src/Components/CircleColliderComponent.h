#pragma once

#include <GL/glew.h>

struct CircleColliderComponent {
	GLfloat radius;

	CircleColliderComponent(GLfloat _radius) : radius(_radius) {}
};