#include "kenney-sandbox.h"

static int load_progress;

static void load_enter(struct global_context *gctx) {
    load_progress = 100;
}

static void load_update(struct global_context *gctx) {
}

static void load_draw(struct global_context *gctx) {
    BeginDrawing();

    ClearBackground(WHITE);

    if (load_progress == 100) {
        state_change(gctx, STATE_SANDBOX);
    } else {
        DrawTextCentered(TextFormat("Loading... %i", load_progress/2), GetScreenWidth()/2, GetScreenHeight()/2, 40, BLACK);
    }

    EndDrawing();
}

struct app_state state_load = {
    .init = NULL,
    .deinit = NULL,
    .enter = load_enter,
    .exit = NULL,
    .update = load_update,
    .draw = load_draw
};
