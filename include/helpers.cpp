#include "helpers.hpp"

void drawRectangle(SDL_FRect rectangle, SDL_Renderer *renderer, float x, float y, int width, int height, int red, int green, int blue) {
    SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = width;
    rectangle.h = height;
    SDL_RenderFillRect(renderer, &rectangle);
}

float randomSpeed() {
    float min = 0.00008;
    float max = 0.0002;
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}
