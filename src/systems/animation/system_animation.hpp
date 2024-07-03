#ifndef SYSTEM_ANIMATION_H_
#define SYSTEM_ANIMATION_H_

#include <entt/entt.hpp>

#include "utils/debug.hpp"
#include "utils/globals.hpp"

#include "components/physics.hpp"
#include "components/movement.hpp"
#include "components/animation.hpp"
#include "components/statemachine.hpp"

void on_progress_animations(entt::registry &, const float& dt);


#endif // SYSTEM_ANIMATION_H_
