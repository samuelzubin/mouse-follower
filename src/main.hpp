#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "box.hpp"
#include "helpers.hpp"

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

/* Window Size */
const int WINDOW_SIZE_X = 1920/2;
const int WINDOW_SIZE_Y = 1080/2;

/* Mouse following */
float mousePosX;
float mousePosY;

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]);

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event);

/* This function runs once per frame.*/
SDL_AppResult SDL_AppIterate(void *appstate);

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result);
