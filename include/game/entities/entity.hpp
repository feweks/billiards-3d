#pragma once

#include "game/entities/entity_data.hpp"
#include <raylib.h>
#include <string>

namespace game::entities {
class Entity {
   public:
    static inline bool draw_wired = false;

    Vector3 position;
    Vector3 rotation;
    Vector3 scale;
    Vector3 velocity;

    EntityData data;
    Color tint;

    Entity(const std::string &type, Vector3 pos, Vector3 rot, Vector3 scale);

    void set_material_texture(Texture2D tex, MaterialMapIndex type = MaterialMapIndex::MATERIAL_MAP_ALBEDO, int idx = -1);
    void set_material_shader(Shader shd, int idx = -1);

    void update(float dt);
    void draw();

    const std::string &get_type() const;

   private:
    Model mdl_data;
    std::string type;

    Matrix update_transform();
};
}  // namespace game::entities
