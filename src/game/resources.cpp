#include "game/resources.hpp"
#include "game/trace.hpp"
#include <raylib.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <format>
#include <unordered_map>

namespace game {
std::unordered_map<std::string, Texture2D> textures;
std::unordered_map<std::string, Model> models;

Texture2D error_tex;
Model error_mdl;

void resources::init() {
    Image error_img = GenImageChecked(50, 50, 25, 25, MAGENTA, BLACK);
    error_tex = LoadTextureFromImage(error_img);
    UnloadImage(error_img);

    Mesh error_mesh = GenMeshCube(1, 1, 1);
    error_mdl = LoadModelFromMesh(error_mesh);
    SetMaterialTexture(&error_mdl.materials[0], MaterialMapIndex::MATERIAL_MAP_ALBEDO, error_tex);
}

Texture2D resources::get_texture(const std::string &path) {
    if (textures.contains(path)) return textures[path];

    if (!std::filesystem::exists(path)) {
        trace_log(TraceLogLevel::LOG_WARNING, std::format("Failed to load texture {}: file not found", path));
        return error_tex;
    }

    Texture2D tex = LoadTexture(path.c_str());

    if (!IsTextureValid(tex)) {
        trace_log(TraceLogLevel::LOG_WARNING, std::format("Failed to load texture {}: invalid data", path));
        return error_tex;
    }

    textures.emplace(path, tex);
    return tex;
}

Model resources::get_model(const std::string &path) {
    if (models.contains(path)) return models[path];

    if (!std::filesystem::exists(path)) {
        trace_log(TraceLogLevel::LOG_WARNING, std::format("Failed to load model {}: file not found", path));
        return error_mdl;
    }

    Model mdl = LoadModel(path.c_str());

    if (!IsModelValid(mdl)) {
        trace_log(TraceLogLevel::LOG_WARNING, std::format("Failed to load model {}: invalid data", path));
        return error_mdl;
    }

    models.emplace(path, mdl);
    return mdl;
}

std::string resources::get_file(const std::string &path) {
    if (!std::filesystem::exists(path)) {
        trace_log(TraceLogLevel::LOG_WARNING, std::format("Failed to load file {}: file not found", path));
        return "";
    }

    std::ifstream file_data(path);
    std::stringstream buf;
    buf << file_data.rdbuf();

    return buf.str();
}

nlohmann::json resources::get_json(const std::string &path) {
    std::string serialized = get_file(path);
    if (serialized == "") {
        trace_log(TraceLogLevel::LOG_WARNING, std::format("Failed to load json {}: invalid data", path));
        return NULL;
    }

    nlohmann::json deserialized = nlohmann::json::parse(serialized);
    return deserialized;
}

void resources::unload() {
    for (auto &tex : textures) {
        UnloadTexture(tex.second);
    }
    textures.clear();

    for (auto &mdl : models) {
        UnloadModel(mdl.second);
    }
    models.clear();
}

void resources::shutdown() {
    unload();

    UnloadTexture(error_tex);
    UnloadModel(error_mdl);
}
}  // namespace game
