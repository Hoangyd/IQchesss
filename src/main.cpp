#include "banco.h"
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_mixer.h"
#include "../include/SDL2/SDL_ttf.h"
#include <iostream>

using namespace std;

int main(int argc, char *args[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "SDL không thể khởi tạo! Lỗi SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    gWindow = SDL_CreateWindow("IQCHESS", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr)
    {
        std::cerr << "Không thể tạo cửa sổ! Lỗi SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == nullptr)
    {
        std::cerr << "Không thể tạo renderer! Lỗi SDL: " << SDL_GetError() << std::endl;
        return 1;
    }
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);
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
    for (int i = 0; i < 3; i++)
    {
        quanco[i] = loadTexture("image/quanco" + std::to_string(i) + ".png");
    }
    playbtn = loadTexture("image/playbutton.png");
    exitbtn = loadTexture("image/exitbutton.png");
    againbtn = loadTexture("image/againbutton.png");
    infobtn = loadTexture("image/infobtn.png");
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

    TTF_Init();
    font = TTF_OpenFont("Roboto-Bold.ttf", 24);

    bg_music = Mix_LoadMUS("sound/music.ogg");
    Mix_VolumeMusic(32);
    camco = Mix_LoadWAV("sound/cam.ogg");
    datco = Mix_LoadWAV("sound/dat.ogg");
    win = Mix_LoadWAV("sound/win.ogg");
    lose = Mix_LoadWAV("sound/lose.ogg");

    resetChess();

    bool quit = false;
    bool play = false;
    SDL_Event e;

    int mouse_x = 0, mouse_y = 0;

    int prev_row = -1, prev_col = -1;
    int cur_row = -1, cur_col = -1;

    int selected_row = -1, selected_col = -1;
    chess *selected = nullptr;

    SDL_Rect infodst;
    infodst.w = infodst.h = SCREEN_HEIGHT / 9.0f;
    infodst.x = SCREEN_WIDTH / 2.0f - infodst.w * 0.5f;
    infodst.y = SCREEN_HEIGHT / 2.0f - infodst.h * 0.5f;
    bool showinfo = false;

    SDL_Rect playdst;
    playdst.w = playdst.h = SCREEN_HEIGHT / 9.0f;
    playdst.x = SCREEN_WIDTH / 2.0f - playdst.w * 1.75f;
    playdst.y = SCREEN_HEIGHT / 2.0f - playdst.h * 0.5f;

    SDL_Rect exitdst;
    exitdst.w = exitdst.h = SCREEN_HEIGHT / 9.0f;
    exitdst.x = SCREEN_WIDTH / 2.0f + exitdst.w * 0.75f;
    exitdst.y = SCREEN_HEIGHT / 2.0f - exitdst.h * 0.5f;

    SDL_Rect replaydist;
    replaydist.w = replaydist.h = SCREEN_HEIGHT / 10.0f;
    replaydist.x = SCREEN_WIDTH * 0.98f - replaydist.w;
    replaydist.y = SCREEN_WIDTH * 0.98f - replaydist.h;

    int state = 0;
    int delay_win = -2000;
    int time = 0;
    int win_time = 0;
    while (!quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            SDL_GetMouseState(&mouse_x, &mouse_y);
            cur_row = (mouse_y - SCREEN_WIDTH / 5.7f) / SQUARE_SIZE;
            cur_col = (mouse_x - SCREEN_HEIGHT / 5.7f) / SQUARE_SIZE;
            if (e.type == SDL_MOUSEBUTTONDOWN)
            {
                if (e.button.button == SDL_BUTTON_LEFT)
                {
                    if (state == 0 && play)
                    {
                        if (selected == nullptr && isAPiece(cur_row, cur_col))
                        {

                            selected_row = cur_row;
                            selected_col = cur_col;
                            selected = cs[cur_row][cur_col];
                            board[cur_row][cur_col] = 0;
                            cs[cur_row][cur_col] = nullptr;
                            Mix_PlayChannel(-1, camco, 0);
                        }
                        else if (selected != nullptr)
                        {
                            if (!isEmpty(cur_row, cur_col))
                                continue;
                            bool k_di_chuyen = (cur_row == selected_row && cur_col == selected_col);
                            bool an_co = false;
                            if (!k_di_chuyen)
                            {
                                int dr = abs(cur_row - selected_row);
                                int dc = abs(cur_col - selected_col);
                                int mid_row = (cur_row + selected_row) / 2;
                                int mid_col = (cur_col + selected_col) / 2;
                                bool ok = board[mid_row][mid_col] == 1 && cs[mid_row][mid_col];
                                if (((dr == 2 && dc == 0) || (dr == 0 && dc == 2)) && ok)
                                {
                                    board[mid_row][mid_col] = 0;
                                    delete cs[mid_row][mid_col];
                                    cs[mid_row][mid_col] = nullptr;
                                    an_co = true;
                                    soco--;
                                }
                            }
                            if (k_di_chuyen || an_co)
                            {
                                cs[cur_row][cur_col] = selected;
                                cs[cur_row][cur_col]->currentTexture = 1;
                                board[cur_row][cur_col] = 1;
                                selected = nullptr;
                                selected_row = selected_col = -1;
                                Mix_PlayChannel(-1, datco, 0);
                                for (int i = 0; i < 3; i++)
                                    state = LoseOrWin();
                                if (state != 0)
                                {
                                    play = false;
                                    if (state == 1)
                                    {
                                        delay_win = SDL_GetTicks();
                                        Mix_PlayChannel(-1, win, 0);
                                        win_time = SDL_GetTicks() - time;
                                    }
                                    else
                                    {
                                        Mix_PlayChannel(-1, lose, 0);
                                    }
                                }
                            }
                        }
                    }
                    if (!play && SDL_GetTicks() - delay_win >= 500)
                    {
                        if (!showinfo)
                        {
                            if (isInRange(mouse_x, playdst.x, playdst.x + playdst.h) && isInRange(mouse_y, playdst.y, playdst.y + playdst.h))
                            {
                                resetChess();
                                state = 0;
                                play = true;
                                if (!Mix_PlayingMusic())
                                {
                                    Mix_PlayMusic(bg_music, -1);
                                }
                                time = SDL_GetTicks();
                            }
                            else if (isInRange(mouse_x, exitdst.x, exitdst.x + exitdst.h) && isInRange(mouse_y, exitdst.y, exitdst.y + exitdst.h))
                            {
                                quit = true;
                            }
                            else if (isInRange(mouse_x, infodst.x, infodst.x + infodst.h) && isInRange(mouse_y, infodst.y, infodst.y + infodst.h))
                            {
                                showinfo = true;
                            }
                        }
                        else
                        {
                            showinfo = false;
                        }
                    }
                    else if (play)
                    {
                        if (isInRange(mouse_x, replaydist.x, replaydist.x + replaydist.h) && isInRange(mouse_y, replaydist.y, replaydist.y + replaydist.h))
                        {
                            time = SDL_GetTicks();
                            resetChess();
                        }
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
        drawBoard();

        if (!play && SDL_GetTicks() - delay_win >= 500)
        {
            SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 127);
            SDL_RenderFillRect(gRenderer, nullptr);
            if (showinfo)
            {
                DisplayText(luatchoi, SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f, SCREEN_HEIGHT / 25.0f, SCREEN_WIDTH / 1.25);
            }
            else
            {
                if (state != 0)
                {
                    DisplayText((state == 1 ? "HẢO HÁN!" : "Ối dồi ôi!"), SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 3.5f, SCREEN_HEIGHT / 45.0f * 4.0f, SCREEN_WIDTH);
                    DisplayText((state == 1 ? "Trong: " + timeformat(win_time) : "Số cờ còn lại: " + to_string(soco)), SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.5f, SCREEN_WIDTH / 18.0f, SCREEN_WIDTH);
                    SDL_RenderCopy(gRenderer, againbtn, nullptr, &playdst);
                }
                else
                {
                    DisplayText("IQCHESS", SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 3.0f, SCREEN_HEIGHT / 45.0f * 5.0f, SCREEN_WIDTH);
                    SDL_RenderCopy(gRenderer, playbtn, nullptr, &playdst);
                }
                SDL_RenderCopy(gRenderer, infobtn, nullptr, &infodst);
                SDL_RenderCopy(gRenderer, exitbtn, nullptr, &exitdst);
            }
        }
        else
        {
            DisplayText("Thời gian: " + timeformat(SDL_GetTicks() - time), SCREEN_WIDTH / 5.0f, SCREEN_HEIGHT / 20.0f, SCREEN_WIDTH / 30.0f, SCREEN_WIDTH);
            DisplayText("Số cờ: " + to_string(soco), SCREEN_WIDTH / 5.0f * 4.5f, SCREEN_HEIGHT / 20.0f, SCREEN_WIDTH / 30.0f, SCREEN_WIDTH);
            if (cur_row != prev_row || cur_col != prev_col)
            {
                if (isAPiece(prev_row, prev_col) && (prev_row != selected_row || prev_col != selected_col))
                {
                    cs[prev_row][prev_col]->currentTexture = 0;
                }
                prev_row = cur_row;
                prev_col = cur_col;
            }
            if (isAPiece(cur_row, cur_col) && (cur_row != selected_row || cur_col != selected_col))
            {
                cs[cur_row][cur_col]->currentTexture = 1;
            }

            drawChess();
            if (selected != nullptr)
            {
                SDL_Rect dest;
                dest.w = SQUARE_SIZE - SCREEN_WIDTH / 81.8f;
                dest.h = SQUARE_SIZE - SCREEN_HEIGHT / 81.8f;
                dest.x = mouse_x - dest.w / 2.0f;
                dest.y = mouse_y - dest.h / 2.0f;
                SDL_RenderCopy(gRenderer, quanco[0], nullptr, &dest);
            }

            SDL_RenderCopy(gRenderer, againbtn, NULL, &replaydist);
        }

        SDL_RenderPresent(gRenderer);
    }

    for (int row = 0; row < 7; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            if (board[row][col] == 1 || cs[row][col])
            {
                board[row][col] = 0;
                delete cs[row][col];
                cs[row][col] = nullptr;
            }
        }
    }

    Mix_FreeMusic(bg_music);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_CloseFont(font);
    gWindow = nullptr;
    gRenderer = nullptr;
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
    return 0;
}
