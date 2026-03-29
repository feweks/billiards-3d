#pragma once

#include <nlohmann/json_fwd.hpp>
#include <string>

namespace game::resources {
void init();

// Reads entire file content. Returns empty string if file was not found.
std::string get_file(const std::string &path);

// Reads entire file and deserializes it. Returns `NULL` if deserialization failed.
nlohmann::json get_json(const std::string &path);

void shutdown();
}  // namespace game::resources
