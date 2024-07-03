#pragma once
#include <entt/entt.hpp>

#include "utils/debug.hpp"
#include "utils/globals.hpp"

#include "components/physics.hpp"
#include "components/movement.hpp"
#include "components/animation.hpp"
#include "components/statemachine.hpp"

void on_state_change(entt::registry &, std::vector<state> &states);
void on_state_check(entt::registry &, std::vector<state> &states);
