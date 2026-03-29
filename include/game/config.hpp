#pragma once

#include <raylib.h>
#include <string>
#include <vector>

namespace game {
struct Config {
    size_t render_width = 1280;
    size_t render_height = 720;

    std::string title = "Default Window";
    std::vector<ConfigFlags> flags;

    void load();
};
}  // namespace game
