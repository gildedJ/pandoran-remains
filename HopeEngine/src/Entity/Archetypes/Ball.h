#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

#include <entityx/entityx.h>
using namespace entityx;

#include "../../Components/BallComponent.h"
#include "../../Components/CircleColliderComponent.h"
#include "../../Components/MovementComponent.h"
#include "../../Components/PositionComponent.h"
#include "../../Components/SpriteComponent.h"

#include "../../ResourceManager.h"

namespace Ball {

	// Initial velocity of the Ball
	const vec2 INITIAL_VELOCITY(100.0f, -350.0f);
	// Radius of the ball object
	const GLfloat RADIUS = 12.5f;

	Entity Create(EntityManager& entityManager, vec2 position)
	{
		Entity ball = entityManager.create();
		ball.assign<BallComponent>();
		ball.assign<CircleColliderComponent>(Ball::RADIUS);
		ball.assign<SpriteComponent>(ResourceManager::GetTexture("face"), vec2(Ball::RADIUS * 2, Ball::RADIUS * 2));
		ball.assign<MovementComponent>(Ball::INITIAL_VELOCITY, vec2(0.0f, 0.0f), 0.0f);
		ball.assign<PositionComponent>(position);
		return ball;
	}
}