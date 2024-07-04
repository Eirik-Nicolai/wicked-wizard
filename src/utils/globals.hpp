#pragma once
#define PIXEL_OFFS 20

#include <entt/entt.hpp>

typedef std::function<void(entt::registry&, entt::entity &)> update_world;
typedef std::function<void(entt::registry&, entt::entity &, const float &)> update_world_deltatime;

typedef std::function<bool(const entt::registry&, const entt::entity &)> check_world;


typedef long long bitmask;
