#define OLC_PGE_APPLICATION
#define OLC_PGEX_TRANSFORMEDVIEW
#define OLC_PGEX_GFX2D
#include "game.hpp"


DungeonThing::DungeonThing()
{
    sAppName = "";

    m_physics = std::make_unique<b2World>(b2Vec2(0.0f, 200.0f));

    MenuItem<std::string> resume{
    "RESUME",
    "",
    [&]{
        NEXT_STATE.state = state::WALKING;
        NEXT_STATE.type = type::FREEROAM;
    }};
    MenuItem<std::string> inventory{
    "INVENTORY",
    "",
    [&]{
        NEXT_STATE.type = type::INIT_INVENTORY;
    }};
    MenuItem<std::string> equipment{
    "EQUIPMENT",
    "",
    [&]{
        // TODO menu list of equipment types
        // and then list of currently held items
        //m_curr_menu = 2;

        NEXT_STATE.type = type::EQUIPMENT;
    }};
    MenuItem<std::string> othershit{
    "SOME OTHER SHIT",
    "",
    []{
        std::cout << "SOME SHIT NOT IMPL" << std::endl;
    }};
    m_pause_menu = SimpleMenu(resume, inventory, equipment, othershit);
}

bool DungeonThing::OnUserCreate()
{
    on_load_init();

    CURR_STATE = {state::COMBAT, type::INIT};
    NEXT_STATE = CURR_STATE;

    m_fElapsedTimeSinceTick = 0;

    return true;
}

bool DungeonThing::OnUserUpdate(float dt)
{
    Clear(olc::BLACK);




    CURR_STATE = NEXT_STATE;

    return true;
}


bool DungeonThing::delay_for(float delay, float dt)
{
    if(m_elapsed_transition_time >= delay)
    {
        m_elapsed_transition_time = 0;
        return true;
    }
    m_elapsed_transition_time+= dt;
    return false;
}

std::string DungeonThing::get_name(const entt::entity &ent, std::string ret)
{
    visual v;
    if(tryget_component(ent, v))
    {
        return v.name;
    }
    return ret;
}


// //// HELPER FUNCTIONS /////

// entt::entity DungeonThing::create_enemy(std::string name, std::string c, int h)
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
// entt::entity DungeonThing::create_ally(std::string name, std::string c, int h)
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
