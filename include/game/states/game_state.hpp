#pragma once

#include "game/entities/entity.hpp"
#include <raylib.h>
#include <raymath.h>
#include <string>
#include <vector>
#include <memory>

namespace game::states {
class GameState {
   public:
    Camera3D camera;

    GameState(const std::string &name, Vector3 cam_pos, Vector3 cam_target);

    virtual void create() = 0;

    virtual void update(float dt);
    virtual void draw();
    virtual void draw_ui();

    std::shared_ptr<entities::Entity> entity_create(const std::string &type, Vector3 pos, Vector3 rot = Vector3Zero(), Vector3 scale = Vector3One());
    void entity_place(std::shared_ptr<entities::Entity> ent);

    virtual void destroy() = 0;

    const std::string get_name() const;

   private:
    bool draw_debug_info = false;
    std::string name;
    std::vector<std::shared_ptr<entities::Entity>> entities;
};
}  // namespace game::states
