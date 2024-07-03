#ifndef MOVING_H_
#define MOVING_H_

#include <entt/entt.hpp>
#include "box2d/box2d.h"

#include "utils/ecs.hpp"
#include "utils/debug.hpp"
#include "utils/globals.hpp"

#include "components/logic.hpp"
#include "components/globals.hpp"
#include "components/physics.hpp"
#include "components/movement.hpp"

void do_movement(entt::registry &reg);

#endif // MOVING_H_
