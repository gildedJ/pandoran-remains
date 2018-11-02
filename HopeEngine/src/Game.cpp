#include "pch.h"

#include <algorithm>
#include <sstream>

#include <irrKlang.h>
using namespace irrklang;

#include "game.h"
#include "ResourceManager.h"

#include "Systems/MovementSystem.h"
#include "Systems/SpriteRenderSystem.h"
#include "Systems/CollisionRenderSystem.h"

#include "Entity/Archetypes/Ball.h"
#include "Entity/Archetypes/Player.h"


// Game-related State data
ISoundEngine      *SoundEngine = createIrrKlangDevice();
GLfloat            ShakeTime = 0.0f;

Game::Game(GLuint width, GLuint height)
	: State(GAME_MENU), Keys(), Width(width), Height(height), Level(0), Lives(3), FPS(0.0f)
{

}

Game::~Game()
{
	SoundEngine->drop();
}

void Game::Init()
{
	// Load shaders
	ResourceManager::LoadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", nullptr, "sprite");
	ResourceManager::LoadShader("assets/shaders/wireframe.vert", "assets/shaders/wireframe.frag", nullptr, "wireframe");
	ResourceManager::LoadShader("assets/shaders/particle.vert", "assets/shaders/particle.frag", nullptr, "particle");
	ResourceManager::LoadShader("assets/shaders/post_processing.vert", "assets/shaders/post_processing.frag", nullptr, "postprocessing");
	// Configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(this->Width), static_cast<GLfloat>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);
	ResourceManager::GetShader("particle").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("particle").SetMatrix4("projection", projection);
	ResourceManager::GetShader("wireframe").Use().SetInteger("sprite", 0);
	ResourceManager::GetShader("wireframe").SetMatrix4("projection", projection);
	// Load textures
	ResourceManager::LoadTexture("assets/textures/background.jpg", GL_FALSE, "background");
	ResourceManager::LoadTexture("assets/textures/awesomeface.png", GL_TRUE, "face");
	ResourceManager::LoadTexture("assets/textures/block.png", GL_FALSE, "block");
	ResourceManager::LoadTexture("assets/textures/block_solid.png", GL_FALSE, "block_solid");
	ResourceManager::LoadTexture("assets/textures/paddle.png", GL_TRUE, "paddle");
	ResourceManager::LoadTexture("assets/textures/particle.png", GL_TRUE, "particle");
	ResourceManager::LoadTexture("assets/textures/powerup_speed.png", GL_TRUE, "powerup_speed");
	ResourceManager::LoadTexture("assets/textures/powerup_sticky.png", GL_TRUE, "powerup_sticky");
	ResourceManager::LoadTexture("assets/textures/powerup_increase.png", GL_TRUE, "powerup_increase");
	ResourceManager::LoadTexture("assets/textures/powerup_confuse.png", GL_TRUE, "powerup_confuse");
	ResourceManager::LoadTexture("assets/textures/powerup_chaos.png", GL_TRUE, "powerup_chaos");
	ResourceManager::LoadTexture("assets/textures/powerup_passthrough.png", GL_TRUE, "powerup_passthrough");
	// Set render-specific controls
	//Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));
	//Particles = new ParticleGenerator(ResourceManager::GetShader("particle"), ResourceManager::GetTexture("particle"), 500);
	//Effects = new PostProcessor(ResourceManager::GetShader("postprocessing"), this->Width, this->Height);
	//Text = new TextRenderer(this->Width, this->Height);
	//Text->Load("fonts/arial.TTF", 24);

	// Load levels
	GameLevel one; one.Load(entities, "assets/levels/01.lvl", this->Width, (GLuint)(this->Height * 0.5));
	//GameLevel two; two.Load(entities, "assets/levels/02.lvl", this->Width, (GLuint)(this->Height * (GLfloat)0.5));
	//GameLevel three; three.Load(entities, "assets/levels/03.lvl", this->Width, (GLuint)(this->Height * (GLfloat)0.5));
	//GameLevel four; four.Load(entities, "assets/levels/04.lvl", this->Width, (GLuint)(this->Height * (GLfloat)0.5));
	this->Levels.push_back(one);
	//this->Levels.push_back(two);
	//this->Levels.push_back(three);
	//this->Levels.push_back(four);
	this->Level = 0;

	// Configure game objects
	
	vec2 playerPos = vec2(this->Width / 2 - Player::SIZE.x / 2, this->Height - Player::SIZE.y);
	Player::Create(entities, playerPos);

	vec2 ballPos = playerPos + vec2(Player::SIZE.x / 2 - Ball::RADIUS, -Ball::RADIUS * 2);
	Ball::Create(entities, ballPos);

	// Systems
	systems.add<MovementSystem>(Width, Height);
	systems.add<SpriteRenderSystem>(ResourceManager::GetShader("sprite"));
	systems.add<BoxCollisionRenderSystem>(ResourceManager::GetShader("wireframe"));
	systems.configure();

	// Audio
	SoundEngine->play2D("assets/audio/breakout.mp3", GL_TRUE);
}

void Game::Update(GLfloat dt)
{
	systems.update_all(dt);
}


void Game::ProcessInput(GLfloat dt)
{
	if (this->State == GAME_MENU)
	{
		if (this->Keys[GLFW_KEY_ENTER] && !this->KeysProcessed[GLFW_KEY_ENTER])
		{
			this->State = GAME_ACTIVE;
			this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
		}
		if (this->Keys[GLFW_KEY_W] && !this->KeysProcessed[GLFW_KEY_W])
		{
			if (this->Level < 3)
				++this->Level;
			else
				this->Level = 0;
			this->KeysProcessed[GLFW_KEY_W] = GL_TRUE;
		}
		if (this->Keys[GLFW_KEY_S] && !this->KeysProcessed[GLFW_KEY_S])
		{
			if (this->Level > 0)
				--this->Level;
			else
				this->Level = 3;
			this->KeysProcessed[GLFW_KEY_S] = GL_TRUE;
		}
	}
	if (this->State == GAME_WIN)
	{
		if (this->Keys[GLFW_KEY_ENTER])
		{
			this->KeysProcessed[GLFW_KEY_ENTER] = GL_TRUE;
			//Effects->Chaos = GL_FALSE;
			this->State = GAME_MENU;
		}
	}
	//if (this->State == GAME_ACTIVE)
	//{
	//	GLfloat velocity = PLAYER_VELOCITY * dt;
	//	// Move playerboard
	//	if (this->Keys[GLFW_KEY_A])
	//	{
	//		if (Player->Position.x >= 0)
	//		{
	//			Player->Position.x -= velocity;
	//			if (Ball->Stuck)
	//				Ball->Position.x -= velocity;
	//		}
	//	}
	//	if (this->Keys[GLFW_KEY_D])
	//	{
	//		if (Player->Position.x <= this->Width - Player->Size.x)
	//		{
	//			Player->Position.x += velocity;
	//			if (Ball->Stuck)
	//				Ball->Position.x += velocity;
	//		}
	//	}
	//	if (this->Keys[GLFW_KEY_SPACE])
	//		Ball->Stuck = GL_FALSE;
	//}
}

void Game::Render()
{

}
