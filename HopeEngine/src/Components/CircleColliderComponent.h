#pragma once

#include <GL/glew.h>

struct CircleColliderComponent {
	GLfloat radius;

	CircleColliderComponent() : radius(0.0f) {}
	CircleColliderComponent(GLfloat _radius) : radius(_radius) {}
};