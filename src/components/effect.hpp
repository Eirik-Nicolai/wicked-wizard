#pragma once

#include <string>
#include <vector>

#include <entt/entt.hpp>

#include "utils/globals.hpp"

// what does our status do
struct effect{
  std::string name;

  update_world on_enter;
  update_world on_exit;

  update_world apply;
};

// how does it work
struct condition_triggered{
  std::string name;

  check_world validator;
};


struct condition_timed{
  std::string name;

  float accum_time;
  float dur;
};


struct condition_ticking{
  std::string name;

  float accum_time;
  float tick_dur;

  uint8_t tick;
  uint8_t max_ticks;
};

struct status{

};
