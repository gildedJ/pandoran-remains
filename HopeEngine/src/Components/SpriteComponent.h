#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

#include "../Renderer/Texture.h"
#include "../ResourceManager.h"

struct SpriteComponent {
	vec2	  size;
	vec2	  offset;
	vec3	  color;
	GLfloat   rotation;
	Texture2D& texture;

	SpriteComponent() : texture(ResourceManager::GetTexture("face")), size(0.0f, 0.0f), offset(0.0f, 0.0f), color(1.0f, 1.0f, 1.0f), rotation(0.0f) {}
	SpriteComponent(Texture2D& _texture, vec2 _size, vec2 _offset, vec3 _color, GLfloat _rotation) :
		texture(_texture), size(_size), offset(_offset), color(_color), rotation(_rotation) {}
	SpriteComponent(Texture2D& _texture, vec2 _size, vec2 _offset, vec3 _color) : texture(_texture), size(_size), offset(_offset), color(_color), rotation(0.0f) {}
	SpriteComponent(Texture2D& _texture, vec2 _size, vec2 _offset) : texture(_texture), size(_size), offset(_offset), color(1.0f, 1.0f, 1.0f), rotation(0.0f) {}
	SpriteComponent(Texture2D& _texture, vec2 _size) : texture(_texture), size(_size), offset(0.0f, 0.0f), color(1.0f, 1.0f, 1.0f), rotation(0.0f) {}
};