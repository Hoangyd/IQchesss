
#include "banco.h"

const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 900;
const int SQUARE_SIZE = SCREEN_WIDTH/10.588;
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* banco = nullptr;
SDL_Texture* quanco[3] = {nullptr, nullptr, nullptr};
Mix_Music* bg_music = nullptr;

int board[7][7] = {
    {-1, -1, 1, 1, 1, -1, -1},
    {-1, -1, 1, 1, 1, -1, -1},
    { 1,  1, 1, 1, 1,  1,  1},
    { 1,  1, 1, 0, 1,  1,  1},
    { 1,  1, 1, 0, 1,  1,  1},
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
            dest.x = j * SQUARE_SIZE + SCREEN_WIDTH/5.7;
            dest.y = i * SQUARE_SIZE + SCREEN_HEIGHT/5.7;
            dest.w = SQUARE_SIZE - SCREEN_WIDTH/81.8;
            dest.h = SQUARE_SIZE - SCREEN_HEIGHT/81.8;
            SDL_RenderCopy(gRenderer, quanco[cs[i][j]->currentTexture], NULL, &dest);
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

bool isInRange(int value, int mn, int mx){
    return mn <= value && value < mx;
}

bool isAPiece(int x, int y){
    return isInRange(x, 0, 7) && isInRange(y, 0, 7) && board[y][x] == 1;
}

bool isEmpty(int x, int y){
    return isInRange(x, 0, 7) && isInRange(y, 0, 7) && board[y][x] == 0;
}

void print(int x, int y){
    cout << "(" << x << "," << y << ") ";
}