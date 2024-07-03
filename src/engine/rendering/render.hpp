#ifndef RENDER_H_
#define RENDER_H_

#include <entt/entt.hpp>
#include "engine/game.hpp"

#include "utils/globals.hpp"

#include "box2d/box2d.h"

#include "components/logic.hpp"
#include "components/physics.hpp"
#include "components/movement.hpp"
#include "components/rendering.hpp"
#include "components/assets.hpp"
#include "components/animation.hpp"

#define MENU_ITEM_OFFS_Y 50

//TODO namespaces
// -------------------------------------
namespace PAUSED
{
    namespace OVERVIEW
    {
        constexpr float EQUIPMENT_POS_X = 0.2;
        constexpr float EQUIPMENT_POS_X_OFFS = 0.3;
        constexpr float EQUIPMENT_POS_Y = 0.1;
        constexpr float EQUIPMENT_POS_Y_OFFS = 0.30;

        constexpr float EQUIPMENT_SIZE_X = 0.65;
        constexpr float EQUIPMENT_SIZE_Y = 0.66;

        constexpr int EQUIPMENT_MAX_STR_LEN = 10*16;

        void draw_equipment(Game*, entt::entity&, std::string&, int x, int y, olc::Pixel c = olc::WHITE);
        std::string get_inv_stats_drawn(Game*, entt::entity&);
    }
}


// -------------------------------------

// TODO check this
inline int GetStringLength(std::string s, int scale)
{
    return s.size() * 8 * scale;
}

inline olc::vi2d screenspace(olc::vi2d offs, b2Vec2 val, b2Vec2 size)
{
    return olc::vi2d(
        val.x-(size.x),
        val.y-(size.y)
    );
};

inline b2Vec2 boxspace(olc::vi2d multiplier, olc::vi2d offs, olc::vi2d val, b2Vec2 size)
{
    return b2Vec2(
        (offs.x*multiplier.x+val.x)/multiplier.x,
        (offs.y*multiplier.y+val.y)/multiplier.y
    );
};

#endif // RENDER_H_
