#include "game/states/game_state.hpp"
#include "game/states/main_menu_state.hpp"
#include <raylib.h>

namespace game::states {
MainMenuState::MainMenuState() : GameState("MainMenuState", (Vector3){-1, 1, -1}, (Vector3){0, 0, 0}) {}

void MainMenuState::create() {}

void MainMenuState::update(float dt) {}

void MainMenuState::draw() {}

void MainMenuState::draw_ui() { DrawText("Billiards", 50, 50, 24, ORANGE); }

void MainMenuState::destroy() {}
}  // namespace game::states
