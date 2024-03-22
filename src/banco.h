#ifndef BANCO_H
#define BANCO_H

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_mixer.h"
#include <iostream>
#include <cmath>

using namespace std;

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SQUARE_SIZE;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* banco;
extern SDL_Texture* quanco[3];
extern int soco;

int LoseOrWin();
bool isInRange(int value, int mn, int mx);
bool isAPiece(int row, int col);
bool isEmpty(int row, int col);
void print(int row, int col);

SDL_Texture* loadTexture(const std::string& path);
void drawChess();
void drawBoard();

extern Mix_Music* bg_music;
extern Mix_Chunk* camco;
extern Mix_Chunk* datco;

class chess{
public:
    int currentTexture = 0;
};

extern int board[7][7];
extern chess * cs[7][7];

#endif
