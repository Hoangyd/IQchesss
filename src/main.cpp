#include "banco.h"
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_mixer.h"
#include <iostream>

using namespace std;

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL không thể khởi tạo! Lỗi SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    gWindow = SDL_CreateWindow("IQCHESS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cerr << "Không thể tạo cửa sổ! Lỗi SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cerr << "Không thể tạo renderer! Lỗi SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    int format = MIX_INIT_OGG;
    if (Mix_Init(format) & format != format)
    {
        std::cerr << "Không thể tạo format! Lỗi SDL_Mixer: " << Mix_GetError() << std::endl;
    }
    if (Mix_OpenAudio(44100, AUDIO_S32SYS, 2, 4096) < 0)
    {
        std::cerr << "Không thể mở thiết bị âm thanh! Lỗi SDL_Mixer: " << Mix_GetError() << std::endl;
        return 1;
    }

    banco = loadTexture("image/banco.png");
    for (int i=0;i<3;i++){
        quanco[i] = loadTexture("image/quanco" + std::to_string(i) + ".png");
    }

    for (int i=0;i<7;i++){
        for (int j=0;j<7;j++){
            if (board[i][j]!=1){
                cs[i][j] = nullptr;
            }
            else{
                cs[i][j] = new chess();
            }
        }
    }

    bool quit = false;
    SDL_Event e;
    
    int previous_x=-1, previous_y=-1;
    int current_x=-1, current_y=-1;
    int selected_x=-1, selected_y=-1;
    int mouse_x, mouse_y;
    chess * selected = nullptr;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            SDL_GetMouseState(&mouse_x, &mouse_y);
            current_x = (mouse_x - SCREEN_WIDTH/5.7) / SQUARE_SIZE;
            current_y = (mouse_y - SCREEN_HEIGHT/5.7) / SQUARE_SIZE;
            if (e.type == SDL_MOUSEBUTTONDOWN){
                if (e.button.button == SDL_BUTTON_LEFT){
                    if (selected == nullptr && isAPiece(current_x, current_y)){
                        cs[current_y][current_x]->currentTexture = 2;
                        selected_x = current_x;
                        selected_y = current_y;
                        selected = cs[current_y][current_x];
                        board[current_y][current_x] = 0;
                        cs[current_y][current_x] = nullptr;
                    }
                    else if (selected != nullptr && isEmpty(current_x, current_y)){
                        cs[current_y][current_x] = selected;
                        cs[current_y][current_x]->currentTexture = 1;
                        board[current_y][current_x] = 1;
                        selected = nullptr;
                        selected_x = selected_y = -1;
                    }
                }
            }
        }
        if (current_x != previous_x || current_y != previous_y){
            if (isAPiece(previous_x, previous_y) && (previous_x != selected_x || previous_y != selected_y)){
                cs[previous_y][previous_x]->currentTexture = 0;
            }
            previous_x = current_x;
            previous_y = current_y;
        }
        if (isAPiece(current_x, current_y) && (current_y != selected_y || current_x != selected_x)){
            cs[current_y][current_x]->currentTexture = 1;
        }

        SDL_SetRenderDrawColor(gRenderer, 0,0,0,255);
        SDL_RenderClear(gRenderer);

        drawBoard();
        drawChess();
        if (selected != nullptr){
            SDL_Rect dest;
            dest.w = SQUARE_SIZE - SCREEN_WIDTH/81.8;
            dest.h = SQUARE_SIZE - SCREEN_HEIGHT/81.8;
            dest.x = mouse_x - dest.w/2;
            dest.y = mouse_y - dest.h/2;
            SDL_RenderCopy(gRenderer, quanco[0], NULL, &dest);
        }
        SDL_RenderPresent(gRenderer);
    }
   
    
    for (int i=0;i<7;i++){
        for (int j=0;j<7;j++){
            if (board[i][j]==1){
                delete cs[i][j];
                cs[i][j] = nullptr;
            }
        }
    }

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;
    SDL_Quit();
    return 0;
}
