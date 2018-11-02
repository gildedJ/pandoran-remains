#pragma once

#include <glm/glm.hpp>
using namespace glm;

#include <entityx/entityx.h>
using namespace entityx;

#include "../../Components/BoxColliderComponent.h"
#include "../../Components/HealthComponent.h"
#include "../../Components/PositionComponent.h"
#include "../../Components/SpriteComponent.h"

#include "../../Renderer/Texture.h"

namespace Block {

	Entity Create(EntityManager& entityManager, vec2 pos, vec2 size, Texture2D &texture, vec3 color, bool isBreakable)
	{
		Entity block = entityManager.create();
		block.assign<BoxColliderComponent>(pos, pos + size);
		block.assign<SpriteComponent>(texture, size, vec2(0.0f, 0.0f), color);
		block.assign<PositionComponent>(pos);

		if (isBreakable)
		{
			block.assign<HealthComponent>(1);
		}

		return block;
	}

}