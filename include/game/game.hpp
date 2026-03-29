#pragma once

#include "game/config.hpp"

namespace game {
void init();

void run();

const Config &get_config();

void shutdown();
}  // namespace game
