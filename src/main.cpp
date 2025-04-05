#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "functions.cpp"

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
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Example Renderer Clear", "1.0", "com.example.renderer-clear");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("My Game Window", WINDOW_SIZE_X, WINDOW_SIZE_Y, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    if (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_ESCAPE) {
        return SDL_APP_SUCCESS;
    }

    if (event->type == SDL_EVENT_MOUSE_MOTION) {
        mousePosX = event->motion.x;
        mousePosY = event->motion.y;
    } 
    
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame.*/
SDL_AppResult SDL_AppIterate(void *appstate)
{   
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* Background color */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */

    //Create rectangle object
    static Box myBox(renderer, 200, 50, 255, 255, 0, 0, WINDOW_SIZE_X, WINDOW_SIZE_Y);

    myBox.updateX(mousePosX);
    myBox.updateY(mousePosY);
    myBox.draw(myBox.rectangle.x, myBox.rectangle.y);
    myBox.drawFace(myBox.rectangle.x, myBox.rectangle.y);
    
    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);
    
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}