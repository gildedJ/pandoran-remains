#pragma once

#include <entityplus/entity.h>

#include "Components/Components.h"
#include "Components/Tags.h"

using namespace entityplus;
using EntityManager = entity_manager<ComponentList, TagList>;
using Entity = EntityManager::entity_t;