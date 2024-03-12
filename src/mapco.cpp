#include "mapco.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
const int SQUARE_SIZE = 100;

SDL_Renderer* gRenderer = nullptr;
SDL_Texture* rook1Texture = nullptr;
SDL_Texture* rook2Texture = nullptr;
int rook1X = 0;
int rook1Y = 0;
int rook2X = 7;
int rook2Y = 0;

SDL_Texture* loadTexture(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);

    Uint32 white = SDL_MapRGB(surface->format, 225, 255, 255);
    SDL_SetColorKey(surface, SDL_TRUE, white);

    SDL_FreeSurface(surface);
    return texture;
}

void drawTexture(SDL_Texture* texture, int x, int y) {
    SDL_Rect destRect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
    SDL_RenderCopy(gRenderer, texture, NULL, &destRect);
}

void drawBoard() {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            int centerX = x * SQUARE_SIZE + SQUARE_SIZE / 2;
            int centerY = y * SQUARE_SIZE + SQUARE_SIZE / 2;
            int radius = SQUARE_SIZE / 2;

            if ((x + y) % 2 == 0) {
                SDL_SetRenderDrawColor(gRenderer, 50, 100, 100, 255); // Màu ô sáng
            } else {
                SDL_SetRenderDrawColor(gRenderer, 100, 150, 150, 255); // Màu ô tối
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

void render() {
    SDL_SetRenderDrawColor(gRenderer, 151, 101, 166, 255);
    SDL_RenderClear(gRenderer);
    drawBoard();
    
    drawTexture(rook1Texture, rook1X, rook1Y);
    drawTexture(rook2Texture, rook2X, rook2Y);

    SDL_RenderPresent(gRenderer);
}
