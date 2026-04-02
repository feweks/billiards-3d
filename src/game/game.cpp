#include "game/game.hpp"
#include "game/config.hpp"
#include "game/resources.hpp"
#include "game/trace.hpp"
#include "game/states/game_state.hpp"
#include "game/states/main_menu_state.hpp"
#include <raylib.h>
#include <rlImGui.h>
#include <format>
#include <memory>

std::unique_ptr<game::states::GameState> game::cur_state;
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
    rlImGuiSetup(true);

    change_state<game::states::MainMenuState>();
}

void update(float dt) {
    if (dt > DT_THRESHOLD) {
        trace_log(TraceLogLevel::LOG_WARNING, std::format("Normalized DT [{} -> {}]", dt, DT_THRESHOLD));
        dt = DT_THRESHOLD;
    }

    if (game::cur_state) {
        game::cur_state->update(dt);
    }
}

void draw() {
    BeginTextureMode(render_tex);
    ClearBackground(BLACK);

    if (game::cur_state) {
        BeginMode3D(game::cur_state->camera);
        game::cur_state->draw();
        EndMode3D();

        game::cur_state->draw_ui();
    }

    EndTextureMode();
    ClearBackground(BLACK);

    Texture2D rtt = render_tex.texture;
    Rectangle src = {0, 0, (float)rtt.width, (float)-rtt.height};
    Rectangle dest = {0, 0, (float)GetScreenWidth(), (float)GetScreenHeight()};

    DrawTexturePro(rtt, src, dest, (Vector2){0, 0}, 0, WHITE);

    if (game::cur_state) {
        rlImGuiBegin();
        game::cur_state->draw_imgui();
        rlImGuiEnd();
    }

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
