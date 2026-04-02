#include "game/states/game_state.hpp"
#include "game/entities/entity.hpp"
#include "game/game.hpp"
#include <raylib.h>
#include <memory>
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

    for (const auto &ent : entities) {
        ent->update(dt);
    }
}

void GameState::draw() {
    for (const auto &ent : entities) {
        ent->draw();
    }
}

void GameState::draw_ui() {
    if (!draw_debug_info) return;

    auto cfg = game::get_config();
    std::string msg = std::format("Render resolution: {}x{}\nWindow Resolution: {}x{}\nFullsceen: {}", cfg.render_width, cfg.render_height,
                                  GetScreenWidth(), GetScreenHeight(), IsWindowFullscreen());
    DrawText(msg.c_str(), 5, 24, 12, ColorAlpha(WHITE, 0.75f));
}

std::shared_ptr<entities::Entity> GameState::entity_create(const std::string &type, Vector3 pos, Vector3 rot, Vector3 scale) {
    return std::make_shared<entities::Entity>(type, pos, rot, scale);
}

void GameState::entity_place(std::shared_ptr<entities::Entity> ent) { entities.push_back(ent); }

const std::string GameState::get_name() const { return name; }
}  // namespace game::states
