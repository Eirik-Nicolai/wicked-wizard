#include "render.hpp"

void Game::render()
{
    SetPixelMode(olc::Pixel::Mode::NORMAL);

    auto offs = tv.GetTopLeftTile();

    for(auto [ent, box2d, curr_anim] : m_reg.view<box2d_ref, current_animation>().each())
    {
        auto anim = m_reg.get<animation>(curr_anim.ent);
        DrawString({300,400}, "pos: " + anim.name);
        auto pos = box2d.ref->GetPosition();
        auto size = box2d.size;

        auto curr_frame = anim.frames[anim.current_frame];

        auto sheet = m_assets->get(anim.sheet).lock().get();

        tv.DrawPartialDecal(
            screenspace(offs, pos, size),
            sheet,
            curr_frame.pos,
            curr_frame.size,
            {size.x*3,size.y*3}
        );

        DrawString({400,400}, "pos: " + curr_frame.pos.str());
        DrawString({400,450}, "size: " + curr_frame.size.str());
    }

    SetPixelMode(olc::Pixel::Mode::NORMAL);

    auto box2d = m_reg.view<box2d_ref, _renderable>();
    for(auto [ent, box2d] : box2d.each())
    {
        auto pos = box2d.ref->GetPosition();
        auto size = box2d.size;
        tv.DrawRect(screenspace(offs, pos, size), {size.x*2, size.y*2});
        tv.FillRect(screenspace(offs, pos, size), {2, 2}, olc::RED);
    }
    SetPixelMode(olc::Pixel::Mode::NORMAL);
}
