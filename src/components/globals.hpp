#ifndef COMP_GLOBALS_H_
#define COMP_GLOBALS_H_

#include <cstdint>
#include <entt/entt.hpp>
#include <queue>
// struct TransitionState
// {
//     float m_transition_progress;
//     float m_transition_acc;
//     float m_transition_time;
//     float m_elapsed_transition_time;
// };

struct _player{};

struct MenuState
{
    int m_curr_menu;
};

struct PlayerState
{
    uint8_t level;
    uint8_t exp;
    bool has_new_level;
};

struct InventoryState
{
    std::vector<entt::entity> consumables;
    std::vector<entt::entity> equipables[9];
    std::vector<entt::entity> other;
};

struct EquipmentState
{
    entt::entity head;
    entt::entity torso;
    entt::entity legs;
    entt::entity main_hand;
    entt::entity off_hand;
    entt::entity finger_left;
    entt::entity finger_right;
    entt::entity ears;
    entt::entity necklace;
};


struct combat_action{
    entt::entity actor;
    entt::entity action;
    entt::entity target;
    bool aoe;
};

struct CombatState
{
    std::queue<combat_action> player_actions;
    std::queue<combat_action> ally_actions;
    std::queue<combat_action> enemy_actions;

    entt::entity player_intended_action;

    int enemy_amount;
    int enemies_left;
    bool has_won;
};

#endif // COMB_GLOBALS_H_
