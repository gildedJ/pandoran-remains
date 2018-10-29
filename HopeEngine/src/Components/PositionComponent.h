#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

struct PositionComponent {
	glm::vec2 position;

	PositionComponent(GLfloat x, GLfloat y) : position(x, y) {}
	PositionComponent(glm::vec2 pos) : position(pos) {}
};