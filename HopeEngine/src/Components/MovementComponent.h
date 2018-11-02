#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

struct MovementComponent {
	vec2 velocity;
	vec2 acceleration;
	GLfloat dragCoefficient;

	MovementComponent() : velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f), dragCoefficient(1.0f) {}
	MovementComponent(GLfloat dx, GLfloat dy) : velocity(dx, dy), acceleration(0.0f, 0.0f), dragCoefficient(1.0f) {}
	MovementComponent(vec2 v) : velocity(v), acceleration(0.0f, 0.0f), dragCoefficient(1.0f) {}
	MovementComponent(GLfloat dx, GLfloat dy, GLfloat ddx, GLfloat ddy) : velocity(dx, dy), acceleration(ddx, ddy), dragCoefficient(1.0f) {}
	MovementComponent(vec2 v, vec2 a) : velocity(v), acceleration(a), dragCoefficient(1.0f) {}
	MovementComponent(GLfloat dx, GLfloat dy, GLfloat ddx, GLfloat ddy, GLfloat drag) : velocity(dx, dy), acceleration(ddx, ddy), dragCoefficient(drag) {}
	MovementComponent(vec2 v, vec2 a, GLfloat drag) : velocity(v), acceleration(a), dragCoefficient(drag) {}
};