#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>


struct BoxColliderComponent {
	glm::vec2 topLeft;
	glm::vec2 bottomRight;

	BoxColliderComponent(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2) : topLeft(x1, y1), bottomRight(x2, y2) {}
	BoxColliderComponent(glm::vec2 _topRight, glm::vec2 _bottomRight) : topLeft(_topLeft), bottomRight(_bottomRight) {}
};