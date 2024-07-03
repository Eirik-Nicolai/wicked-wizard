#pragma once

#include <entt/entt.hpp>

#include <cstdint>
#include <string>

enum class STATE { IDLE, WALKING, UNKNOWN };

struct state {
  size_t id;
  std::string name;

  std::function<void(entt::registry&, entt::entity &)> on_enter;
  std::function<void(entt::registry&, entt::entity &)> on_exit;

  //entt::entity animation;

  std::function<bool(entt::registry& reg, entt::entity &ent)> validator;
};

struct new_state{
  size_t id;
  std::string name;

};

struct curr_state {
  size_t id;
  std::string name;
};

struct secondary_state {
  size_t id;
  std::string name;
};

// // movement states
// struct state_movement : public state {
//     entt::entity animation;
// };

// struct state_walking : public state_movement {};

// struct state_idle : public state_movement {};


// // movement states
// struct state_status : public state {
//     // something
// };
