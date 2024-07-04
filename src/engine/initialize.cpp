#include "game.hpp"

#include "initialize.hpp"

void test(){}

void Game::on_load_init()
{
    // m_reg.on_construct<ai::_strolling>().connect<&ai::set_init_position_for_strolling>();

    // m_reg.on_update<affected>().connect<&combat::update_stats>();

    // STATE AND GLOBALS

    // m_reg.ctx().emplace<TransitionState>(0.0,5.0,2.0,0.0);
    m_reg.ctx().emplace<MenuState>(0);
    //m_reg.ctx().emplace<PlayerState>(100,100,1,0);

    auto &winsize = GetWindowSize();

    auto player = m_reg.create();
    m_player = player;
    m_reg.emplace<_controllable>(player);

    m_reg.emplace<movement>(player, 100.f, 100.f, 100.f);
    
    // CREATE DYNAMIC BOX
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(600.f, 200.f);
    bodyDef.angularDamping = 10000.f;
    auto body = m_physics->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    auto bodySize = b2Vec2(4.0f, 6.0f);
    dynamicBox.SetAsBox(bodySize.x, bodySize.y);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.5f;

    body->CreateFixture(&fixtureDef);

    body->SetGravityScale(2);
    m_reg.emplace<box2d_ref>(player, body, bodySize);
    // m_reg.emplace<_renderable>(player);

    DEBUG("loading spritesheet");

    size_t i;
    if(!m_assets->load("assets/spritesheets/link.png", i))
        throw std::runtime_error("Couldnt load link.png");


    DEBUG("link sheet indx " + std::to_string(i));

    size_t i_stickboy;
    if(!m_assets->load("assets/spritesheets/stickboy.png", i_stickboy))
        throw std::runtime_error("Couldnt load stickboy");

    DEBUG("stickboy sheet indx " + std::to_string(i_stickboy));

    m_reg.emplace<player_sheet>(
        player,
        i_stickboy
    );

    DEBUG("creating animation frames");
    auto walking_frames_east = std::vector<animation_frame>{
        {olc::vi2d(1,64),   olc::vi2d(64,64), 0.2f, std::vector<hitbox>()},
        {olc::vi2d(65,64),  olc::vi2d(64,64), 0.2f, std::vector<hitbox>()},
    };
    auto walking_frames_west = std::vector<animation_frame>{
        {olc::vi2d(1,64*2),   olc::vi2d(64,64), 0.2f, std::vector<hitbox>()},
        {olc::vi2d(65,64*2),  olc::vi2d(64,64), 0.2f, std::vector<hitbox>()},
    };

    auto idle_frames = std::vector<animation_frame>{
        {olc::vi2d(1,1),   olc::vi2d(64,64), 10, std::vector<hitbox>()},
    };

    auto stunned_frames = std::vector<animation_frame>{
        {olc::vi2d(1,64), olc::vi2d(64,64), 0.01f, std::vector<hitbox>()},
        {olc::vi2d(65,64), olc::vi2d(64,64), 0.01f, std::vector<hitbox>()},
        {olc::vi2d(1,64*2), olc::vi2d(64,64), 0.01f, std::vector<hitbox>()},
        {olc::vi2d(65,64*2), olc::vi2d(64,64), 0.01f, std::vector<hitbox>()},
    };

    DEBUG("creating animation entities");

    auto walking_animation_east = m_reg.create();
    auto walking_animation_west = m_reg.create();

    auto idle_animation = m_reg.create();

    auto stunned_animation = m_reg.create();

    m_reg.emplace<animation>(
        walking_animation_east,
        i_stickboy,
        "walking",
        (uint8_t)0,
        0.f,

        walking_frames_east.size(),
        walking_frames_east
    );

    m_reg.emplace<animation>(
        walking_animation_west,
        i_stickboy,
        "walking",
        (uint8_t)0,
        0.f,

        walking_frames_west.size(),
        walking_frames_west
    );


    m_reg.emplace<animation>(
        idle_animation,
        i_stickboy,
        "idle",
        (uint8_t)0,
        0.f,

        idle_frames.size(),
        idle_frames
    );

    m_reg.emplace<animation>(
        stunned_animation,
        i_stickboy,
        "stunned",
        (uint8_t)0,
        0.f,

        idle_frames.size(),
        idle_frames
    );

    m_reg.emplace<current_animation>(
        player,
        idle_animation
    );

    State idle = State(STATE::IDLE, "idle",
                       [idle_animation](entt::registry& reg, entt::entity &ent){
                           DEBUG("CHANGING TO IDLE ANIM");
                           reg.replace<current_animation>(ent, idle_animation);
                       },
                       [](entt::registry&, entt::entity &){},
                       [](const entt::registry& reg, const entt::entity &ent) // change input method
                       {
                           auto box2d = reg.get<box2d_ref>(ent);
                           auto vel = box2d.ref->GetLinearVelocity().x;
                           // DEBUG("CHECK IDLE " + std::to_string(vel));
                           return vel < 50 && vel > -50;
                       });

    State walking_east = State(STATE::WALKING_EAST, "walking_east",
                          [walking_animation_east](entt::registry& reg, entt::entity &ent){
                              DEBUG("CHANGING TO WALKING EAST ANIM");
                              reg.replace<current_animation>(ent, walking_animation_east);
                          },
                          [](entt::registry&, entt::entity &){},
                          [](const entt::registry& reg, const entt::entity &ent){ // change input method
                              auto box2d = reg.get<box2d_ref>(ent);
                              auto vel = box2d.ref->GetLinearVelocity().x;
                              //DEBUG("CHECK WALKING " + std::to_string(vel));
                              return vel >= 50;
                          });

    State walking_west = State(STATE::WALKING_WEST, "walking_west",
                          [walking_animation_west](entt::registry& reg, entt::entity &ent){
                              DEBUG("CHANGING TO WALKING WEST ANIM");
                              reg.replace<current_animation>(ent, walking_animation_west);
                          },
                          [](entt::registry&, entt::entity &){},
                          [](const entt::registry& reg, const entt::entity &ent){ // change input method
                              auto box2d = reg.get<box2d_ref>(ent);
                              auto vel = box2d.ref->GetLinearVelocity().x;
                              //DEBUG("CHECK WALKING " + std::to_string(vel));
                              return vel <= -50;
                          });

    // effect damage = effect{
    //     .name = "do_damage",
    //     .on_enter = [](entt::registry&, entt::entity &){},
    //     .on_exit = [](entt::registry&, entt::entity &){},
    //     .apply = [](entt::registry&, entt::entity &){
    //         DEBUG("DOING DAMAGE");
    //     }
    // };

    // condition_ticking ticking = condition_ticking{
    //     .name = "ticking_conditon",
    //     .accum_time = 0.f,
    //     .tick_dur = 1.f,
    //     .tick = 0,
    //     .max_ticks = 4,
    // };


    // effect stun = effect{
    //     .name = "do_damage",
    //     .on_enter = [](entt::registry&, entt::entity &){

    //     },
    //     .on_exit = [](entt::registry&, entt::entity &){},
    //     .apply = [](entt::registry&, entt::entity &){
    //     }
    // };

    // condition_timed timed = condition_timed{
    //     .name = "ticking_conditon",
    //     .accum_time = 0.f,
    //     .dur = 5.f
    // };



    walking_west.add_termination(STATE::IDLE);
    walking_east.add_termination(STATE::IDLE);

    idle.add_termination(STATE::WALKING_WEST);
    idle.add_termination(STATE::WALKING_EAST);

    walking_west.add_blocker(STATE::STUNNED);
    walking_east.add_blocker(STATE::STUNNED);
    idle.add_blocker(STATE::STUNNED);

    m_reg.emplace<StateManager>(
        player,
        StateManager(idle, std::vector<State>{
            idle,
            walking_west,
            walking_east,
        })
    );

    m_reg.emplace<status_manager>(
        player,
        std::set<entt::entity>()
    );



    DEBUG(idle);
    DEBUG(walking_west);
    DEBUG(walking_east);



    State stunned_state = State(STATE::STUNNED, "stunned",
                          [stunned_animation](entt::registry& reg, entt::entity &ent){
                              DEBUG("ADDING STUNNED");
                              reg.emplace_or_replace<status_animation>(ent, stunned_animation);
                          },
                          [](entt::registry &reg, entt::entity &ent){
                              DEBUG("REMOVING STUNNED");
                              reg.remove<status_animation>(ent);
                          }
    );

    stunned_state.add_termination(STATE::IDLE);
    stunned_state.add_termination(STATE::WALKING_WEST);
    stunned_state.add_termination(STATE::WALKING_EAST);

    m_reg.emplace<cond_timer>(status_stunned, cond_timer{.accum_time=0, .dur=3});
    m_reg.emplace<onadd_effect>(
        status_stunned,
        "add_stun_state",
        [stunned_state](entt::registry &reg, entt::entity &affected){
            DEBUG("ADDING STATE STUNNED");
            reg.get<StateManager>(affected).give_state(stunned_state);
    });
   m_reg.emplace<continous_effect>(
        status_stunned,
        "add_stun_state",
        [](entt::registry &reg, entt::entity &affected, const float &){
            //DEBUG("WE ARE STUNNED");
    });
   m_reg.emplace<onremove_effect>(
        status_stunned,
        "add_stun_state",
        [stunned_state](entt::registry &reg, entt::entity &affected){
            DEBUG("REMOVE STATE STUNNED");
            reg.get<StateManager>(affected).deactivate(stunned_state, reg, affected);
    });
    auto ground = m_reg.create();

    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(500.f, GetScreenSize().y-300.f);

    auto groundBody = m_physics->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    auto groundBodySize = b2Vec2(400.0f, 10.0f);
    groundBox.SetAsBox(groundBodySize.x, groundBodySize.y);
    groundBody->CreateFixture(&groundBox, 0.0f);

    m_reg.emplace<box2d_ref>(ground, groundBody, groundBodySize);
    m_reg.emplace<_renderable>(ground);


    b2BodyDef groundBodyDef2;
    groundBodyDef2.type = b2_kinematicBody;
    groundBodyDef2.position.Set(1000.f, GetScreenSize().y-400.f);

    auto groundBody2 = m_physics->CreateBody(&groundBodyDef2);

    b2PolygonShape groundBox2;
    auto groundBodySize2 = b2Vec2(400.0f, 10.0f);
    groundBox2.SetAsBox(groundBodySize2.x, groundBodySize2.y);

    b2FixtureDef fixtureDef2;
    fixtureDef2.shape = &groundBox2;
    fixtureDef2.density = 1.0f;
    fixtureDef2.friction = 0.2f;

    groundBody2->CreateFixture(&fixtureDef2);

    auto ground2 = m_reg.create();
    m_reg.emplace<box2d_ref>(ground2, groundBody2, groundBodySize2);
    m_reg.emplace<_renderable>(ground2);


    DEBUG("Loading complete");


}
