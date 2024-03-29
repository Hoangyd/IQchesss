#include "banco.h"
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_mixer.h"
#include <iostream>

using namespace std;

int main(int argc, char* args[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL không thể khởi tạo! Lỗi SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    gWindow = SDL_CreateWindow("IQCHESS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        std::cerr << "Không thể tạo cửa sổ! Lỗi SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr) {
        std::cerr << "Không thể tạo renderer! Lỗi SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    int format = MIX_INIT_OGG;
    if (Mix_Init(format) & format != format)
    {
        std::cerr << "Không thể tạo format! Lỗi SDL_Mixer: " << Mix_GetError() << std::endl;
    }
    if (Mix_OpenAudio(44100, AUDIO_S32SYS, 2, 4096) < 0)
    {
        std::cerr << "Không thể mở thiết bị âm thanh! Lỗi SDL_Mixer: " << Mix_GetError() << std::endl;
        return 1;
    }

    banco = loadTexture("image/banco.png");
    for (int i=0;i<3;i++){
        quanco[i] = loadTexture("image/quanco" + std::to_string(i) + ".png");
    }
    playbtn = loadTexture("image/playbutton.png");
    cout << playbtn;
    exitbtn = loadTexture("image/exitbutton.png");
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

    bg_music = Mix_LoadMUS("sound/music.ogg");
    Mix_VolumeMusic(32);
    // Mix_PlayMusic(bg_music, -1);

    camco = Mix_LoadWAV("sound/cam.ogg");
    datco = Mix_LoadWAV("sound/dat.ogg");

    for (int row=0;row<7;row++){
        for (int col=0;col<7;col++){
            if (board[row][col]!=1){
                cs[row][col] = nullptr;
            }
            else{
                cs[row][col] = new chess();
                soco++;
            }
        }
    }

    bool quit = false;
    bool play = false;
    SDL_Event e;
    
    int mouse_x=0, mouse_y=0;

    int prev_row=-1, prev_col=-1;
    int cur_row=-1, cur_col=-1;

    int selected_row=-1, selected_col=-1;
    chess * selected = nullptr;

    SDL_Rect playdst;
    playdst.x = SCREEN_WIDTH/2 - 105;
    playdst.y = SCREEN_HEIGHT/2 - 50;
    playdst.w = playdst.h = 100;
    
    SDL_Rect exitdst;
    exitdst.x = SCREEN_WIDTH/2 + 5;
    exitdst.y = SCREEN_HEIGHT/2 - 50;
    exitdst.w = exitdst.h = 100;

    int state = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            SDL_GetMouseState(&mouse_x, &mouse_y);
            cur_row = (mouse_y - SCREEN_WIDTH/5.7) / SQUARE_SIZE;
            cur_col = (mouse_x - SCREEN_HEIGHT/5.7) / SQUARE_SIZE;
            if (e.type == SDL_MOUSEBUTTONDOWN){
                if (e.button.button == SDL_BUTTON_LEFT){
                    if (state == 0 && play){
                        if (selected == nullptr && isAPiece(cur_row, cur_col)){
                            cs[cur_row][cur_col]->currentTexture = 2;
                            selected_row = cur_row;
                            selected_col = cur_col;
                            selected = cs[cur_row][cur_col];
                            board[cur_row][cur_col] = 0;
                            cs[cur_row][cur_col] = nullptr;
                            Mix_PlayChannel(-1, camco, 0);
                        }
                        else if (selected != nullptr){
                            if (!isEmpty(cur_row, cur_col)) continue;
                            bool a = (cur_row == selected_row && cur_col == selected_col);
                            bool b = false;
                            if (!a){
                                bool r = abs(cur_row - selected_row) == 2;
                                bool c = abs(cur_col - selected_col) == 2;
                                int mid_row = (cur_row + selected_row) / 2;
                                int mid_col = (cur_col + selected_col) / 2;
                                bool ok = board[mid_row][mid_col] == 1 && cs[mid_row][mid_col];
                                if ((r || c) && ok){
                                    board[mid_row][mid_col] = 0;
                                    delete cs[mid_row][mid_col];
                                    cs[mid_row][mid_col] = nullptr;
                                    b = true;
                                    soco--;
                                }
                            }
                            if (a || b){
                                cs[cur_row][cur_col] = selected;
                                cs[cur_row][cur_col]->currentTexture = 1;
                                board[cur_row][cur_col] = 1;
                                selected = nullptr;
                                selected_row = selected_col = -1;
                                Mix_PlayChannel(-1, datco, 0);
                                state = LoseOrWin();
                            }
                        }
                    }
                    if (!play){
                        if (isInRange(mouse_x, playdst.x, playdst.x + playdst.h) && isInRange(mouse_y, playdst.y, playdst.y + playdst.h)){
                            play = true;
                        }
                        else if (isInRange(mouse_x, exitdst.x, exitdst.x + exitdst.h) && isInRange(mouse_y, exitdst.y, exitdst.y + exitdst.h)){
                            quit = true;
                        }
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0,0,0,255);
        SDL_RenderClear(gRenderer);
        drawBoard();

        if (!play){
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 127);
            SDL_RenderFillRect(gRenderer, nullptr);
            SDL_RenderCopy(gRenderer, playbtn, nullptr, &playdst);
            SDL_RenderCopy(gRenderer, exitbtn, nullptr, &exitdst);

        }
        else{
            if (cur_row != prev_row || cur_col != prev_col){
                if (isAPiece(prev_row, prev_col) && (prev_row != selected_row || prev_col != selected_col)){
                    cs[prev_row][prev_col]->currentTexture = 0;
                }
                prev_row = cur_row;
                prev_col = cur_col;
            }
            if (isAPiece(cur_row, cur_col) && (cur_row != selected_row || cur_col != selected_col)){
                cs[cur_row][cur_col]->currentTexture = 1;
            }

            drawChess();
            if (selected != nullptr){
                SDL_Rect dest;
                dest.w = SQUARE_SIZE - SCREEN_WIDTH/81.8;
                dest.h = SQUARE_SIZE - SCREEN_HEIGHT/81.8;
                dest.x = mouse_x - dest.w/2;
                dest.y = mouse_y - dest.h/2;
                SDL_RenderCopy(gRenderer, quanco[0], nullptr, &dest);
            }
        }

        SDL_RenderPresent(gRenderer);
    }
   
    for (int row=0;row<7;row++){
        for (int col=0;col<7;col++){
            if (board[row][col]==1 || cs[row][col]){
                board[row][col] = 0;
                delete cs[row][col];
                cs[row][col] = nullptr;
            }
        }
    }

    Mix_FreeMusic(bg_music);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gWindow = nullptr;
    gRenderer = nullptr;
    Mix_CloseAudio();
    Mix_Quit();
    SDL_Quit();
    return 0;
}
