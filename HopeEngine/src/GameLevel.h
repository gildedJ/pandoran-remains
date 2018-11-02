#pragma once

#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

#include <entityx/entityx.h>
using namespace entityx;

#include "ResourceManager.h"


/// GameLevel holds all Tiles as part of a Breakout level and 
/// hosts functionality to Load/render levels from the harddisk.
class GameLevel
{
public:
	// Constructor
	GameLevel() { }
	// Loads level from file
	void      Load(EntityManager& entityManager, const GLchar *file, GLuint levelWidth, GLuint levelHeight);
private:
	// Initialize level from tile data
	void      init(EntityManager& entityManager, std::vector<std::vector<GLuint>> tileData, GLuint levelWidth, GLuint levelHeight);
};
