#include "include\SDL2\SDL.h"
#include <iostream>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int SQUARE_SIZE = 100;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

int rook1X = 0;
int rook1Y = 0;
int rook2X = 7;
int rook2Y = 0;

void drawBoard() {
    SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
    SDL_Rect rect;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            rect.x = x * SQUARE_SIZE;
            rect.y = y * SQUARE_SIZE;

            if ((x + y) % 2 == 0) {
                SDL_SetRenderDrawColor(gRenderer, 255, 206, 158, 255); // Light square color
            } else {
                SDL_SetRenderDrawColor(gRenderer, 209, 139, 71, 255); // Dark square color
            }
            SDL_RenderFillRect(gRenderer, &rect);
        }
    }
}

void drawPiece(int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, 255);
    SDL_Rect rect;
    rect.x = x * SQUARE_SIZE + SQUARE_SIZE / 4;
    rect.y = y * SQUARE_SIZE + SQUARE_SIZE / 4;
    rect.w = SQUARE_SIZE / 2;
    rect.h = SQUARE_SIZE / 2;
    SDL_RenderFillRect(gRenderer, &rect);
}

void render() {
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
    SDL_RenderClear(gRenderer);
    drawBoard();
    
    drawPiece(rook1X, rook1Y, {0, 0, 255}); // blue rook
    drawPiece(rook2X, rook2Y, {0, 0, 255}); // blue rook

    SDL_RenderPresent(gRenderer);
}

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

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

                if ((col == rook1X && row == rook1Y) || (col == rook2X && row == rook2Y)) {
                    if (col == rook1X && row == rook1Y) {
                        rook1X = col;
                        rook1Y = row;
                    } else if (col == rook2X && row == rook2Y) {
                        rook2X = col;
                        rook2Y = row;
                    }
                }
            }
        }
        render();
    }

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    return 0;
}
