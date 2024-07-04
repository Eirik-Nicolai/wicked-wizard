#define OLC_PGE_APPLICATION
#define OLC_PGEX_TRANSFORMEDVIEW
#define OLC_PGEX_GFX2D
#define OLC_PGEX_QUICKGUI

#include "game.hpp"


Game::Game()
{
    sAppName = "";
    follow_player = false;
    m_physics = std::make_unique<b2World>(b2Vec2(0.0f, 300.0f));

    m_assets = std::make_unique<AssetManager>();

    tv = olc::TileTransformedView({100,100}, {64,64});
    tv.SetZoom(1, {0,0});
}

bool Game::OnUserCreate()
{
    on_load_init();

    CURR_STATE = GameState::LOADING_INIT;
    NEXT_STATE = CURR_STATE;

    m_fPhysicsElapsedTime = 0.f;


    CURR_STATE = NEXT_STATE;

    // l = std::make_unique<olc::QuickGUI::Label>(debugger, "Hello Hello Hello Hello Hello Hello Hello Hello ", olc::vi2d(200,300), olc::vi2d(100,100));

    // debugger.AddControl(l.get());

    return true;
}

inline olc::vi2d screenspace(olc::vi2d multiplier, olc::vi2d offs, b2Vec2 val, b2Vec2 size)
{
    return olc::vi2d(
        val.x-(size.x),
        val.y-(size.y)
    );
};

bool Game::OnUserUpdate(float dt)
{
    Clear(olc::BLACK);
    tv.DrawRect({0,0}, GetScreenSize());

    if(GetMouseWheel() > 0) tv.ZoomAtScreenPos(2.f, GetMousePos());
    if(GetMouseWheel() < 0) tv.ZoomAtScreenPos(0.5f, GetMousePos());
    if(GetMouse(2).bPressed) tv.StartPan(GetMousePos());
    if(GetMouse(2).bHeld) tv.UpdatePan(GetMousePos());
    if(GetMouse(2).bReleased) tv.EndPan(GetMousePos());

    // if(GetMouse(1).bHeld)
    // {
    //     auto move = m_reg.view<box2d_ref>(entt::exclude<_controllable>);
    //     for(auto [ent, box2d] : move.each())
    //     {
    //         box2d.ref->SetLinearVelocity(b2Vec2(200.f, -100.f));
    //     }

    // }

    // TODO camera follow player. Need to use world/screen funcs ?

    on_progress_animations(m_reg, dt);

    on_state_check(m_reg);

    // FIXME move this later
    on_state_change(m_reg);


    auto size = GetScreenSize();
    // if(GetMouse(1).bReleased)
    // {
    //     follow_player = !follow_player;
    // }

    // box2d_ref body;
    // tryget_component(m_reg, m_player, body);
    // auto pos = body.ref->GetPosition();
    // if(follow_player)
    // {
    //     tv.SetZoom(2, {0,0});

    //     box2d_ref body;
    //     tryget_component(m_reg, m_player, body);
    //     auto pos = body.ref->GetPosition();
    //     tv.SetWorldOffset(olc::vi2d(pos.x, pos.y)-size/4);
    // }
    // else
    // {
    //     tv.SetZoom(1, {0,0});
    // }

    DrawString({100, 300}, size.str(), olc::RED, 2);
    DrawString({100, 350}, (size/2).str(), olc::RED, 2);

    on_userinput_walking();

    do_movement(m_reg);

    on_condition_update(m_reg, dt);

    on_effect_apply(m_reg);


    // if(follow_player)
    // {
    //     box2d_ref body;
    //     tryget_component(m_reg, m_player, body);
    //     auto pos = body.ref->GetPosition();
    //     auto newpos = screenspace({0,0}, tv.GetTopLeftTile(), pos, body.size);

    //     DrawString({100, 100}, "phys: " + std::to_string(pos.x) + ", " + std::to_string(pos.y), olc::RED, 2);
    //     DrawString({100, 125}, "screen: " + newpos.str(), olc::RED, 2);

    //     tv.UpdatePan(-newpos);
    // }

    // DrawString({100, 300}, "tv: " + tv.GetWorldScale().str(), olc::RED, 2);
    // DrawString({100, 350}, "tv: " + tv.GetWorldTL().str(), olc::RED, 2);

    // TODO figure out how this works exactly
    // debugger.Update(this);
    // debugger.Draw(this);

    if(m_fPhysicsElapsedTime > PHYSICS_TICK)
    {
        m_fPhysicsElapsedTime = 0.f;
    }
    else
        m_fPhysicsElapsedTime += dt;

    m_physics->Step(dt, 8, 3);
    m_physics->ClearForces();

    //DrawString({1000, 200}, std::to_string(GetFPS()), olc::RED, 2);

    render();
    return true;
}



// //// HELPER FUNCTIONS /////

// entt::entity Game::create_enemy(std::string name, std::string c, int h)
// {
//     auto ent = m_reg.create();
//     m_reg.emplace<_enemy>(ent);
//     m_reg.emplace<visual>(ent,visual{
//         .name = name,
//         .char_repr = c,
//     });
//     m_reg.emplace<health>(ent, h, h);
//     m_reg.emplace<affected>(ent);
//     return ent;
// }
// entt::entity Game::create_ally(std::string name, std::string c, int h)
// {
//     auto ent = m_reg.create();
//     m_reg.emplace<_ally>(ent);
//     m_reg.emplace<visual>(ent,visual{
//         .name = name,
//         .char_repr = c,
//     });
//     m_reg.emplace<health>(ent, h, h);
//     m_reg.emplace<affected>(ent);
//     return ent;
// }
