#pragma once

#include "game/states/game_state.hpp"

namespace game::states {
class MainMenuState : public GameState {
   public:
    MainMenuState();

    void create() override;

    void update(float dt) override;
    void draw() override;
    void draw_ui() override;

    void destroy() override;
};
}  // namespace game::states
