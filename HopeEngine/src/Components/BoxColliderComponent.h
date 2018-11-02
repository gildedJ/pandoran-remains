#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

struct BoxColliderComponent {
	vec2 topLeft;
	vec2 bottomRight;

	BoxColliderComponent() : topLeft(0.0f, 0.0f), bottomRight(0.0f, 0.0f) {}
	BoxColliderComponent(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) : topLeft(x1, y1), bottomRight(x2, y2) {}
	BoxColliderComponent(vec2 _topLeft, vec2 _bottomRight) : topLeft(_topLeft), bottomRight(_bottomRight) {}
};