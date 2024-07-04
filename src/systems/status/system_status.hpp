#pragma once

#include <entt/entt.hpp>

#include "components/status.hpp"

void on_condition_update(entt::registry &, float &);

void on_effect_apply(entt::registry &);
