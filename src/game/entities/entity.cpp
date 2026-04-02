#include "game/entities/entity.hpp"
#include "game/resources.hpp"
#include "game/trace.hpp"
#include <raylib.h>
#include <raymath.h>
#include <rlgl.h>
#include <format>

namespace game::entities {
Entity::Entity(const std::string &type, Vector3 pos, Vector3 rot, Vector3 scale) {
    this->position = pos;
    this->rotation = rot;
    this->scale = scale;

    this->type = type;
    tint = WHITE;
    mdl_data = {0};

    if (data.load(this->type)) {
        mdl_data = resources::get_model(data.path);
        trace_log(TraceLogLevel::LOG_INFO, std::format("Loaded entity {} succesfully from {}", type, data.path));
    }
}

void Entity::update(float dt) { mdl_data.transform = update_transform(); }

void Entity::draw() {
    if (!data.culling) rlDisableBackfaceCulling();
    if (draw_wired)
        DrawModelWires(mdl_data, (Vector3){0, 0, 0}, 1, tint);
    else
        DrawModel(mdl_data, (Vector3){0, 0, 0}, 1, tint);
    if (!data.culling) rlEnableBackfaceCulling();
}

const std::string &Entity::get_type() const { return this->type; }

Matrix Entity::update_transform() {
    Matrix mat_scale = MatrixScale(scale.x, scale.y, scale.z);

    Matrix mat_rot_x = MatrixRotateX(rotation.x * DEG2RAD);
    Matrix mat_rot_y = MatrixRotateY(rotation.y * DEG2RAD);
    Matrix mat_rot_z = MatrixRotateZ(rotation.z * DEG2RAD);

    Matrix mat_rot = MatrixMultiply(MatrixMultiply(mat_rot_z, mat_rot_y), mat_rot_x);

    Matrix mat_trans = MatrixTranslate(position.x, position.y, position.z);

    Matrix transform = MatrixMultiply(mat_scale, mat_rot);
    transform = MatrixMultiply(transform, mat_trans);

    return transform;
}
}  // namespace game::entities
