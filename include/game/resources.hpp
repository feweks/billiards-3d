#pragma once

#include <raylib.h>
#include <nlohmann/json_fwd.hpp>
#include <string>

namespace game::resources {
void init();

// Load a texture from path and caches it. If texture file is not found or its data is invalid, returns a default 50x50 MAGENTA/BLACK texture instead.
Texture2D get_texture(const std::string &path);

// Loads a model from path and caches it. If model file is not found or its data is invalid, returns a default cube model instead.
Model get_model(const std::string &path);

// Reads entire file content. Returns empty string if file was not found.
std::string get_file(const std::string &path);

// Reads entire file and deserializes it. Returns `NULL` if deserialization failed.
nlohmann::json get_json(const std::string &path);

// Unloads all loaded resources (except default ones).
void unload();

void shutdown();
}  // namespace game::resources
