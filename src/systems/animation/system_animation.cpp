#include "system_animation.hpp"

void on_progress_animations(entt::registry& reg, const float& dt)
{
    auto anim = reg.view<current_animation>();
    for(auto &&[ent, curr] : anim.each())
    {
        animation &anim = reg.get<animation>(curr.ent);
        auto curr_frame = anim.frames[anim.current_frame];

        // DEBUG(anim.name);
        // DEBUG(std::to_string(anim.current_frame_duration) + " " + std::to_string(dt));

        anim.current_frame_duration += dt;
        if(anim.current_frame_duration >= curr_frame.frame_dur)
        {
            anim.current_frame_duration = 0;
            anim.current_frame++;
        }

        if(anim.current_frame == anim.max_frames)
        {
            anim.current_frame = 0;
        }
    }
}
