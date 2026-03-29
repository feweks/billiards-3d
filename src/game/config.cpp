#include "game/config.hpp"
#include "game/resources.hpp"
#include <nlohmann/json.hpp>

namespace game {
void Config::load() {
    nlohmann::json cfg_data = resources::get_json("resources/data/game_config.json");
    if (cfg_data == NULL) return;

    render_width = cfg_data.at("render_resolution").at(0);
    render_height = cfg_data.at("render_resolution").at(1);
    title = cfg_data.at("title");

    auto cfg_flags = cfg_data.at("flags");
    for (unsigned int flag : cfg_flags) {
        flags.push_back((ConfigFlags)flag);
    }
}
}  // namespace game
