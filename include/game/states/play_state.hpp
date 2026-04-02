#pragma once

#include "game/states/game_state.hpp"

namespace game::states {
class PlayState : public GameState {
   public:
    PlayState();

    void create() override;

    void update(float dt) override;
    void draw() override;
    void draw_ui() override;
    void draw_imgui() override;

    void destroy() override;
};
}  // namespace game::states
