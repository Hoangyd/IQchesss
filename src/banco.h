#ifndef BANCO_H
#define BANCO_H

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include <iostream>
#include <cmath>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SQUARE_SIZE;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern SDL_Texture* banco;
extern SDL_Texture* quanco[3];

bool isValidMove(int x1, int y1, int x2, int y2);
int LoseOrWin();

SDL_Texture* loadTexture(const std::string& path);
void drawChess();
void drawBoard();

class chess{
public:
    int currentTexture = 0;
};

extern int board[7][7];
extern chess * cs[7][7];

#endif
