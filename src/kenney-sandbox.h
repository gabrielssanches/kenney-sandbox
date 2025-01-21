#ifndef KENNEY_SANDBOX_H 
#define KENNEY_SANDBOX_H 

#include <raylib.h>
#include <raymath.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "raylib_ext.h"

#ifdef _DEBUG
#define DEBUG_PRINT(fmt, ...) \
    do { \
        fprintf(stderr, "[%s:%d] " fmt, __FILE__, __LINE__, ##__VA_ARGS__); \
    } while (0)
#else
#define DEBUG_PRINT(fmt, ...) do {} while (0)
#endif

#define RESOLUTION_WIDTH 1280
#define RESOLUTION_HEIGHT 720

enum state_name {
    STATE_LOAD,
    STATE_SANDBOX,

    STATE_MAX_
};

enum soundfx {
    SFX_MAX_
};

struct global_context {
    bool audio_init;
    bool quit;
    struct app_state *state_current;
    struct app_state *state_next;
    struct app_state *states[STATE_MAX_];
};

typedef void (*app_func_t)(struct global_context *);

struct app_state {
    app_func_t init;
    app_func_t deinit;
    app_func_t enter;
    app_func_t exit;
    app_func_t update;
    app_func_t draw;
};


void state_change(struct global_context *gctx, enum state_name next_state);

extern struct app_state state_load;
extern struct app_state state_sandbox;

#endif // KENNEY_SANDBOX_H 
