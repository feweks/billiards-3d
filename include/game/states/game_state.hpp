#pragma once

#include <raylib.h>
#include <string>

namespace game::states {
class GameState {
   public:
    Camera3D camera;

    GameState(const std::string &name, Vector3 cam_pos, Vector3 cam_target);

    virtual void create() = 0;

    virtual void update(float dt);

    virtual void draw();

    virtual void draw_ui();

    virtual void destroy() = 0;

    const std::string get_name() const;

   private:
    bool draw_debug_info = false;
    std::string name;
};
}  // namespace game::states
