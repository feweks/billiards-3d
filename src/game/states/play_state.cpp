#include "game/states/play_state.hpp"
#include "game/states/game_state.hpp"

namespace game::states {
PlayState::PlayState() : GameState("play_state", (Vector3){-2, 0, 2}, (Vector3){0, 1, 0}) {}

void PlayState::create() {}

void PlayState::update(float dt) { GameState::update(dt); }

void PlayState::draw() {
    GameState::draw();
    DrawGrid(5, 3);
}

void PlayState::draw_ui() { GameState::draw_ui(); }

void PlayState::draw_imgui() {}

void PlayState::destroy() {}
}  // namespace game::states
