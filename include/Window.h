#include <SDL.h>
#include <iostream>
#include <cstdint>

using namespace std;

class Window
{
public:
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    int width = 400;
    int height = 400;

    bool init();
    void renderFrame(uint32_t *frameBuffer);
    void close();
};