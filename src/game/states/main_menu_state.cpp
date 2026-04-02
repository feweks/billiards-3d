#include "game/states/game_state.hpp"
#include "game/states/main_menu_state.hpp"
#include <raylib.h>

namespace game::states {
MainMenuState::MainMenuState() : GameState("main_menu_state", (Vector3){-2, 1, -2}, (Vector3){0, 0, 0}) {}

void MainMenuState::create() {
    auto ent = entity_create("pool_table", (Vector3){0, 0, 0});
    entity_place(ent);
}

void MainMenuState::update(float dt) { GameState::update(dt); }

void MainMenuState::draw() {
    GameState::draw();
    DrawGrid(10, 1);
}

void MainMenuState::draw_ui() {
    GameState::draw_ui();
    DrawText("Billiards", 50, 50, 24, ORANGE);
}

void MainMenuState::destroy() {}
}  // namespace game::states
