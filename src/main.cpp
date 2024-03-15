#include "banco.h"
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include <iostream>

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

    banco = loadTexture("image/banco.png");
    quanco[0] = loadTexture("image/quanco.png");

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
    
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            int x, y;
            SDL_GetMouseState(&x, &y);
            std::cout << x << ' ' << y << std::endl;
            //     int col = x / SQUARE_SIZE;
            //     int row = y / SQUARE_SIZE;
            // }
        }
        drawBoard();
        drawChess();
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
