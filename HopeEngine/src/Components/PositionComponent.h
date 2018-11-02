#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

struct PositionComponent {
	vec2 position;

	PositionComponent() : position(0.0f, 0.0f) {}
	PositionComponent(GLfloat x, GLfloat y) : position(x, y) {}
	PositionComponent(vec2 pos) : position(pos) {}
};