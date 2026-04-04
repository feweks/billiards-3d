#include "game/states/play_state.hpp"
#include "game/states/game_state.hpp"
#include "game/trace.hpp"
#include <raylib.h>
#include <raymath.h>
#include <format>

namespace game::states {
PlayState::PlayState() : GameState("play_state", (Vector3){-2, 1, 2}, (Vector3){0, 1, 0}) {}

void PlayState::create() {
    entity_place(entity_create("pool_table", Vector3Zero()));

    pool_balls.reserve(POOL_BALLS_COUNT);
    /*for (int i = 0; i < POOL_BALLS_COUNT; i++) {
        auto ball = entity_create(std::format("pool_ball_{}", i), (Vector3){0, POOL_TABLE_HEIGHT, 0});
        entity_place(ball);

        pool_balls.push_back(ball);
        }*/
    auto ball = entity_create(std::format("pool_ball_{}", 0), (Vector3){0, POOL_TABLE_HEIGHT, 0});
    entity_place(ball);

    pool_balls.push_back(ball);

    pool_cue_ball = entity_create("pool_ball_cue", CUE_BALL_STARTPOS);
    entity_place(pool_cue_ball);
}

void PlayState::update(float dt) {
    GameState::update(dt);
    UpdateCamera(&camera, CameraMode::CAMERA_FREE);

    auto ball = pool_balls[0];
    const float BALL_SPEED = dt * 0.01;

    if (IsKeyDown(KEY_KP_8)) ball->velocity.x += BALL_SPEED;
    if (IsKeyDown(KEY_KP_2)) ball->velocity.x -= BALL_SPEED;
    if (IsKeyDown(KEY_KP_4)) ball->velocity.z += BALL_SPEED;
    if (IsKeyDown(KEY_KP_6)) ball->velocity.z -= BALL_SPEED;

    if (ball->velocity.x > 0) {
        // if (ball->velocity.x <= POOL_BALL_MIN_VEL) ball->velocity.x = 0;
        ball->velocity.x -= BALL_SPEED * 0.5f;
    }

    if (ball->velocity.x < 0) {
        // if (ball->velocity.x >= -POOL_BALL_MIN_VEL) ball->velocity.x = 0;
        ball->velocity.x += BALL_SPEED * 0.5f;
    }

    if (ball->velocity.z > 0) {
        // if (ball->velocity.z <= POOL_BALL_MIN_VEL) ball->velocity.z = 0;
        ball->velocity.z -= BALL_SPEED * 0.5f;
    }

    if (ball->velocity.z < 0) {
        // if (ball->velocity.z >= -POOL_BALL_MIN_VEL) ball->velocity.z = 0;
        ball->velocity.z += BALL_SPEED * 0.5f;
    }
}

void PlayState::draw() {
    GameState::draw();
    DrawGrid(5, 3);
}

void PlayState::draw_ui() {
    GameState::draw_ui();

    std::string pos_txt = std::format("POS: {}, {}, {}", pool_balls[0]->position.x, pool_balls[0]->position.y, pool_balls[0]->position.z);
    DrawText(pos_txt.c_str(), 5, 24, 24, WHITE);

    std::string vel_txt = std::format("VEL: {}, {}, {}", pool_balls[0]->velocity.x, pool_balls[0]->velocity.y, pool_balls[0]->velocity.z);
    DrawText(vel_txt.c_str(), 5, 24 + 24, 24, WHITE);
}

void PlayState::draw_imgui() {}

void PlayState::destroy() {}
}  // namespace game::states
