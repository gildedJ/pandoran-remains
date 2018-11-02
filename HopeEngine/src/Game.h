#pragma once
#include <vector>
#include <tuple>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <entityx/entityx.h>

#include "GameLevel.h"

// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};

// Represents the four possible (collision) directions
enum Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT
};
// Defines a Collision typedef that represents collision data
typedef std::tuple<GLboolean, Direction, glm::vec2> Collision; // <collision?, what direction?, difference vector center - closest point>

// Game holds all game-related state and functionality.
// Combines all game-related data into a single class for
// easy access to each of the components and manageability.
class Game : public EntityX
{
public:
	// Game state
	GameState              State;
	GLboolean              Keys[1024];
	GLboolean              KeysProcessed[1024];
	GLuint                 Width, Height;
	std::vector<GameLevel> Levels;
	//std::vector<PowerUp>   PowerUps;
	GLuint                 Level;
	GLuint                 Lives;
	GLfloat				   FPS;
	// Constructor/Destructor
	Game(GLuint width, GLuint height);
	~Game();
	// Initialize game state (load all shaders/textures/levels)
	void Init();
	// GameLoop
	void ProcessInput(GLfloat dt);
	void Update(GLfloat dt);
	void Render();
	//void DoCollisions();
	// Reset
	//void ResetLevel();
	//void ResetPlayer();
	// Powerups
	//void SpawnPowerUps(GameObject &block);
	//void UpdatePowerUps(GLfloat dt);
};
