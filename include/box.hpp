#include <SDL3/SDL.h>
#include <random>

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

        Box(SDL_Renderer* renderer, float size, int red, int green, int blue, float initialPositionX, float initialPositionY, int WINDOW_SIZE_X, int WINDOW_SIZE_Y);
    
        void draw(float rectPositionX, float rectPositionY);

        void drawFace(float rectPositionX, float rectPositionY);

        float updateX(float mousePosX);

        float updateY(float mousePosY);
};
