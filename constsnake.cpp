#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"
#include "function_snake.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *win = nullptr;
SDL_Renderer *ren = nullptr;
enum Color {
    white, red, yellow, blue, green, black, total
};

SDL_Color color[total] = {{255, 255, 255} //white
                          ,{255, 0, 0} //red
                          ,{255, 255, 0} //yellow
                          ,{0, 0, 255} //blue
                          ,{0, 255, 0} //green
                          ,{0, 0, 0}}; //black                          

bool INIT()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << "SDL_INIT: ERROR" << std::endl;
        success = false;
    }
    if (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG != IMG_INIT_PNG) {
        std::cout << "IMG_INIT: ERROR" << std::endl;
        success = false;
    }
    if (TTF_Init() != 0) {
        std::cout << "TTF_INIT: ERROR" << std::endl;
        success = false;
    }
    return success;
}

SDL_Texture *convertFont(const std::string &text, SDL_Color color, int font_size)
{
    TTF_Font *font = TTF_OpenFont("1.ttf",font_size);
    if (font == nullptr) {
        std::cout << "Font load failed" << std::endl;
        return nullptr;
    }
    SDL_Surface *sur = TTF_RenderText_Blended(font, text.c_str(), color);
    if (sur == nullptr) {
        std::cout << "Surface Create failed" << std::endl;
        return nullptr;
    }
    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, sur);
    if (tex == nullptr) {
        std::cout << "Font Surface can't be rendered" << std::endl;
        return nullptr;
    }
    SDL_FreeSurface(sur);
    return tex;
}

void renderFont(const std::string &text, SDL_Color color, int font_size, int x, int y, int w, int h)
{
    //Render the text to the renderer
    //require the text --- color ---- the size of the font --- the position of the display
    SDL_Texture *tex = convertFont(text, color, font_size);
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    pos.w = w;
    pos.h = h;
    SDL_RenderCopy(ren, tex, NULL, &pos);
}
void Game_Quit()
{
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}
void renderRect(int x, int y) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    pos.w = 20;
    pos.h = 20;
    SDL_SetRenderDrawColor(ren, 0x00, 0xFF, 0x00, 0x00);
    SDL_RenderFillRect(ren, &pos);
    SDL_RenderPresent(ren);
}

void renderBlackRect(int x, int y) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    pos.w = 20;
    pos.h = 20;
    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderFillRect(ren, &pos);
    SDL_RenderPresent(ren);
}

void renderBackground() {
    SDL_Rect fillScreen = {0, 0, 640, 480};
    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderFillRect(ren, &fillScreen); SDL_SetRenderDrawColor(ren, 0xFF, 0x00, 0x00, 0x00);
    for (int i = 0; i <= 480; i = i + 20)        SDL_RenderDrawLine(ren, 0, i, 640, i);
    for (int i = 0; i <= 640; i = i + 20)
        SDL_RenderDrawLine(ren, i, 0, i, 640);
        
    SDL_RenderPresent(ren);
}
void Game_Start()
{
    if (welcome() == false)
        Game_Quit();
    else 
        start();
}

SDL_Texture *loadImage(const std::string imagefile) {
    SDL_Texture *tex = IMG_LoadTexture(ren, imagefile.c_str());
    if (tex == nullptr) {
        std::cout << "No such " << imagefile << "!" << std::endl;
        return nullptr;
    }
    return tex;
}

void renderImage(const std::string imagefile, int x, int y) {
    SDL_Rect pos;
    pos.x = x;
    pos.y = y;
    SDL_Texture *tex = loadImage(imagefile);
    SDL_QueryTexture(tex, NULL, NULL, &pos.w, &pos.h);
    SDL_RenderCopy(ren, tex, NULL, &pos);
}


bool start() {
    renderBackground();
    bool running = true;
    int length = 2;
    int x = 0;
    int y = 0;
    while (running == true) {
        SDL_Event event;       
        while(SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN) {
                switch(event.key.keysym.sym)
                {
                case SDLK_UP:
                    renderRect(x, y-20);
                    y-=20;
                    break;
                case SDLK_DOWN:
                    renderRect(x,y+20);
                    y+=20;
                    break;
                case SDLK_RIGHT:
                    renderRect(x+20, y);
                    x+=20;
                    break;
                case SDLK_LEFT:
                    renderRect(x-20, y);
                    x-=20;
                    break;
                case SDLK_RETURN:break;
                default: break;
                };
            }
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }
    return running;
}


bool welcome()
{
    renderImage("welcome.png", 0, 0);
    renderFont("+Start game", color[black], 30, 350, 300, 200, 50);
    renderFont("-Quit game", color[black], 30, 350, 340, 200, 50);
    SDL_RenderPresent(ren);
    int choice = 1;
    while(1) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                return false;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                case SDLK_DOWN: 
                    SDL_RenderClear(ren);
                    renderImage("welcome.png", 0, 0);
                    renderFont("-Start game", color[black], 30, 350, 300, 200, 50);
                    renderFont("+Quit game", color[black], 30, 350, 340, 200, 50);
                    choice = 0;
                    break;
                case SDLK_UP:
                    SDL_RenderClear(ren);
                    renderImage("welcome.png", 0, 0);
                    renderFont("+Start game", color[black], 30, 350, 300, 200, 50);
                    renderFont("-Quit game", color[black], 30, 350, 340, 200, 50);
                    choice = 1;
                    break;
                case SDLK_RETURN:
                    if (choice == 0)
                        return false;
                    else
                        return true;
                }
            }
            else if (event.type == SDL_KEYUP){
                SDL_RenderPresent(ren);
            }
        }
    }       
}
int main()
{
    INIT();
    win = SDL_CreateWindow("Fat Snake", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    Game_Start();
    Game_Quit();
    return 0;
}
