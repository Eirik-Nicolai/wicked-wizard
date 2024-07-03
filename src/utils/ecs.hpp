#ifndef ECS_H_
#define ECS_H_

#include "entt/entt.hpp"

template <typename component>
bool has(entt::registry &reg, entt::entity &ent)
{
  return reg.all_of<component>(ent);
}

template <typename component>
bool tryget_component(entt::registry &reg, entt::entity &ent, component &comp)
{
  if(auto getcomp = reg.try_get<component>(ent);reg.try_get<component>(ent) != nullptr)
  {
    comp = (*getcomp);
    return true;
  }
  return false;
}

template <typename component>
bool tryget_component(entt::registry &reg, const entt::entity &ent, component &comp)
{
  if(auto getcomp = reg.try_get<component>(ent);reg.try_get<component>(ent) != nullptr)
  {
    comp = (*getcomp);
    return true;
  }
  return false;
}

//TODO check reference
template <typename component>
component get(entt::registry &reg, const entt::entity e)
{
  return reg.get<component>(e);
}

template <typename component>
const component cget(entt::registry &reg, const entt::entity e)
{
  return reg.get<component>(e);
}


#endif // ECS_H_
