 #include "mapco.h"
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
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

    rook1Texture = loadTexture("image/conco-fotor-202403121127(1).png");
    rook2Texture = loadTexture("image/conco-fotor-202403121127(1).png");

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int x, y;
                SDL_GetMouseState(&x, &y);
                int col = x / SQUARE_SIZE;
                int row = y / SQUARE_SIZE;

                if (selectedRook == 0) {
                    rook1X = col;
                    rook1Y = row;
                    selectedRook = -1; // Bỏ chọn quân xe sau khi di chuyển
                } else if (selectedRook == 1) {
                    rook2X = col;
                    rook2Y = row;
                    selectedRook = -1; // Bỏ chọn quân xe sau khi di chuyển
                } else {
                    if (col == rook1X && row == rook1Y) {
                        selectedRook = 0; // Chọn Quân xe 1
                    } else if (col == rook2X && row == rook2Y) {
                        selectedRook = 1; // Chọn Quân xe 2
                    }
                }
            }

            render();
        }
    }

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;

    SDL_Quit();

    return 0;
}