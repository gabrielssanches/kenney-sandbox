#include "kenney-sandbox.h"

static Camera2D camera = { 0 };

static void sandbox_enter(struct global_context *gctx) {
    camera.target = Vector2Zero();
    camera.offset = Vector2Zero();
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

static void sandbox_update(struct global_context *gctx) {
    if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
        Vector2 mouse_delta = GetMouseDelta();
        camera.offset = Vector2Add(camera.offset, mouse_delta);
    }
    camera.zoom += (10*GetMouseWheelMove())/100.0f;
}

static void sandbox_draw(struct global_context *gctx) {
    BeginDrawing();

    ClearBackground(BLACK);

    BeginMode2D(camera);

    // draw screen outline
    Rectangle screen_outline = { 0, 0, 0, 0};
    screen_outline.width = RESOLUTION_WIDTH;
    screen_outline.height = RESOLUTION_HEIGHT;
    DrawRectangleLinesEx(screen_outline, 2.0, RED);

    EndMode2D();

    DrawText(TextFormat("%ix%i@%i zoom:%0.3f", GetScreenWidth(), GetScreenHeight(), GetFPS(), camera.zoom), 30, 30, 30, BLUE);

    EndDrawing();
}

struct app_state state_sandbox = {
    .init = NULL,
    .deinit = NULL,
    .enter = sandbox_enter,
    .exit = NULL,
    .update = sandbox_update,
    .draw = sandbox_draw
};
