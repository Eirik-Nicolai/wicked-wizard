#pragma once

#include <string>
#include <vector>

#include <entt/entt.hpp>

#include "utils/ecs.hpp"
#include "utils/globals.hpp"

#include "components/statemachine.hpp"

struct cond_triggee{
  check_world validator;
};

struct cond_timer{
    float accum_time;
    float dur;
};

struct cond_ticking{
  float accum_time;
  float tick_dur;

  uint8_t tick;
  uint8_t max_ticks;
};

struct onadd_effect{
  std::string name;
  update_world action;
};

struct onremove_effect{
  std::string name;
  update_world action;
};

struct continous_effect{
  std::string name;
  update_world_deltatime action;
};

struct active_on{
  entt::entity ent;
};

struct status_manager{
  std::set<entt::entity> statuses;
  void add_status(entt::registry &reg, entt::entity &affected, entt::entity &status){
    if(auto eff = reg.try_get<onadd_effect>(status))
      eff->action(reg, affected); // TODO this might have to be changed

    reg.emplace<active_on>(status, affected);
    statuses.emplace(status);
    std::cout << "add SIZE: " << std::to_string(statuses.size()) << std::endl;
  }

  void remove_status(entt::registry &reg, entt::entity &affected, entt::entity &status){
    if(auto eff = reg.try_get<onremove_effect>(status))
      eff->action(reg, affected);

    reg.remove<active_on>(status);
    statuses.erase(status);
    std::cout << "remove SIZE: " << std::to_string(statuses.size()) << std::endl;
  }
};
