#include "game/states/game_state.hpp"
#include "game/game.hpp"
#include <raylib.h>
#include <string>
#include <format>

namespace game::states {
GameState::GameState(const std::string &name, Vector3 cam_pos, Vector3 cam_target) {
    this->name = name;
    camera = (Camera3D){
        .position = cam_pos,
        .target = cam_target,
        .up = (Vector3){0, 1, 0},
        .fovy = 75,
        .projection = CameraProjection::CAMERA_PERSPECTIVE,
    };
}

void GameState::update(float dt) {
    if (IsKeyReleased(KEY_F3)) {
        draw_debug_info = !draw_debug_info;
    }
}

void GameState::draw() {}

void GameState::draw_ui() {
    if (!draw_debug_info) return;

    auto cfg = game::get_config();
    std::string msg = std::format("Render resolution: {}x{}\nWindow Resolution: {}x{}\nFullsceen: {}", cfg.render_width, cfg.render_height,
                                  GetScreenWidth(), GetScreenHeight(), IsWindowFullscreen());
    DrawText(msg.c_str(), 5, 24, 12, ColorAlpha(WHITE, 0.75f));
}

const std::string GameState::get_name() const { return name; }
}  // namespace game::states
