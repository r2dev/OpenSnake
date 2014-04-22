#include <iostream>
#include <SDL2/SDL.h>

const int SCREEN_WIDTH = 480 * 1.618; //the width of the screen
const int SCREEN_HEIGHT = 480; //the height of the screen

SDL_Window *win = nullptr;
SDL_Renderer *ren = nullptr;



SDL_Texture *displayIMG(std::string filename)
{
    SDL_Texture *tex = nullptr;
    SDL_Surface *image = nullptr;
    image = SDL_LoadBMP(filename.c_str());
    if (image == 0)
        std::cout << SDL_GetError() << std::endl;
    else {
        tex = SDL_CreateTextureFromSurface(ren, image);
        SDL_FreeSurface(image);
    }
    return tex;
}

void ApplySurface(int x, int y, SDL_Renderer *ren, SDL_Texture *tex) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(ren, tex, NULL, &pos);
}

int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }
    win = SDL_CreateWindow("my second", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    if ((win == nullptr) || (ren == nullptr)) {
        std::cout << SDL_GetError() << std::endl;
        return -2;
    }
    
    SDL_Texture *background = nullptr;
    SDL_Texture *object = nullptr;
    
    background = displayIMG("good.bmp");
    object = displayIMG("hello.bmp");
    
    if ((background == nullptr) || (object == nullptr)) {
        std::cout << SDL_GetError() << std::endl;
        return -3;
    }
    
    SDL_RenderClear(ren);
    ApplySurface(0, 0, ren, background);
    ApplySurface(30, 40, ren, object);
    SDL_RenderPresent(ren);
    SDL_Delay(20000);
    return 0;
}
       
    
            