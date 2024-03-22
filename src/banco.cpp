
#include "banco.h"

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;
const int SQUARE_SIZE = SCREEN_WIDTH/10.588;
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* banco = nullptr;
SDL_Texture* quanco[3] = {nullptr, nullptr, nullptr};
SDL_Texture* playbtn = nullptr;
SDL_Texture* exitbtn = nullptr;
Mix_Music* bg_music = nullptr;
Mix_Chunk* camco = nullptr;
Mix_Chunk* datco = nullptr;
int soco = 0;

int board[7][7] = {
    {-1, -1, 1, 1, 1, -1, -1},
    {-1, -1, 1, 1, 1, -1, -1},
    { 1,  1, 1, 1, 1,  1,  1},
    { 1,  1, 1, 0, 1,  1,  1},
    { 1,  1, 1, 1, 1,  1,  1},
    {-1, -1, 1, 1, 1, -1, -1},
    {-1, -1, 1, 1, 1, -1, -1},
};
//     {-1, -1, 0, 0, 0, -1, -1},
//     {-1, -1, 0, 0, 1, -1, -1},
//     { 0,  0, 0, 0, 0,  0,  0},
//     { 0,  0, 0, 0, 1,  1,  0},
//     { 0,  0, 0, 0, 0,  0,  0},
//     {-1, -1, 0, 0, 1, -1, -1},
//     {-1, -1, 0, 0, 1, -1, -1},
// };

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
    for (int row=0;row<7;row++){
        for (int col=0;col<7;col++){
            if (board[row][col]!=1){
                continue;
            }
            SDL_Rect dest;
            dest.x = col * SQUARE_SIZE + SCREEN_WIDTH/5.7;
            dest.y = row * SQUARE_SIZE + SCREEN_HEIGHT/5.7;
            dest.w = SQUARE_SIZE - SCREEN_WIDTH/81.8;
            dest.h = SQUARE_SIZE - SCREEN_HEIGHT/81.8;
            SDL_RenderCopy(gRenderer, quanco[cs[row][col]->currentTexture], nullptr, &dest);
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

bool isAPiece(int row, int col){
    return isInRange(row, 0, 7) && isInRange(col, 0, 7) && board[row][col] == 1 && cs[row][col];
}

bool isEmpty(int row, int col){
    return isInRange(row, 0, 7) && isInRange(col, 0, 7) && board[row][col] == 0 && !cs[row][col];
}

void print(int row, int col){
    cout << "(" << row << "," << col << ") ";
}

int LoseOrWin(){
    if (soco==1){
        if (board[3][3]==1 || cs[3][3]){
            return 1;
        }
        else{
            return -1;
        }
    }

    for (int row=0;row<7;row++){
        for (int col=0;col<7;col++){
            if (board[row][col] != 1){
                continue;
            }
            bool u = isAPiece(row-1, col) && isEmpty(row-2, col);
            bool d = isAPiece(row+1, col) && isEmpty(row+2, col);
            bool r = isAPiece(row, col+1) && isEmpty(row, col+2);
            bool l = isAPiece(row, col-1) && isEmpty(row, col-2);
            if (u || d || r || l){
                return 0;
            }
        }
    }

    return -1;
}