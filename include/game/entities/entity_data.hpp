#pragma once

#include <string>

namespace game::entities {
struct EntityData {
    std::string path = "";
    bool culling = true;

    bool load(const std::string &ent_type);
};
}  // namespace game::entities
