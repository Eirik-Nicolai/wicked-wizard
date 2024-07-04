#ifndef GAME_H_
#define GAME_H_

#include "olc/olcPixelGameEngine.h"
#include "olc/olcPGEX_QuickGUI.h"
#include "olc/olcPGEX_TransformedView.h"

#include <queue>
#include <entt/entt.hpp>

#include "utils/utils.hpp"
#include "utils/debug.hpp"

#include "menu.hpp"

#include "types_and_defines.hpp"
#include "components/combat.hpp"
#include "components/assets.hpp"
#include "components/status.hpp"
#include "components/globals.hpp"
#include "components/rendering.hpp"
#include "components/statemachine.hpp"

//#include "engine/animation_manager.hpp"
#include "engine/asset_manager.hpp"

#include "systems/logic/logic.hpp"
#include "systems/movement/moving.hpp"
#include "systems/status/system_status.hpp"
#include "systems/animation/system_animation.hpp"
#include "systems/statemachine/system_statechange.hpp"

#include "box2d/box2d.h"

class Game : public olc::PixelGameEngine
{

    private: // debugging
        entt::entity status_stunned;

    public:
        Game();

        std::unique_ptr<AssetManager> m_assets;

        // std::vector<state> states;

    public:
        bool OnUserCreate() override;
        bool OnUserUpdate(float) override;

    private: //states
        void STATE_WALKING(float);
        void STATE_COMBAT(float);
        void STATE_PAUSE(float);


        void on_load_init();
        void on_load_combat();

        void render();

        void on_userinput_walking();
        void on_userinput_paused();
        void on_userinput_combat();

        bool delay_for(float, float);

    private:
        entt::registry m_reg;
        std::unique_ptr<b2World> m_physics;

        olc::TileTransformedView tv;
        olc::QuickGUI::Manager debugger;
        std::unique_ptr<olc::QuickGUI::Label> l;

        entt::entity m_player;

        GameState CURR_STATE;
        GameState NEXT_STATE;

        float m_animElapsed;
        float m_fPhysicsElapsedTime;
        const float ANIM_TICK = 1.f / 5.f;
        const float PHYSICS_TICK = 1.f / 120.f;

        // EQUIPMENT AND INVENTORY
        SimpleMenu m_pause_menu;

    public:
        // inline std::string get_name(const entt::entity &ent, std::string ret)
        // {
        //     visual v;
        //     if(tryget_component(ent, v))
        //     {
        //         return v.name;
        //     }
        //     return ret;
        // }

        template <typename component>
        void draw_resource_bar(component &c, int x, int y, int w, int h, olc::Pixel col)
        {
            DrawRect(x,y, w, h, col);
            FillRect(x+5,y+5,
                     (w-5)*get_percentage(c.curr, c.max)-5, h-10, olc::WHITE);
        }

    private: //DEBUGGING HELPER FUNCTIONS
        entt::entity create_enemy(std::string, std::string, int);
        entt::entity create_ally(std::string, std::string, int);

        bool follow_player = true;

};


#endif // GAME_H_
