#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
using namespace glm;

#include <entityx/entityx.h>
using namespace entityx;

// Components
#include "../Components/PositionComponent.h"
#include "../Components/MovementComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/CircleColliderComponent.h"

class MovementSystem : public System<MovementSystem>
{
	int windowWidth, windowHeight;
	static constexpr GLfloat DRAG_MAGNITUDE = 0.00125f;
public:
	explicit MovementSystem(int _windowWidth, int _windowHeight) : windowWidth(_windowWidth), windowHeight(_windowHeight) {}

	void update(EntityManager &entities, EventManager &events, TimeDelta dt) override
	{
		entities.each<MovementComponent, PositionComponent>([&](Entity entity, MovementComponent &movement, PositionComponent &position)
		{
			vec2 halfAcceleration = movement.acceleration * 0.5f * (float)dt; // -(movement.velocity * DRAG_MAGNITUDE * movement.dragCoefficient);
			movement.velocity += halfAcceleration;
			vec2 desiredLocation = position.position + movement.velocity * (float)dt;
			movement.velocity += halfAcceleration;

			// entity moved
			if (desiredLocation != position.position)
			{
				// check for collision
				if (entity.has_component<BoxColliderComponent>())
				{
					// get this entity's box collider
					ComponentHandle<BoxColliderComponent> boxColliderHandle = entity.component<BoxColliderComponent>();
					BoxColliderComponent *boxCollider = boxColliderHandle.get();
					vec2 boxSize = boxCollider->bottomRight - boxCollider->topLeft;

					// Clamp horizontal movement to screen space
					if (desiredLocation.x < 0) { desiredLocation.x = 0; }
					GLfloat maximumX = windowWidth - boxSize.x;
					if (desiredLocation.x > (windowWidth - boxSize.x)) { desiredLocation.x = windowWidth - boxSize.x; }

					// Check for ball collisions
					entities.each<CircleColliderComponent>([&](Entity ballEntity, CircleColliderComponent &circleCollider)
					{

					});
				}
				if (entity.has_component<CircleColliderComponent>())
				{
					// get this entity's circle collider
					ComponentHandle<CircleColliderComponent> circleColliderHandle = entity.component<CircleColliderComponent>();
					CircleColliderComponent *circleCollider = circleColliderHandle.get();
					GLfloat diameter = circleCollider->radius * 2;

					// Check for bouncing against screen borders
					if (desiredLocation.x < 0)
					{
						desiredLocation.x = 0;
						movement.velocity.x = -movement.velocity.x;
					}
					if (desiredLocation.x > windowWidth - diameter)
					{
						desiredLocation.x = windowWidth - diameter;
						movement.velocity.x = -movement.velocity.x;
					}
					if (desiredLocation.y < 0)
					{
						desiredLocation.y = 0;
						movement.velocity.y = -movement.velocity.y;
					}
					if (desiredLocation.y > windowHeight - diameter)
					{
						desiredLocation.y = windowHeight - diameter;
						movement.velocity.y = -movement.velocity.y;
					}

					// Check for ball collisions
					entities.each<BoxColliderComponent>([&](Entity boxEntity, BoxColliderComponent &boxCollider)
					{
						GLfloat closestX = desiredLocation.x + circleCollider->radius;
						if (closestX < boxCollider.topLeft.x) { closestX = boxCollider.topLeft.x; }
						if (closestX > boxCollider.bottomRight.x) { closestX = boxCollider.bottomRight.x; }
						GLfloat closestY = desiredLocation.y - circleCollider->radius;
						if (closestY < boxCollider.topLeft.y) { closestY = boxCollider.topLeft.y; }
						if (closestY > boxCollider.bottomRight.y) { closestY = boxCollider.bottomRight.y; }

						GLfloat distanceX = desiredLocation.x + circleCollider->radius - closestX;
						GLfloat distanceY = desiredLocation.y - circleCollider->radius - closestY;

						if (distanceX * distanceX + distanceY * distanceY < circleCollider->radius * circleCollider->radius)
						{
							// collision!
							movement.velocity.x = -movement.velocity.x;
							movement.velocity.y = -movement.velocity.y;
						}

					});
				}

				// move ok
				position.position = desiredLocation;
			}
		});
	}
};