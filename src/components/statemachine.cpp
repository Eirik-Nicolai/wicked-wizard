#include "statemachine.hpp"


State::State(STATE s, std::string n,
             std::function<void(entt::registry&, entt::entity &)> on_enter,
             std::function<void(entt::registry&, entt::entity &)> on_exit,
             std::function<bool(const entt::registry&, const entt::entity &)> validator
) : mask(to_mask(s)), name(n),
    on_enter(on_enter), on_exit(on_exit), validator(validator)
{}

State::State(STATE s, std::string n,
             update_world on_enter,
             update_world on_exit
) : mask(to_mask(s)), name(n),
    on_enter(on_enter), on_exit(on_exit)
{
  validator = nullptr;
}

void State::add_blocker(STATE s)
{
  if(block_amnt<32) blocked_by[block_amnt++]=to_mask(s); //TODO just save this as a bitmask ?
}

void State::add_requirement(STATE s)
{
  if(req_amnt<32) requirements[req_amnt++]=to_mask(s);
}

void State::add_termination(STATE s)
{
  if(term_amnt<32) terminates[term_amnt++]=to_mask(s);
}

bitmask State::blocking_states()
{
  return to_mask(blocked_by, block_amnt);
}
bitmask State::required_states()
{
  return to_mask(requirements, req_amnt);
}
bitmask State::terminates_states()
{
  return to_mask(terminates, term_amnt);
}



StateManager::StateManager(State &init_state)
{
  curr = init_state.mask;
  registered_states.emplace(init_state.mask, init_state);
}


StateManager::StateManager(State &init_state, std::vector<State> states)
{
  curr = init_state.mask;
  for(State s : states)
  {
    registered_states.emplace(s.mask, s);
  }
}

void StateManager::register_state(State &state)
{
  registered_states.emplace(state.mask, state);
}


bool StateManager::validate_states(entt::registry &reg, entt::entity &ent)
{
  for(auto &rs : registered_states)
  {
    auto s = rs.second;
    if(s.validator && !is_active(s.mask))
    {
      if(s.validator(reg, ent))
      {
        try_activate(s);
      }
    }
  }
  return false;
}

void StateManager::try_activate(State state)
{
  if(activatable(state))
  {
    DEBUG("ADDING " + state.name + " TO QUEUE");
    queue_activate(state);
    DEBUG_VAL(next.size());
  }
}

bool StateManager::activatable(State state)
{
  // DEBUG("activatable")
  // DEBUG_VAL(curr)
  // DEBUG_VAL(is_active(state.mask));
  // DEBUG_VAL(is_blocked(state.blocking_states()));
  // DEBUG_VAL(has_required_states(state.required_states()));
  return
    !is_blocked(state.blocking_states())
    && has_required_states(state.required_states());
}

bool StateManager::is_active(bitmask state)
{
  return (state & curr) != 0;
}

bool StateManager::is_blocked(bitmask blockmask)
{
  // DEBUG_VAL(blockmask);
  return (blockmask & curr) != 0;
}

bool StateManager::has_required_states(bitmask reqmask)
{
  // DEBUG_VAL(reqmask);
  return (reqmask ^ curr) == 0 || reqmask == 0; //XOR
}

void StateManager::queue_activate(State state)
{
  next.push(state);
}

void StateManager::activate(entt::registry &reg, entt::entity &ent)
{
  while(!next.empty())
  {
    auto state = next.top();
    DEBUG("CHANGING TO")
    DEBUG_VAL(state)
    if(state.terminates_states() != 0)
      deactivate(state.terminates_states(), reg, ent);

    curr |= state.mask;
    state.on_enter(reg, ent);

    next.pop();
    DEBUG_VAL(next.size());
  }
}

void StateManager::deactivate(bitmask states, entt::registry &reg, entt::entity &ent)
{
  if(states == 0) return;
  bitmask to_deactivate_mask = curr & states;
  auto to_deactivate = get_registered_states(to_deactivate_mask);

  for(auto state : to_deactivate)
  {
    deactivate(state, reg, ent);
  }
}

void StateManager::deactivate(State state, entt::registry &reg, entt::entity &ent)
{
  DEBUG("DEACTIVATING " + state.name);
  curr &= !state.mask;
  state.on_exit(reg, ent);
  deactivate(get_requiring(state.mask), reg, ent);
}

std::vector<State> StateManager::get_registered_states(bitmask mask)
{
  std::vector<State> list;
  for(auto s : registered_states)
  {
    if(s.first && mask)
      list.emplace_back(s.second);
  }
  return list;
}

bitmask StateManager::get_requiring(bitmask mask)
{
  if(mask == 0) return 0;
  bitmask requiring = 1;
  for(auto s : registered_states)
    mask &= s.first;
  return requiring;
}

bool StateManager::give_state(State s)
{
  DEBUG_SPACE()
  DEBUG_LINE()
  DEBUG("TRYING TO ADD STATE " + s.name);
  DEBUG("ACTIVATABLE IS ");
  DEBUG(activatable(s));
  if(s.state == STATE::UNKNOWN)
    return false;

  try_activate(s);

  DEBUG_LINE()
  DEBUG_SPACE()
  return true;
}

// FIXME add back with a queue
// void StateManager::take_state(entt::registry &reg, entt::entity &ent, State s)
// {
//   deactivate(s, reg, ent);
// }
