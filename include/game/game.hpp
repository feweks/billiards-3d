#pragma once

#include "game/states/game_state.hpp"
#include "game/config.hpp"
#include <type_traits>

namespace game {
void init();

void run();

template <typename T>
requires std::is_base_of_v<states::GameState, T>
void change_state();

const Config &get_config();

void shutdown();
}  // namespace game
