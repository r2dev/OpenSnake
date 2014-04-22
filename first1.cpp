#include <SDL2/SDL.h>
#include <iostream>
int main()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *win;
    win = SDL_CreateWindow("My first small try", 100, 100, (480 * 1.6), 480, SDL_WINDOW_SHOWN);
 
   if (win == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }
    
    SDL_Renderer *ren = nullptr;
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }

    SDL_Surface *bmp = nullptr;
    bmp = SDL_LoadBMP("hello.bmp");
    
    if (bmp == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }
    
    SDL_Texture *tex = nullptr;
    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    SDL_RenderClear(ren);
    SDL_RenderCopy(ren, tex, NULL, NULL);
    SDL_RenderPresent(ren);
    SDL_Delay(2000);
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);    
    SDL_Quit();
}
     
        