#pragma once

#include <entityplus/entity.h>

#include "BallComponent.h"
#include "BoxColliderComponent.h"
#include "CircleColliderComponent.h"
#include "HealthComponent.h"
#include "MovementComponent.h"
#include "PositionComponent.h"
#include "SpriteComponent.h"

using ComponentList = component_list<BallComponent, BoxColliderComponent, CircleColliderComponent, HealthComponent, MovementComponent, PositionComponent, SpriteComponent>;