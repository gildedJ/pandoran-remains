#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

#include <entityx/entityx.h>
using namespace entityx;

#include "../../Components/BoxColliderComponent.h"
#include "../../Components/MovementComponent.h"
#include "../../Components/PositionComponent.h"
#include "../../Components/SpriteComponent.h"
#include "../../Components/HealthComponent.h"

#include "../../ResourceManager.h"

namespace Player {

	// Initial size of the player paddle
	const vec2 SIZE(100.0f, 20.0f);
	// Initial velocity of the player paddle
	const GLfloat VELOCITY(500.0f);

	Entity Create(EntityManager& entityManager, vec2 position)
	{
		Entity player = entityManager.create();
		player.assign<PositionComponent>(position);
		player.assign<BoxColliderComponent>(position, position + Player::SIZE);
		player.assign<MovementComponent>();
		player.assign<SpriteComponent>(ResourceManager::GetTexture("paddle"), Player::SIZE);
		player.assign<HealthComponent>(3);
		return player;
	}
}