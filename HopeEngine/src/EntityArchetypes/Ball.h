#pragma once

#include "../entity.h"

namespace Ball {

	const GLfloat RADIUS = 30.0f

	Entity Create(EntityManager entityManager)
	{
		Entity ball = entityManager.create_entity();
		ball.add_component<BallComponent>();
		ball.add_component<CircleColliderComponent>(Ball::RADIUS);
		ball.add_component<SpriteComponent>();
		ball.add_component<MovementComponent>();
		ball.add_component<PositionComponent>();

		return ball;
	}
}