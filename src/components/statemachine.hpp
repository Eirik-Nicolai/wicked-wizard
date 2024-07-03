#pragma once

#include <entt/entt.hpp>

#include <cstdint>
#include <stack>
#include <string>
#include <sstream>
#include <bitset>

#include "utils/debug.hpp"

// FIXME move OOP parts away from components

enum STATE {
// rendering
FLIPPED,


// movement
IDLE,
TURNING,
WALKING_EAST,
WALKING_WEST,
JUMPING,
ATTACK_1,
UNKNOWN
};

inline long to_mask(STATE s){return 1 << (int) s;}
inline long to_mask(const long *s, int amnt)
{
    long mask = 0;
    for(int i = 0; i < amnt; ++i)
        mask ^= s[i];
    return mask;
}


struct State
{
    State(STATE s, std::string n,
        std::function<void(entt::registry&, entt::entity &)> on_enter,
        std::function<void(entt::registry&, entt::entity &)> on_exit,
        std::function<bool(entt::registry&, entt::entity &)> validator
    );
    long mask;
    std::string name; //debugging
    long blocked_by[32];
    long requirements[32];
    long terminates[32];
    int block_amnt = 0;
    int req_amnt = 0;
    int term_amnt = 0;

    void add_blocker(State s);
    void add_requirement(State s);
    void add_termination(State s);
    long blocking_states();
    long required_states();
    long terminates_states();

    std::function<void(entt::registry&, entt::entity &)> on_enter = nullptr;
    std::function<void(entt::registry&, entt::entity &)> on_exit = nullptr;

    std::function<bool(entt::registry& reg, entt::entity &ent)> validator = nullptr;

    // bool activatable = false;; // used with validator

    std::string str()
    {
        std::bitset<32> bit(mask);
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

    void try_activate(State state);
    bool activatable(State state);

    bool is_active(long state);

    bool is_blocked(long blockmask);
    bool has_required_states(long reqmask);

    void queue_activate(State state);
    void activate(entt::registry &reg, entt::entity &ent);

    void deactivate(long states, entt::registry &reg, entt::entity &ent);

    void deactivate(State state, entt::registry &reg, entt::entity &ent);

    std::vector<State> get_registered_states(long mask);

    long get_requiring(long mask);

  private:
    long curr;
    std::stack<State> next;

    // TODO this could also just be a bitmask no ?
    std::unordered_map<long, State> registered_states;


  public:
    std::string str()
    {
        std::bitset<32> bit(curr);
        std::stringstream ss;
        ss << "State_man{registered[ ";
        for(auto &s : registered_states)
            ss << s.second.name << " ";
        ss << "], queued(" << next.size() << "), mask(" << bit << ")}";
        return ss.str();
    }
};
