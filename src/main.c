#include "stdio.h"

#include "cimport.h"
#include "scene.h"
#include "postprocess.h"

#include "raylib.h"

int main(void) {
    SetTraceLogLevel(LOG_DEBUG);
    TraceLog(LOG_DEBUG, "[GITS-V] Program starting");

    TraceLog(LOG_DEBUG, "[GITS-V] Setting up assimp logging");
    struct aiLogStream stream;
    stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT, NULL);
    aiAttachLogStream(&stream);

    const char *path = ".\\data\\Slingshot\\slingshot.obj";
    const struct aiScene *scene = aiImportFile(path, aiProcessPreset_TargetRealtime_Quality);
    struct aiMesh *m = scene->mMeshes[0];
    struct aiString name = m->mName;
    size_t numFaces = m->mNumFaces;
    TraceLog(LOG_DEBUG, "[GITS-V] Slingshot mesh: [%zu] '%s'", numFaces, name.data);
    aiReleaseImport(scene);

    TraceLog(LOG_DEBUG, "[GITS-V] Preparing Raylib Window");
    InitWindow(800, 600, "GITS-Viewer A0");

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
    }

    TraceLog(LOG_DEBUG, "[GITS-V] Clearing Raylib");
    CloseWindow();

    TraceLog(LOG_DEBUG, "[GITS-V] Clearing assimp logging");
    aiDetachAllLogStreams();

    TraceLog(LOG_DEBUG, "[GITS-V] Program exiting");
    return 0;
}
