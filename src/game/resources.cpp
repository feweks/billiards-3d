#include "game/resources.hpp"
#include "game/trace.hpp"
#include <raylib.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <format>

namespace game {
void resources::init() {}

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

void resources::shutdown() {}
}  // namespace game
