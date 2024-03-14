#ifndef MAPCO_H
#define MAPCO_H
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include <iostream>
#include <cmath>
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SQUARE_SIZE;
extern SDL_Window* gWindow;
extern SDL_Renderer* gRenderer;
extern int rook1X;
extern int rook1Y;
extern int rook2X;
extern int rook2Y;
extern int selectedRook;
extern SDL_Texture* rook1Texture;
extern SDL_Texture* rook2Texture;
extern SDL_Texture* backgroundTexture;
bool isValidMove(int x, int y);
SDL_Texture* loadTexture(const std::string& path);
void drawTexture(SDL_Texture* texture, int x, int y);
void drawBoard();
void render();
#endif
