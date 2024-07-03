#include "game.hpp"
#include "keypress.hpp"
#include <iostream>

void Game::on_userinput_walking()
{
    if (GetKey(olc::Key::A).bPressed)
    {
        m_reg.emplace<_moving_left>(m_player);
    }
    if (GetKey(olc::Key::A).bReleased)
    {
        m_reg.remove<_moving_left>(m_player);
    }

    if (GetKey(olc::Key::D).bPressed)
    {
        m_reg.emplace<_moving_right>(m_player);
    }
    if (GetKey(olc::Key::D).bReleased)
    {
        m_reg.remove<_moving_right>(m_player);
    }

    if (GetKey(olc::Key::SPACE).bPressed)
    {
        m_reg.emplace<_jump>(m_player);
    }

    // // OPEN INVENTORY / PAUSE GAME
    // if (GetKey(olc::Key::I).bReleased)
    // {
    //     NEXT_STATE.state = state::PAUSED;
    //     NEXT_STATE.type = type::INIT;
    // }

    // // DEBUGGING
    // if (GetKey(olc::Key::X).bReleased)
    // {
    //     NEXT_STATE.state = state::COMBAT;
    //     NEXT_STATE.type = type::INIT;
    // }
}

void Game::on_userinput_paused()
{
    // switch(CURR_STATE.type)
    // {
    //     case type::OVERVIEW:
    //     {
    //         if (GetKey(olc::Key::W).bReleased)
    //         {
    //             m_pause_menu.scroll_up();
    //         }
    //         if (GetKey(olc::Key::S).bReleased)
    //         {
    //             m_pause_menu.scroll_down();
    //         }
    //         if(GetKey(olc::Key::ENTER).bReleased)
    //         {
    //             m_pause_menu.select();
    //         }
    //     }
    //     break;
    //     default:
    //         std::cout << "PAUSE TYPE NOT RECOGNISED" << std::endl;
    // }

    // if(GetKey(olc::Key::ESCAPE).bReleased)
    // {
    //     switch(CURR_STATE.type)
    //     {
    //         case type::OVERVIEW:
    //             NEXT_STATE.state = state::WALKING;
    //             NEXT_STATE.type = type::FREEROAM;
    //             break;
    //         default:
    //             NEXT_STATE.type = type::INIT;


    //     }
    // }


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


void Game::on_userinput_combat()
{
    // if (CURR_STATE.type == type::PLAYER_SELECTING_ACTION)
    // {
    //     Debugger::instance() += "SELECTING";
    //     if (GetKey(olc::Key::W).bReleased || GetKey(olc::Key::UP).bReleased)
    //     {
    //         m_combat_menus[m_curr_menu].scroll_up();
    //     }
    //     if (GetKey(olc::Key::S).bReleased || GetKey(olc::Key::DOWN).bReleased)
    //     {
    //         m_combat_menus[m_curr_menu].scroll_down();
    //     }
    //     if (GetKey(olc::Key::A).bReleased || GetKey(olc::Key::LEFT).bReleased)
    //     {
    //         m_combat_menus[m_curr_menu].scroll_left();
    //     }
    //     if (GetKey(olc::Key::D).bReleased || GetKey(olc::Key::RIGHT).bReleased)
    //     {
    //         m_combat_menus[m_curr_menu].scroll_right();
    //     }
    //     if(GetKey(olc::Key::ENTER).bReleased || GetKey(olc::Key::SPACE).bReleased)
    //     {
    //         m_combat_menus[m_curr_menu].select();
    //     }
    // }
    // else
    // {
    //     if (GetKey(olc::Key::W).bReleased || GetKey(olc::Key::UP).bReleased)
    //     {
    //         m_target_menu.scroll_down();
    //     }
    //     if (GetKey(olc::Key::S).bReleased || GetKey(olc::Key::DOWN).bReleased)
    //     {
    //         m_target_menu.scroll_down();
    //     }
    //     if (GetKey(olc::Key::A).bReleased || GetKey(olc::Key::LEFT).bReleased)
    //     {
    //         m_target_menu.scroll_left();
    //     }
    //     if (GetKey(olc::Key::D).bReleased || GetKey(olc::Key::RIGHT).bReleased)
    //     {
    //         m_target_menu.scroll_right();
    //     }
    //     if(GetKey(olc::Key::ENTER).bReleased || GetKey(olc::Key::SPACE).bReleased)
    //     {
    //         m_target_menu.select();
    //     }
    // }
}
