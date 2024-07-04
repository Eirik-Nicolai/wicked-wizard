#ifndef ANIMATION_H_
#define ANIMATION_H_

#include "components/combat.hpp"

#include "olc/olcPixelGameEngine.h"
#include <entt/entt.hpp>

struct status_animation{
  entt::entity ent; //TODO this should be a list
};

struct current_animation{
  entt::entity ent;
};

struct animation_frame {
  olc::vi2d pos;
  olc::vi2d size;

  float frame_dur;
  std::vector<hitbox> hitboxes; // TODO heap allocate ?
};

struct animation {
  size_t sheet;
  std::string name;

  uint8_t current_frame;
  float current_frame_duration;

  size_t max_frames;
  std::vector<animation_frame> frames;
};

#endif // ANIMATION_H_
