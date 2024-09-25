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
    COUNT,
} weapon_t;

typedef struct {
    weapon_t type;
    int levels;
    const char *paths[3];
} weapon_data_t;

static const weapon_data_t weapon_data[] = {
    { .type = 0, .levels = 1, .paths = {".\\data\\Slingshot\\slingshot.obj"} },
    { .type = 1, .levels = 1, .paths = {".\\data\\Wrench\\wrench.obj"} },
    { .type = 2, .levels = 1, .paths = {".\\data\\Tether\\ControlTether.obj"} },
    { .type = 3, .levels = 3, .paths = {
        ".\\data\\MiningLaser1\\MiningLaserLevel1.obj",
        "",
        ""
    } },
    { .type = 4, .levels = 1, .paths = {".\\data\\Ripper\\Ripper.obj"} },
    { .type = 5, .levels = 1, .paths = {".\\data\\Toaster\\Toaster.obj"} },
    { .type = 6, .levels = 3, .paths = {
        ".\\data\\Spew1\\Spew1.obj",
        "",
        "",
    } },
    { .type = 7, .levels = 2, .paths = {
        ".\\data\\Scattergun\\ScattergunLV1.obj",
        "",
    } },
    { .type = 8, .levels = 3, .paths = {
        ".\\data\\Rivetgun2\\RivetgunLV1.obj",
        "",
        "",
    } },
    { .type = 9, .levels = 3, .paths = {
        ".\\data\\RocketLauncher1\\Rocketlauncher.obj",
        "",
        "",
    } },

    { .type = 10, .levels = 1, .paths = {".\\data\\CoringCharge\\CoringCharge.obj"} },
    { .type = 11, .levels = 1, .paths = {".\\data\\RecruitGrenade\\Recruiter.obj"} },
    { .type = 12, .levels = 1, .paths = {".\\data\\Cleaner\\Cleaner.obj"} },
};

static const char *names[] = {
    "Slingshot",
    "Wrench",
    "Tether",
    "Mining Laser",
    "Ripper",
    "Toaster",
    "Spew",
    "Scatter",
    "Rivet Gun",
    "Rocket Launcher",

    "Coring Charge",
    "Recruiter Grenade",
    "Cleaner",
};

weapon_t selectedWeapon = SLINGSHOT;
bool picking = false;
const char *options = NULL;
int levelIndex = 0;

Model model = { 0 };

int main(void) {
    SetTraceLogLevel(LOG_DEBUG);
    TraceLog(LOG_DEBUG, "[GITS-V] Program starting");

    TraceLog(LOG_DEBUG, "[GITS-V] Preparing Raylib Window");
    InitWindow(800, 600, "GITS-Viewer A-0.1");
    TraceLog(LOG_DEBUG, "[GITS-V] Loading Style");
    GuiLoadStyle("styles/style_amber.rgs");

    cam = (Camera3D) {
        .position = (Vector3) { 0.f, 3.f, -10.f },
        .target = (Vector3) { 0.f, 0.f, 0.f },
        .up = (Vector3) { 0.f, 1.f, 0.f },
        .fovy = 45.f,
        .projection = CAMERA_PERSPECTIVE,
    };

    TraceLog(LOG_DEBUG, "[GITS-V] Loading initial model data");
    const weapon_data_t *current = &weapon_data[selectedWeapon];
    model = LoadModel(current->paths[0]);
    options = TextJoin(names, COUNT, ";");

    while (!WindowShouldClose()) {
        //TODO: Better handling of choosing the rendered weapon
        if (IsKeyPressed(KEY_W)) {
            selectedWeapon++;
            if (selectedWeapon >= COUNT) selectedWeapon = COUNT - 1;
        } else if (IsKeyPressed(KEY_S)) {
            selectedWeapon--;
            if (selectedWeapon < 0) selectedWeapon = 0;
        }

        if (selectedWeapon != current->type) {
            UnloadModel(model);

            current = &weapon_data[selectedWeapon];
            model = LoadModel(current->paths[0]);
            levelIndex = 0;
        }

        UpdateCamera(&cam, CAMERA_ORBITAL);

        BeginDrawing();
        ClearBackground((Color){ .r = 0, .g = 0, .b = 25, .a = 255 });

        BeginMode3D(cam);
        DrawModel(model, Vector3Zero(), 2.0f, WHITE);
        EndMode3D();

        char buffer[256] = "";
        sprintf_s(buffer, 256, "Drawing %s", names[selectedWeapon]);
        GuiStatusBar(RECT(0, 600-25, 800, 25), buffer);

        GuiPanel(RECT(0, 0, 800, 25), "Controls");
        if (GuiDropdownBox(RECT(15, 28, 150, 15), options, (int *)&selectedWeapon, picking)) {
            picking = !picking;
        }
        (void)levelIndex;
        //TODO: Draw control to select level of weapon

        EndDrawing();
    }

    TraceLog(LOG_DEBUG, "[GITS-V] Cleanup loaded model");
    UnloadModel(model);
    TraceLog(LOG_DEBUG, "[GITS-V] Clearing Raylib");
    CloseWindow();
    TraceLog(LOG_DEBUG, "[GITS-V] Program exiting");
    return 0;
}
