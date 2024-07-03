#include "statemachine.hpp"


State::State(STATE s, std::string n,
             std::function<void(entt::registry&, entt::entity &)> on_enter,
             std::function<void(entt::registry&, entt::entity &)> on_exit,
             std::function<bool(entt::registry&, entt::entity &)> validator
) : mask(to_mask(s)), name(n),
    on_enter(on_enter), on_exit(on_exit), validator(validator)
{}

void State::add_blocker(State s)
{
  if(block_amnt<32) blocked_by[block_amnt++]=s.mask;
}

void State::add_requirement(State s)
{
  std::cout << "adding req " << s.mask << std::endl;
  if(req_amnt<32) requirements[req_amnt++]=s.mask;
}

void State::add_termination(State s)
{
  if(term_amnt<32) terminates[term_amnt++]=s.mask;
}

long State::blocking_states()
{
  return to_mask(blocked_by, block_amnt);
}
long State::required_states()
{
  return to_mask(requirements, req_amnt);
}
long State::terminates_states()
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
        DEBUG("VALIDATED");
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
    //std::cout << "actiavted" << std::endl;
    queue_activate(state);
  }
}

bool StateManager::activatable(State state)
{
  return
    !is_active(state.mask)
    && !is_blocked(state.blocking_states())
    && has_required_states(state.required_states());
}

bool StateManager::is_active(long state)
{
  return (state & curr) != 0;
}

bool StateManager::is_blocked(long blockmask)
{
  return (blockmask & curr) != 0;
}

bool StateManager::has_required_states(long reqmask)
{
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
    std::cout << "ADDING STATE" << std::endl;
    std::cout << state.str() << std::endl;

    if(state.terminates_states() != 0)
      deactivate(state.terminates_states(), reg, ent);

    curr |= state.mask;
    state.on_enter(reg, ent);

    next.pop();
  }
}

void StateManager::deactivate(long states, entt::registry &reg, entt::entity &ent)
{
  if(states == 0) return;
  long to_deactivate_mask = curr & states;
  auto to_deactivate = get_registered_states(to_deactivate_mask);

  for(auto state : to_deactivate)
  {
    deactivate(state, reg, ent);
  }
}

void StateManager::deactivate(State state, entt::registry &reg, entt::entity &ent)
{
  curr &= !state.mask;
  state.on_exit(reg, ent);
  deactivate(get_requiring(state.mask), reg, ent);
}

std::vector<State> StateManager::get_registered_states(long mask)
{
  std::vector<State> list;
  for(auto s : registered_states)
  {
    if(s.first && mask)
      list.emplace_back(s.second);
  }
  return list;
}

long StateManager::get_requiring(long mask)
{
  if(mask == 0) return 0;
  long requiring = 1;
  for(auto s : registered_states)
    mask &= s.first;
  return requiring;
}
