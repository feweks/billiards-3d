#include "game/states/game_state.hpp"
#include "game/states/main_menu_state.hpp"
#include "game/states/play_state.hpp"
#include "game/game.hpp"
#include <raylib.h>
#include <imgui.h>

namespace game::states {
MainMenuState::MainMenuState() : GameState("main_menu_state", (Vector3){-2, 1, -2}, (Vector3){0, 0, 0}) {}

void MainMenuState::create() {}

void MainMenuState::update(float dt) { GameState::update(dt); }

void MainMenuState::draw() {
    GameState::draw();
    DrawGrid(10, 1);
}

void MainMenuState::draw_ui() {
    GameState::draw_ui();
    DrawText("Billiards", 50, 50, 24, ORANGE);
}

void MainMenuState::draw_imgui() {
    ImGui::Begin("Main Menu");

    if (ImGui::Button("PlayState")) {
        game::change_state<game::states::PlayState>();
    }

    ImGui::End();
}

void MainMenuState::destroy() {}
}  // namespace game::states
