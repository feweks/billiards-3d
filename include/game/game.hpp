#pragma once

#include "game/trace.hpp"
#include "game/states/game_state.hpp"
#include "game/config.hpp"
#include <string>
#include <format>
#include <memory>
#include <type_traits>

namespace game {
extern std::unique_ptr<states::GameState> cur_state;

void init();

void run();

template <typename T>
requires std::is_base_of_v<states::GameState, T>
void change_state() {
    std::string prev_name = "NULL";
    if (cur_state) {
        prev_name = cur_state->get_name();
        cur_state->destroy();
    }

    cur_state = std::make_unique<T>();
    cur_state->create();

    trace_log(TraceLogLevel::LOG_INFO, std::format("Changed state [{} -> {}]", prev_name, cur_state->get_name()));
}

const Config &get_config();

void shutdown();
}  // namespace game
