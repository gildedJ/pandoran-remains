#pragma once

#include <entityplus/entity.h>

struct Player {};
struct Enemy {};
struct PowerUp {};

using TagList = tag_list<struct Player, struct Enemy, struct PowerUp>;