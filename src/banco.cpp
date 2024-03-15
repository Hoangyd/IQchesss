
#include "banco.h"

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;
const int SQUARE_SIZE = 85;
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* banco = nullptr;
SDL_Texture* quanco[3] = {nullptr, nullptr, nullptr};

int board[7][7] = {
    {-1, -1, 1, 1, 1, -1, -1},
    {-1, -1, 1, 1, 1, -1, -1},
    { 1,  1, 1, 1, 1,  1,  1},
    { 1,  1, 1, 0, 1,  1,  1},
    { 1,  1, 1, 1, 1,  1,  1},
    {-1, -1, 1, 1, 1, -1, -1},
    {-1, -1, 1, 1, 1, -1, -1},
};

chess * cs[7][7];

SDL_Texture* loadTexture(const std::string& path) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    if (!texture) {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(surface);
    return texture;
}

void drawChess() {
    for (int i=0;i<7;i++){
        for (int j=0;j<7;j++){
            if (board[i][j]!=1){
                continue;
            }
            SDL_Rect dest;
            dest.x = j * SQUARE_SIZE + 160;
            dest.y = i * SQUARE_SIZE + 160;
            dest.w = SQUARE_SIZE - 15;
            dest.h = SQUARE_SIZE - 15;
            SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
            SDL_RenderCopy(gRenderer, quanco[0], NULL, &dest);
        }
    }
}

void drawBoard() {
    SDL_Rect src;
    src.x = src.y = 0;
    src.w = src.h = 950;
    SDL_Rect dest;
    dest.x = dest.y = 0;
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT;
    SDL_RenderCopy(gRenderer, banco, &src, &dest);
}
// Hàm kiểm tra ô có thể di chuyển
    bool isValidMove(int x, int y) {
        if ((x == 0 && y == 0) || (x == 1 && y == 0) || (x == 0 && y == 1) || (x == 1 && y == 1) ||
            (x == 6 && y == 0) || (x == 6 && y == 1) || (x == 5 && y == 1) || (x == 5 && y == 0) ||
            (x == 0 && y == 5) || (x == 0 && y == 6) || (x == 1 && y == 5) || (x == 1 && y == 6) ||
            (x == 5 && y == 5) || (x == 5 && y == 6) || (x == 6 && y == 5) || (x == 6 && y == 6)) {
            return false; // Ô không thể di chuyển tới
        }
        return true; // Ô có thể di chuyển tới
    }


