#include "raylib.h"
#include "raymath.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#define RECT(a, b, c, d) ((Rectangle){ .x = a, .y = b, .width = c, .height = d })

Camera3D cam;

typedef enum {
    // MAIN WEAPONS
    SLINGSHOT,
    WRENCH,
    TETHER,
    MINELASER,
    RIPPER,
    TOASTER,
    SPEW,
    SCATTER,
    RIVET,
    BAZOOKA,

    // GRENADES
    CORINGG,
    RECRUITG,
    CLEANERG,
} weapon_t;

static const char *paths[] = {
    ".\\data\\Slingshot\\slingshot.obj",
    ".\\data\\Wrench\\wrench.obj",
    ".\\data\\Tether\\ControlTether.obj",
    ".\\data\\MiningLaser1\\MiningLaserLevel1.obj",
    ".\\data\\Ripper\\Ripper.obj",
    ".\\data\\Toaster\\Toaster.obj",
    ".\\data\\Spew1\\Spew1.obj",
    ".\\data\\Scattergun\\ScattergunLV1.obj",
    ".\\data\\Rivetgun2\\RivetgunLV1.obj",
    ".\\data\\RocketLauncher1\\Rocketlauncher.obj",

    ".\\data\\CoringCharge\\CoringCharge.obj",
    ".\\data\\RecruitGrenade\\Recruiter.obj",
    ".\\data\\Cleaner\\Cleaner.obj",
};

weapon_t shownWeapon = (weapon_t)0;

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
    Model model = LoadModel(paths[shownWeapon]);

    while (!WindowShouldClose()) {
        //TODO: Reload model on the fly
        if (IsKeyPressed(KEY_W)) {
            shownWeapon++;
        } else if (IsKeyPressed(KEY_S)) {
            shownWeapon--;
        }

        UpdateCamera(&cam, CAMERA_ORBITAL);

        BeginDrawing();
        ClearBackground(BLACK);

        GuiButton(RECT(5, 5, 50, 25), "#191#Info");

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
