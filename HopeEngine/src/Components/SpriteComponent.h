#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>

struct SpriteComponent {
	glm::vec2 size;
	glm::vec2 offset;
	glm::vec3 color;
	GLfloat   rotation;
	Texture2D texture;

	SpriteComponent(Texture2D _texture, glm::vec2 _size, glm::vec2 _offset, glm::vec2 _color, GLfloat _rotation) :
		texture(_texture), size(_size), offset(_offset), color(_color), rotation(_rotation) {}
	SpriteComponent(Texture2D _texture, glm::vec2 _size, glm::vec2 _offset) : texture(_texture), size(_size), offset(_offset), color(0.0f, 0.0f, 0.0f), rotation(0.0f) {}
	SpriteComponent(Texture2D _texture, glm::vec2 _size) : texture(_texture), size(_size), offset(0.0f, 0.0f), color(0.0f, 0.0f, 0.0f), rotation(0.0f) {}
};