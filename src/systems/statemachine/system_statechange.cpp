#include "system_statechange.hpp"




void on_state_check(entt::registry &reg)
{
    for(auto &&[ent, state_man]: reg.view<StateManager>().each())
    {
        state_man.validate_states(reg, ent);
    }
}

void on_state_change(entt::registry &reg)
{
    for(auto &&[ent, state_man]: reg.view<StateManager>().each())
    {
        state_man.activate(reg, ent);
    }
}
