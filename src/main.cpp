#include "../include/SDL2/SDL.h"
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

int selectedRook = -1; // -1: No rook selected, 0: Rook 1 selected, 1: Rook 2 selected

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
                SDL_SetRenderDrawColor(gRenderer, 50, 0, 0, 255); // Light square color
            } else {
                SDL_SetRenderDrawColor(gRenderer, 200, 200, 150, 255); // Dark square color
            }
            SDL_RenderFillRect(gRenderer, &rect);
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
    SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
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

                if (col == rook1X && row == rook1Y) {
                    selectedRook = 0; // Select Rook 1
                } else if (col == rook2X && row == rook2Y) {
                    selectedRook = 1; // Select Rook 2
                } else {
                    selectedRook = -1; // Deselect both rooks
                }
            } else if (e.type == SDL_KEYDOWN && selectedRook != -1) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        if (selectedRook == 0) {
                            if (rook1Y > 0) rook1Y--;
                        } else if (selectedRook == 1) {
                            if (rook2Y > 0) rook2Y--;
                        }
                        break;
                    case SDLK_DOWN:
                        if (selectedRook == 0) {
                            if (rook1Y < 7) rook1Y++;
                        } else if (selectedRook == 1) {
                            if (rook2Y < 7) rook2Y++;
                        }
                        break;
                    case SDLK_LEFT:
                        if (selectedRook == 0) {
                            if (rook1X > 0) rook1X--;
                        } else if (selectedRook == 1) {
                            if (rook2X > 0) rook2X--;
                        }
                        break;
                    case SDLK_RIGHT:
                        if (selectedRook == 0) {
                            if (rook1X < 7) rook1X++;
                        } else if (selectedRook == 1) {
                            if (rook2X < 7) rook2X++;
                        }
                        break;
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
