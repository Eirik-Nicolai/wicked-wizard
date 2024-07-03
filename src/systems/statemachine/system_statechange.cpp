#include "system_statechange.hpp"




void on_state_check(entt::registry &reg, std::vector<state> &states)
{

    for(auto &&[ent, c_state]: reg.view<secondary_state>().each())
    {
        for(auto &s : states)
        {
            if(c_state.id == s.id) continue;
            //DEBUG("CHECKING");
            if(s.validator(reg, ent))
            {
                DEBUG("VALIDATED " + s.name);
                reg.emplace<new_state>(
                    ent,
                    s.id,
                    s.name
                );
                break;
            }
        }
    }

    // movement
    for(auto &&[ent, c_state]: reg.view<curr_state>().each())
    {
        for(auto &s : states)
        {
            if(c_state.id == s.id) continue;
            //DEBUG("CHECKING");
            if(s.validator(reg, ent))
            {
                DEBUG("VALIDATED " + s.name);
                reg.emplace<new_state>(
                    ent,
                    s.id,
                    s.name
                );
                break;
            }
        }
    }
}

void on_state_change(entt::registry &reg, std::vector<state> &states)
{
    for(auto &&[ent, n_state, c_state]: reg.view<new_state, curr_state>().each())
    {

        DEBUG("CHANGING FROM " + c_state.name);
        states[c_state.id].on_exit(reg, ent);
        reg.erase<curr_state>(ent);

        DEBUG("CHANGING TO " + n_state.name);
        states[n_state.id].on_enter(reg, ent);
        reg.emplace<curr_state>(
            ent,
            n_state.id,
            n_state.name
        );
        reg.erase<new_state>(ent);
    }
}
