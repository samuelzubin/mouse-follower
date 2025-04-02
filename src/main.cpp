#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

/* Window Size */
const int WINDOW_SIZE_X = 1920/2; //640
const int WINDOW_SIZE_Y = 1080/2; //400

/* Arrow Key movement*/
float xPos =  100; 
float yPos = 0; 
float xIncrement = 0.05;
float yIncrement = 0.05;


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
        SDL_Log("Mouse position: (%f, %f)", event->motion.x, event->motion.y);
    } 

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{
    SDL_FRect rect;

    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* Background color */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */

    /* draw a filled rectangle in the middle of the canvas. */
    SDL_SetRenderDrawColor(renderer, 50, 255, 255, SDL_ALPHA_OPAQUE);  /* rectangle color */
    rect.x = xPos;
    rect.y = yPos;
    rect.w = 200;
    rect.h = 200;
    SDL_RenderFillRect(renderer, &rect);

    if (xPos + xIncrement > WINDOW_SIZE_X - rect.w || xPos + xIncrement < 0) {
        xIncrement = -xIncrement;
    }
  
    if (yPos + yIncrement > WINDOW_SIZE_Y - rect.h || yPos + yIncrement < 0) {
        yIncrement = -yIncrement;
    }

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);

    xPos += xIncrement;
    yPos += yIncrement;

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}