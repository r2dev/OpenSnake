#include <iostream>
#include <string>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

void renderTex();
SDL_Texture *loadImage();

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

SDL_Window *win = nullptr;
SDL_Renderer *ren = nullptr;

SDL_Texture *loadImage(std::string file) {
    SDL_Texture *tex = IMG_LoadTexture(ren, file.c_str());
    if (tex == nullptr) {
        std::cout << SDL_GetError() << "--- 1 ---" << std::endl;
        return nullptr;
    }
    return tex;
}


void renderTex(SDL_Texture *tex, int x, int y) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(ren, tex, NULL, &pos);
    SDL_RenderPresent(ren);
}

void renderImage(std::string file, int x, int y) {
    SDL_Texture *tex = loadImage(file);
    renderTex(tex, x, y);
}
    

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << SDL_GetError() << "-----init----" <<std::endl;
        return -1;
    }
    if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG) {
        std::cout << "IMG_INIT_ERROR" << std::endl;
    }
    win = SDL_CreateWindow("PNG_TEST1", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //code
    renderImage("back.png", 0, 0);
    renderImage("front.png", 100, 100);
    
    SDL_Delay(2000);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);

    SDL_Quit();
    IMG_Quit();
    return 0;
}
    
