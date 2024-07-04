#pragma once

#include <entt/entt.hpp>

#include <cstdint>
#include <stack>
#include <string>
#include <sstream>
#include <bitset>

#include "utils/debug.hpp"
#include "utils/globals.hpp"


// FIXME move OOP parts away from components

enum STATE {
// rendering
FLIPPED = 0,


// movement
IDLE,
TURNING,
WALKING_EAST,
WALKING_WEST,
JUMPING,
ATTACK_1,


// combat
STUNNED,
HURT,

UNSTOPPABLE,
INVOLNOURABLE,
INVISIBLE,

UNKNOWN = 63
};

inline bitmask to_mask(STATE s){return 1 << (int) s;}
inline bitmask to_mask(const bitmask *s, int amnt)
{
    bitmask mask = 0;
    for(int i = 0; i < amnt; ++i)
        mask ^= s[i];
    return mask;
}


struct State
{
    State(STATE s, std::string n,
        update_world on_enter,
        update_world on_exit,
        check_world  validator
    );
    State(STATE s, std::string n,
        update_world on_enter,
        update_world on_exit
    );
    bitmask mask;
    STATE state;
    std::string name; //debugging
    bitmask blocked_by[32];
    bitmask requirements[32];
    bitmask terminates[32];
    int block_amnt = 0;
    int req_amnt = 0;
    int term_amnt = 0;

    void add_blocker(STATE s);
    void add_requirement(STATE s);
    void add_termination(STATE s);
    bitmask blocking_states();
    bitmask required_states();
    bitmask terminates_states();

    update_world on_enter = nullptr;
    update_world on_exit = nullptr;
    check_world validator = nullptr;

    // bool activatable = false;; // used with validator

    std::string str()
    {
        std::bitset<64> bit(mask);
        std::stringstream ss;
        ss << "State{name(" << name << "), mask(" << bit << ")}";
        return ss.str();
    }
};

class StateManager {

  public:
    StateManager(State &init_state);
    StateManager(State &init_state,std::vector<State> registered_states);

  public:
    void register_state(State &init_state);
    bool validate_states(entt::registry &reg, entt::entity &ent);
    void activate(entt::registry &reg, entt::entity &ent);

    bool give_state(State s);
    // void take_state(State s);

    void deactivate(State state, entt::registry &reg, entt::entity &ent);

  private:
    bool activatable(State state);

    bool is_active(bitmask state);

    bool is_blocked(bitmask blockmask);
    bitmask get_requiring(bitmask mask);
    void queue_activate(State state);

    void try_activate(State state);
    bool has_required_states(bitmask reqmask);

    std::vector<State> get_registered_states(bitmask mask);

    void deactivate(bitmask states, entt::registry &reg, entt::entity &ent);

  private:
    bitmask curr;
    std::stack<State> next;

    // TODO this could also just be a bitmask no ?
    std::unordered_map<bitmask, State> registered_states;


  public:
    std::string str()
    {
        std::bitset<64> bit(curr);
        std::stringstream ss;
        ss << "State_man{registered[ ";
        for(auto &s : registered_states)
            ss << s.second.name << " ";
        ss << "], queued(" << next.size() << "), mask(" << bit << ")}";
        return ss.str();
    }
};
