#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

void drawRectangle(SDL_FRect rectangle, SDL_Renderer *renderer, float x, float y, int width, int height, int red, int green, int blue) {
    SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = width;
    rectangle.h = height;
    SDL_RenderFillRect(renderer, &rectangle);
}