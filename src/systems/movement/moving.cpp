#include "moving.hpp"

void do_movement(entt::registry &reg)
{
    auto rmover = reg.view<_moving_right, movement, box2d_ref>();
    for(auto [ent, move, box2d] : rmover.each())
    {
        box2d.ref->ApplyForceToCenter(b2Vec2(30000.f, 0.f), true);
    }

    auto lmover = reg.view<_moving_left, movement, box2d_ref>();
    for(auto [ent, move, box2d] : lmover.each())
    {
        box2d.ref->ApplyForceToCenter(b2Vec2(-30000.f, 0.f), true);
    }

    auto jump = reg.view<_jump, movement, box2d_ref>();
    for(auto [ent, move, box2d] : jump.each())
    {
        box2d.ref->ApplyLinearImpulseToCenter(b2Vec2(0.f, -25000.f), true);
        reg.remove<_jump>(ent);
    }
}
