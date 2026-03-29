#include "game/game.hpp"
#include "game/config.hpp"
#include "game/resources.hpp"
#include "game/trace.hpp"
#include <raylib.h>
#include <format>

game::Config config;
RenderTexture2D render_tex;
const float DT_THRESHOLD = 0.3;

void game::init() {
    config.load();

    for (ConfigFlags flag : config.flags) {
        SetConfigFlags(flag);
    }

    InitWindow(1280, 720, config.title.c_str());
    InitAudioDevice();

    resources::init();

    render_tex = LoadRenderTexture(config.render_width, config.render_height);
}

void update(float dt) {
    if (dt > DT_THRESHOLD) {
        trace_log(TraceLogLevel::LOG_WARNING, std::format("Normalized DT [{} -> {}]", dt, DT_THRESHOLD));
        dt = DT_THRESHOLD;
    }
}

void draw() {
    BeginTextureMode(render_tex);
    ClearBackground(BLACK);

    EndTextureMode();
    ClearBackground(BLACK);

    Texture2D rtt = render_tex.texture;
    Rectangle src = {0, 0, (float)rtt.width, (float)-rtt.height};
    Rectangle dest = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};

    DrawTexturePro(rtt, src, dest, (Vector2){0, 0}, 0, WHITE);

    DrawFPS(5, 3);

    EndDrawing();
}

void game::run() {
    while (!WindowShouldClose()) {
        update(GetFrameTime());
        draw();
    }
}

const game::Config &game::get_config() { return config; }

void game::shutdown() {
    resources::shutdown();

    CloseWindow();
}
