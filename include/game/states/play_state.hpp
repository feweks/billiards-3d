#pragma once

#include "game/states/game_state.hpp"
#include "game/entities/entity.hpp"
#include <memory>
#include <vector>

namespace game::states {
class PlayState : public GameState {
   public:
    static constexpr size_t POOL_BALLS_COUNT = 16;
    static constexpr float POOL_TABLE_HEIGHT = 1.0f;
    static constexpr float POOL_BALL_MIN_VEL = 0;
    static constexpr float POOL_BALL_MAX_VEL = 10;
    static constexpr Vector3 CUE_BALL_STARTPOS = (Vector3){0, POOL_TABLE_HEIGHT, 0.5f};

    std::vector<std::shared_ptr<entities::Entity>> pool_balls;
    std::shared_ptr<entities::Entity> pool_cue_ball;

    PlayState();

    void create() override;

    void update(float dt) override;
    void draw() override;
    void draw_ui() override;
    void draw_imgui() override;

    void destroy() override;
};
}  // namespace game::states
