#include "kenney-sandbox.h"

static struct global_context gctx = {0};

void state_change(struct global_context *gctx, enum state_name next_state) {
    if (next_state < STATE_MAX_) {
        gctx->state_next = gctx->states[next_state];
    }
}

static void UpdateDrawFrame(void) {
    if (gctx.state_current != gctx.state_next) {
        if (gctx.state_current->exit != NULL) {
            gctx.state_current->exit(&gctx);
        }
        if (gctx.state_next->enter != NULL) {
            gctx.state_next->enter(&gctx);
        }
        gctx.state_current = gctx.state_next;
    }
    gctx.state_current->update(&gctx);
    gctx.state_current->draw(&gctx);
}

int main(int argc, char *argv[]) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    SetConfigFlags(FLAG_WINDOW_UNDECORATED);

    InitWindow(RESOLUTION_WIDTH, RESOLUTION_HEIGHT, "kenney-sandbox");

    static struct app_state state_bootstrap = { 0 };
    gctx.state_current = &state_bootstrap;
    gctx.state_next = &state_load;
    gctx.states[STATE_LOAD] = &state_load;
    gctx.states[STATE_SANDBOX] = &state_sandbox;

    // init all states
    for (int i = 0; i < STATE_MAX_; i++) {
        if (gctx.states[i]->init != NULL) {
            gctx.states[i]->init(&gctx);
        }
    }

    SetTargetFPS(60);
    SetExitKey(KEY_NULL);
    while (!gctx.quit && !WindowShouldClose()) {   // Detect window close button or ESC key
        UpdateDrawFrame();
    }

    // deinit all states
    for (int i = 0; i < STATE_MAX_; i++) {
        if (gctx.states[i]->deinit != NULL) {
            gctx.states[i]->deinit(&gctx);
        }
    }

   if (gctx.audio_init) {
       CloseAudioDevice();
   }

    CloseWindow();        // Close window and OpenGL context

    return 0;
}

