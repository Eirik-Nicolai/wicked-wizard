#include "system_status.hpp"

void on_condition_update(entt::registry &reg, float &dt)
{
    for(auto &&[ent, cond, act] : reg.view<cond_timer, active_on>().each())
    {
        DEBUG("UPDATING TIMER");

        DEBUG_VAL(cond.accum_time);
        cond.accum_time += dt;
        if(cond.accum_time >= cond.dur)
        {
            cond.accum_time = 0;
            auto man = reg.get<status_manager>(act.ent);
            man.remove_status(reg, act.ent, ent);
        }
    }

    for(auto &&[ent, eff] : reg.view<continous_effect>().each())
    {
        eff.action(reg, ent, dt);
    }
}

void on_effect_apply(entt::registry &reg)
{
    // for(auto &&[ent, act, eff] : reg.view<active_on, continous_effect>().each())
    // {
    //     DEBUG("PERFORMING ACTION");
    //     eff.action(reg, act.ent);
    // }
}
