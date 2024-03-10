#include "../include/SDL2/SDL.h"
#include <stdio.h>
#include <algorithm> // Thêm thư viện để sử dụng std::max và std::min
#include "../logicgame.h" // Include tệp header logicgame.h

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;
const int BOARD_SIZE = 8;
const int SQUARE_SIZE = SCREEN_WIDTH / BOARD_SIZE;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

int rook1X = 0;
int rook1Y = 0;
int rook2X = 560;
int rook2Y = 0;

bool isDraggingRook1 = false;
bool isDraggingRook2 = false;

void veBanCoVaXe() {
    SDL_SetRenderDrawColor(gRenderer, 400, 255, 255, 255); // Set màu nền là màu trắng
    SDL_RenderClear(gRenderer);

    // Vẽ bàn cờ với các ô đen và trắng
    bool isWhiteSquare = true;

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            SDL_Rect square = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
            if (isWhiteSquare) {
                SDL_SetRenderDrawColor(gRenderer, 200, 206, 158, 255); // Màu sáng cho ô trắng
            }
            else {
                SDL_SetRenderDrawColor(gRenderer, 300, 139, 71, 255); // Màu tối cho ô đen
            }
            SDL_RenderFillRect(gRenderer, &square);
            isWhiteSquare = !isWhiteSquare;
        }
        isWhiteSquare = !isWhiteSquare;
    }

    // Vẽ 2 con xe màu đỏ
    SDL_SetRenderDrawColor(gRenderer, 100, 100, 100, 255); // Set màu là màu đỏ
    SDL_Rect rook1 = { rook1X, rook1Y, SQUARE_SIZE, SQUARE_SIZE };
    SDL_Rect rook2 = { rook2X, rook2Y, SQUARE_SIZE, SQUARE_SIZE };
    SDL_RenderFillRect(gRenderer, &rook1);
    SDL_RenderFillRect(gRenderer, &rook2);

    SDL_RenderPresent(gRenderer);
}

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    gWindow = SDL_CreateWindow("Chessboard with SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return -1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);

                if (mouseX >= rook1X && mouseX < rook1X + SQUARE_SIZE && mouseY >= rook1Y && mouseY < rook1Y + SQUARE_SIZE) {
                    isDraggingRook1 = true;
                }
                else if (mouseX >= rook2X && mouseX < rook2X + SQUARE_SIZE && mouseY >= rook2Y && mouseY < rook2Y + SQUARE_SIZE) {
                    isDraggingRook2 = true;
                }
            }
            else if (e.type == SDL_MOUSEBUTTONUP) {
                isDraggingRook1 = false;
                isDraggingRook2 = false;
            }
            else if (e.type == SDL_MOUSEMOTION) {
                if (isDraggingRook1) {
                    rook1X = e.motion.x - SQUARE_SIZE / 2;
                    rook1Y = e.motion.y - SQUARE_SIZE / 2;

                    // Đảm bảo rằng quân xe 1 nằm trọn trong ô mới
                    rook1X = std::max(0, std::min(rook1X, SCREEN_WIDTH - SQUARE_SIZE));
                    rook1Y = std::max(0, std::min(rook1Y, SCREEN_HEIGHT - SQUARE_SIZE));
                }
                else if (isDraggingRook2) {
                    rook2X = e.motion.x - SQUARE_SIZE / 2;
                    rook2Y = e.motion.y - SQUARE_SIZE / 2;

                    // Đảm bảo rằng quân xe 2 nằm trọn trong ô mới
                    rook2X = std::max(0, std::min(rook2X, SCREEN_WIDTH - SQUARE_SIZE));
                    rook2Y = std::max(0, std::min(rook2Y, SCREEN_HEIGHT - SQUARE_SIZE));
                }
            }

            veBanCoVaXe(); // Gọi hàm vẽ bàn cờ và các con xe
        }
    }

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    gRenderer = NULL;

    SDL_Quit();

    return 0;
}
