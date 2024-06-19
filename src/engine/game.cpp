#define OLC_PGE_APPLICATION
#include "game.hpp"

DungeonThing::DungeonThing()
{
    sAppName = "";
    m_curr_menu = 0;
    m_transition_time = 2;
    m_transition_progress = 0;
    m_transition_acc = 5;
    m_elapsed_transition_time = 1;

    m_equip_finger_left = false;
    m_equip_head_left = false;

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

    MenuItem<std::string> USE{
    "USE ITEM",
    "",
    [&]{
        std::cout << "USE ITEM NOT IMPL" << std::endl;
    }};
    MenuItem<std::string> INSPECT{
    "INSPECT",
    "",
    [&]{
        std::cout << "INSPECT NOT IMPL" << std::endl;
    }};
    MenuItem<std::string> BACK{
    "BACK",
    "",
    [&]{
        m_curr_menu = 0;
        NEXT_STATE.type = type::OVERVIEW;
    }};

    //m_pausemenus.emplace_back(SimpleMenu(USE, INSPECT, BACK));
    MenuItem<std::string> EQUIP{
    "EQUIP ITEM",
    "",
    [&]{
        std::cout << "EQUIP ITEM NOT IMPL" << std::endl;
    }};
    MenuItem<std::string> INFO{
    "INFO",
    "",
    [&]{
        std::cout << "INFO NOT IMPL" << std::endl;
    }};
    //m_pausemenus.emplace_back(SimpleMenu(EQUIP, INFO, BACK));

}

bool DungeonThing::OnUserCreate()
{
    on_load_init();

    CURR_STATE = {state::PAUSED, type::INIT};
    NEXT_STATE = CURR_STATE;

    m_fElapsedTimeSinceTick = 0;

    return true;
}

bool DungeonThing::OnUserUpdate(float dt)
{
    Clear(olc::BLACK);
    Debugger::instance().Clear();

    switch(CURR_STATE.state)
    {
        case state::COMBAT:
        {
            STATE_COMBAT(dt);
        }
        break;

        case state::PAUSED:
        {
            STATE_PAUSE(dt);
        }
        break;

        case state::WALKING:
        {
            STATE_WALKING(dt);
        }
        break;

        default:
        {
            std::cout << "not impl" << std::endl;
        }
    }

    Debugger::instance().Print(this, 0.80, 0.80);
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

void DungeonThing::set_equipment(const entt::entity &e)
{
    auto &equipment = m_reg.ctx().get<EquipmentState>();
    switch (get<equipment_type>(e).type)
    {
        case equiptype::HEAD:
            equipment.head = e;
            break;
        case equiptype::TORSO:
            equipment.torso = e;
            break;
        case equiptype::LEGS:
            equipment.legs = e;
            break;
        case equiptype::MAINHAND:
            equipment.main_hand = e;
            break;
        case equiptype::OFFHAND:
            equipment.off_hand = e;
            break;
        case equiptype::ACCESS_FINGER:
            if(m_equip_finger_left)
                equipment.finger_left = e;
            else
                equipment.finger_right = e;
            break;
        case equiptype::ACCESS_HEAD:
            if(m_equip_head_left)
                equipment.finger_right = e;
            else
                equipment.finger_right = e;
            break;
        default:
            throw std::runtime_error("equipment indx not recognised");
    }
}

//TODO move to combat
bool DungeonThing::has_enough_resources(entt::entity &actor, entt::entity &action)
{
    cost c;
    if(tryget_component(action, c))
    {
        switch(c.type)
        {
            case resource_type::MANA:
            {
                mana m;
                if(tryget_component(actor, m))
                {
                    return m.curr >= c.amount;
                }
                return false;
            }
            break;
            case resource_type::HEALTH:
            {
                health h;
                if(tryget_component(actor, h))
                {
                    return h.curr >= c.amount;
                }
                //this shouldn't happen
                return false;
            }
            break;
            default:
                std::cout << "RESOURCE TYPE NOT IMPL" << std::endl;
        }
    }
    // no cost
    return true;
}


//// HELPER FUNCTIONS /////

entt::entity DungeonThing::create_enemy(std::string name, std::string c, int h)
{
    auto ent = m_reg.create();
    m_reg.emplace<_enemy>(ent);
    m_reg.emplace<visual>(ent,visual{
        .name = name,
        .char_repr = c,
    });
    m_reg.emplace<health>(ent, h, h);
    m_reg.emplace<affected>(ent);
    return ent;
}
entt::entity DungeonThing::create_ally(std::string name, std::string c, int h)
{
    auto ent = m_reg.create();
    m_reg.emplace<_ally>(ent);
    m_reg.emplace<visual>(ent,visual{
        .name = name,
        .char_repr = c,
    });
    m_reg.emplace<health>(ent, h, h);
    m_reg.emplace<affected>(ent);
    return ent;
}
