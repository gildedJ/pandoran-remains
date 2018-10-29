#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

struct MovementComponent {
	glm::vec2 velocity;
	glm::vec2 acceleration;

	MovementComponent() : velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f) {}
	MovementComponent(GLfloat dx, GLfloat dy) : velocity(dx, dy), acceleration(0.0f, 0.0f) {}
	MovementComponent(glm::vec2 v) : velocity(v), acceleration(0.0f, 0.0f) {}
	MovementComponent(GLfloat dx, GLfloat dy, GLfloat ddx, GLfloat ddy) : velocity(dx, dy), acceleration(ddx, ddy) {}
	MovementComponent(glm::vec2 v, glm::vec2 a) : velocity(v), acceleration(a) {}
};