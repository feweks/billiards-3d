cmake_minimum_required(VERSION 3.16)

project(billiards LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

include(FetchContent)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/raylib
)

FetchContent_MakeAvailable(raylib)

FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/nlohmann-json
)

FetchContent_MakeAvailable(nlohmann_json)

FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.92.7
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/imgui
)

FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
    rlimgui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
    GIT_TAG main
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/rlImGui
)

FetchContent_MakeAvailable(rlimgui)

add_library(imgui
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_draw.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_widgets.cpp
    ${CMAKE_SOURCE_DIR}/external/imgui/imgui_tables.cpp
)

target_include_directories(imgui PUBLIC
    ${CMAKE_SOURCE_DIR}/external/imgui
)

add_library(rlimgui
    ${CMAKE_SOURCE_DIR}/external/rlImGui/rlImGui.cpp
)

target_include_directories(rlimgui PUBLIC
    ${CMAKE_SOURCE_DIR}/external/rlImGui
    ${CMAKE_SOURCE_DIR}/external/imgui
)

target_link_libraries(rlimgui
    raylib
    imgui
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    raylib
    nlohmann_json::nlohmann_json
    imgui
    rlimgui
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets/resources
        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/resources
)
