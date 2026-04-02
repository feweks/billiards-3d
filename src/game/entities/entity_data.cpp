#include "game/entities/entity_data.hpp"
#include "game/resources.hpp"
#include "game/trace.hpp"
#include <raylib.h>
#include <nlohmann/json.hpp>
#include <format>

namespace game::entities {
bool EntityData::load(const std::string &ent_type) {
    std::string ent_path = std::format("resources/data/entities/{}.json", ent_type);
    auto ent_cfg = resources::get_json(ent_path);

    if (ent_cfg == NULL) {
        trace_log(TraceLogLevel::LOG_WARNING, std::format("Failed to load ent {}: invalid config data", ent_type));
        return false;
    }

    this->path = ent_cfg["path"];
    this->culling = ent_cfg["culling"];

    return true;
}
}  // namespace game::entities
