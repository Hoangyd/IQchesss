#include "../include/SDL2/SDL.h"
#include <iostream>
#include <cmath>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int SQUARE_SIZE = 100;

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;

int rook1X = 0;
int rook1Y = 0;
int rook2X = 7;
int rook2Y = 0;

int selectedRook = -1; // -1: No rook selected, 0: Rook 1 selected, 1: Rook 2 selected

void drawBoard() {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            int centerX = x * SQUARE_SIZE + SQUARE_SIZE / 2;
            int centerY = y * SQUARE_SIZE + SQUARE_SIZE / 2;
            int radius = SQUARE_SIZE / 2;

            if ((x + y) % 2 == 0) {
                SDL_SetRenderDrawColor(gRenderer, 50, 100, 100, 255); // Light square color
            } else {
                SDL_SetRenderDrawColor(gRenderer, 100, 20, 150, 255); // Dark square color
            }

            for (int i = 0; i < 360; ++i) {
                float angle = i * M_PI / 180;
                int circleX = centerX + radius * cos(angle);
                int circleY = centerY + radius * sin(angle);
                SDL_RenderDrawPoint(gRenderer, circleX, circleY);
            }
        }
    }
}

void drawRook(int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, 255);
    SDL_Rect rect;
    rect.x = x * SQUARE_SIZE + SQUARE_SIZE / 4;
    rect.y = y * SQUARE_SIZE + SQUARE_SIZE / 4;
    rect.w = SQUARE_SIZE / 2;
    rect.h = SQUARE_SIZE / 2;
    SDL_RenderFillRect(gRenderer, &rect);
}

void render() {
    SDL_SetRenderDrawColor(gRenderer, 151, 201, 166, 255);
    SDL_RenderClear(gRenderer);
    drawBoard();
    
    drawRook(rook1X, rook1Y, {255, 0, 0}); // Red rook
    drawRook(rook2X, rook2Y, {0, 255, 0}); // Green rook

    SDL_RenderPresent(gRenderer);
}

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    gWindow = SDL_CreateWindow("Chess Board", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

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
                    selectedRook = -1; // Deselect the rook after moving
                } else if (selectedRook == 1) {
                    rook2X = col;
                    rook2Y = row;
                    selectedRook = -1; // Deselect the rook after moving
                } else {
                    if (col == rook1X && row == rook1Y) {
                        selectedRook = 0; // Select Rook 1
                    } else if (col == rook2X && row == rook2Y) {
                        selectedRook = 1; // Select Rook 2
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
