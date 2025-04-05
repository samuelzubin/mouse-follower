#include <SDL3/SDL.h>
#include <random>

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

class Box {
    public:
        SDL_FRect rectangle;
        SDL_Renderer* renderer;

        SDL_FRect leftEye;
        SDL_FRect rightEye;
        SDL_FRect mouth1;
        SDL_FRect mouth2;
        SDL_FRect mouth3;

        int WINDOW_SIZE_X;
        int WINDOW_SIZE_Y;

        float xIncrement = randomSpeed();
        float yIncrement = randomSpeed();

        float size;
        int red;
        int green;
        int blue;

        float initialPositionX;
        float initialPositionY;

        Box(SDL_Renderer* renderer, float size, int red, int green, int blue, float initialPositionX, float initialPositionY, int WINDOW_SIZE_X, int WINDOW_SIZE_Y) {
            this->renderer = renderer;
            this->WINDOW_SIZE_X = WINDOW_SIZE_X;
            this->WINDOW_SIZE_Y = WINDOW_SIZE_Y;
            this->size = size;
            this->red = red;
            this->green = green;
            this->blue = blue;
            this->initialPositionX = initialPositionX;
            this->initialPositionY = initialPositionY;

            SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
            rectangle.w = size;
            rectangle.h = size;
            rectangle.x = initialPositionX;
            rectangle.y = initialPositionY;
            SDL_RenderFillRect(renderer, &rectangle);
        }
    
        void draw(float rectPositionX, float rectPositionY) {
            SDL_SetRenderDrawColor(renderer, red, green, blue, SDL_ALPHA_OPAQUE);
            rectangle.w = size;
            rectangle.h = size;
            rectangle.x = rectPositionX;
            rectangle.y = rectPositionY;
            SDL_RenderFillRect(renderer, &rectangle);
        }

        void drawFace(float rectPositionX, float rectPositionY) {
            // Eyes
            drawRectangle(leftEye, renderer, (rectPositionX + rectangle.w / 2) - rectangle.w/10, rectPositionY + (rectangle.h / 6.66667), (size/25), size/3.33333, 0, 0, 0);
            drawRectangle(rightEye, renderer, (rectPositionX + rectangle.w / 2) + rectangle.w/10, rectPositionY + (rectangle.h / 6.66667), (size/25), size/3.33333, 0, 0, 0);
            
            //Mouth
            drawRectangle(mouth1, renderer, (rectPositionX + rectangle.w / 2) - size/3.125, rectPositionY + size/2, size/25, size/3.33333, 0, 0, 0);
            drawRectangle(mouth2, renderer, (rectPositionX + rectangle.w / 2) - size /3.125, rectPositionY + size/1.25, size/1.470588, size/25, 0, 0, 0);
            drawRectangle(mouth3, renderer, (rectPositionX + rectangle.w / 2) + size /3.125, rectPositionY + size/2, size/25, size/3.33333, 0, 0, 0);
        }

        float updateX(float mousePosX) {
            if (rectangle.x + xIncrement < 0 || rectangle.x + rectangle.w + xIncrement > WINDOW_SIZE_X) {
                xIncrement = -xIncrement;
            }
            
            else {
                xIncrement = fabs(xIncrement);
            }

            rectangle.x += (mousePosX - (rectangle.x + rectangle.w / 2)) * xIncrement;
            return rectangle.x;
        }

        float updateY(float mousePosY) {
            if (rectangle.y + yIncrement < 0 || rectangle.y + rectangle.h + yIncrement > WINDOW_SIZE_Y) {
                yIncrement = -yIncrement;
            }
            
            else {
                yIncrement = fabs(yIncrement);
            }
            
            rectangle.y += (mousePosY - (rectangle.y + rectangle.h / 2)) * yIncrement;

            return rectangle.y;
        }
};