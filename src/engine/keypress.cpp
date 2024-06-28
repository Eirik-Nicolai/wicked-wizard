#include "game.hpp"
#include "keypress.hpp"
#include <iostream>

void DungeonThing::on_userinput_walking()
{
    if (GetKey(olc::Key::W).bHeld)
    {
        m_reg.get<dirVertical>(m_player).up = true;
    }
    if (GetKey(olc::Key::W).bReleased)
    {
        m_reg.get<dirVertical>(m_player).up = false;
    }

    if (GetKey(olc::Key::S).bHeld)
    {
        m_reg.get<dirVertical>(m_player).down = true;
    }
    if (GetKey(olc::Key::S).bReleased)
    {
        m_reg.get<dirVertical>(m_player).down = false;
    }

    if (GetKey(olc::Key::A).bHeld)
    {
        m_reg.get<dirHorisontal>(m_player).left = true;
    }
    if (GetKey(olc::Key::A).bReleased)
    {
        m_reg.get<dirHorisontal>(m_player).left = false;
    }

    if (GetKey(olc::Key::D).bHeld)
    {
        m_reg.get<dirHorisontal>(m_player).right = true;
    }
    if (GetKey(olc::Key::D).bReleased)
    {
        m_reg.get<dirHorisontal>(m_player).right = false;
    }


    // OPEN INVENTORY / PAUSE GAME
    if (GetKey(olc::Key::I).bReleased)
    {
        NEXT_STATE.state = state::PAUSED;
        NEXT_STATE.type = type::INIT;
    }

    // DEBUGGING
    if (GetKey(olc::Key::X).bReleased)
    {
        NEXT_STATE.state = state::COMBAT;
        NEXT_STATE.type = type::INIT;
    }
}

void DungeonThing::on_userinput_paused()
{
    switch(CURR_STATE.type)
    {
        case type::OVERVIEW:
        {
            if (GetKey(olc::Key::W).bReleased)
            {
                m_pause_menu.scroll_up();
            }
            if (GetKey(olc::Key::S).bReleased)
            {
                m_pause_menu.scroll_down();
            }
            if(GetKey(olc::Key::ENTER).bReleased)
            {
                m_pause_menu.select();
            }
        }
        break;
        default:
            std::cout << "PAUSE TYPE NOT RECOGNISED" << std::endl;
    }

    if(GetKey(olc::Key::ESCAPE).bReleased)
    {
        switch(CURR_STATE.type)
        {
            case type::OVERVIEW:
                NEXT_STATE.state = state::WALKING;
                NEXT_STATE.type = type::FREEROAM;
                break;
            default:
                NEXT_STATE.type = type::INIT;


        }
    }


    // DEBUG

    // if(GetKey(olc::Key::Z).bReleased)
    // {
    //     m_reg.patch<health>(m_player, [](auto &h){
    //         h.curr -= 15;
    //     });
    // }

    // if(GetKey(olc::Key::X).bReleased)
    // {
    //     m_reg.patch<health>(m_player, [](auto &h){
    //        h.curr += 15;
    //     });
    // }
}


void DungeonThing::on_userinput_combat()
{
    if (CURR_STATE.type == type::PLAYER_SELECTING_ACTION)
    {
        Debugger::instance() += "SELECTING";
        if (GetKey(olc::Key::W).bReleased || GetKey(olc::Key::UP).bReleased)
        {
            m_combat_menus[m_curr_menu].scroll_up();
        }
        if (GetKey(olc::Key::S).bReleased || GetKey(olc::Key::DOWN).bReleased)
        {
            m_combat_menus[m_curr_menu].scroll_down();
        }
        if (GetKey(olc::Key::A).bReleased || GetKey(olc::Key::LEFT).bReleased)
        {
            m_combat_menus[m_curr_menu].scroll_left();
        }
        if (GetKey(olc::Key::D).bReleased || GetKey(olc::Key::RIGHT).bReleased)
        {
            m_combat_menus[m_curr_menu].scroll_right();
        }
        if(GetKey(olc::Key::ENTER).bReleased || GetKey(olc::Key::SPACE).bReleased)
        {
            m_combat_menus[m_curr_menu].select();
        }
    }
    else
    {
        if (GetKey(olc::Key::W).bReleased || GetKey(olc::Key::UP).bReleased)
        {
            m_target_menu.scroll_down();
        }
        if (GetKey(olc::Key::S).bReleased || GetKey(olc::Key::DOWN).bReleased)
        {
            m_target_menu.scroll_down();
        }
        if (GetKey(olc::Key::A).bReleased || GetKey(olc::Key::LEFT).bReleased)
        {
            m_target_menu.scroll_left();
        }
        if (GetKey(olc::Key::D).bReleased || GetKey(olc::Key::RIGHT).bReleased)
        {
            m_target_menu.scroll_right();
        }
        if(GetKey(olc::Key::ENTER).bReleased || GetKey(olc::Key::SPACE).bReleased)
        {
            m_target_menu.select();
        }
    }
}
