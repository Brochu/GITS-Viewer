#include "raylib.h"
#include "raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

Camera3D cam;

int main(void) {
    SetTraceLogLevel(LOG_DEBUG);
    TraceLog(LOG_DEBUG, "[GITS-V] Program starting");

    TraceLog(LOG_DEBUG, "[GITS-V] Preparing Raylib Window");
    InitWindow(800, 600, "GITS-Viewer A0");

    TraceLog(LOG_DEBUG, "[GITS-V] Loading Style");
    GuiLoadStyle("styles/style_amber.rgs");

    cam = (Camera3D) {
        .position = (Vector3) { 0.f, 3.f, -10.f },
        .target = (Vector3) { 0.f, 0.f, 0.f },
        .up = (Vector3) { 0.f, 1.f, 0.f },
        .fovy = 45.f,
        .projection = CAMERA_PERSPECTIVE,
    };

    TraceLog(LOG_DEBUG, "[GITS-V] Loading test model");
    const char *path = ".\\data\\Tether\\ControlTether.obj";
    Model model = LoadModel(path);

    while (!WindowShouldClose()) {
        UpdateCamera(&cam, CAMERA_ORBITAL);

        BeginDrawing();
        ClearBackground(BLACK);

        GuiButton((Rectangle){ .x = 5.f, .y = 5.f, .width = 50.f, .height = 25.f }, "#191#Info");

        BeginMode3D(cam);
        DrawModel(model, Vector3Zero(), 2.0f, WHITE);
        EndMode3D();

        EndDrawing();
    }

    TraceLog(LOG_DEBUG, "[GITS-V] Clearing Raylib");
    CloseWindow();

    TraceLog(LOG_DEBUG, "[GITS-V] Program exiting");
    return 0;
}
