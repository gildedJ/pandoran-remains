#pragma once

#include <GL/glew.h>

struct HealthComponent {
	GLuint health;
	GLuint maxHealth;

	HealthComponent() : health(0), maxHealth(0) {}
	HealthComponent(int _health) : health(_health), maxHealth(_health) {}
};