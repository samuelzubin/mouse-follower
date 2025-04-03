#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "functions.cpp"
#include <cmath>

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;

/* Window Size */
const int WINDOW_SIZE_X = 1920/2;
const int WINDOW_SIZE_Y = 1080/2;

/* Box movement*/
float xPos =  100; 
float yPos = 0; 
float xIncrement = 0.0001;
float yIncrement = 0.0001;

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

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{   
    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* Background color */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */

    //Create rectangle objects
    SDL_FRect rect;
    SDL_FRect leftEye;
    SDL_FRect rightEye;
    SDL_FRect mouth1;
    SDL_FRect mouth2;
    SDL_FRect mouth3;
    
    /* draw a filled rectangle in the middle of the canvas. */
    SDL_SetRenderDrawColor(renderer, 50, 255, 255, SDL_ALPHA_OPAQUE);  /* rectangle color */
    rect.x = xPos;
    rect.y = yPos;
    rect.w = 200;
    rect.h = 200;
    SDL_RenderFillRect(renderer, &rect);
    
    if (xPos + xIncrement < 0 || xPos + rect.w + xIncrement > WINDOW_SIZE_X) {
        xIncrement = -xIncrement;
    }
    
    else {
        xIncrement = fabs(xIncrement);
    }
    
    if (yPos + yIncrement < 0 || yPos + rect.h + yIncrement > WINDOW_SIZE_Y) {
        yIncrement = -yIncrement;
    }
    
    else {
        yIncrement = fabs(yIncrement);
    }
    
    xPos += (mousePosX - (xPos + rect.w / 2)) * xIncrement;
    yPos += (mousePosY - (yPos + rect.h / 2)) * yIncrement;

    // Eyes
    drawRectangle(leftEye, renderer, (xPos + rect.w / 2) - 20, yPos + 30, 8, 60, 0, 0, 0);
    drawRectangle(rightEye, renderer, (xPos + rect.w / 2) + 20, yPos + 30, 8, 60, 0, 0, 0);
    
    //Mouth
    drawRectangle(rightEye, renderer, (xPos + rect.w / 2) - 64,yPos + 100, 8, 60, 0, 0, 0);
    drawRectangle(rightEye, renderer, (xPos + rect.w / 2) - 64, yPos + 160, 136, 8, 0, 0, 0);
    drawRectangle(rightEye, renderer, (xPos + rect.w / 2) + 64, yPos + 100, 8, 60, 0, 0, 0);

    /* put the newly-cleared rendering on the screen. */
    SDL_RenderPresent(renderer);
    
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}