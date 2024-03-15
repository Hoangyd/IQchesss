
#include "banco.h"

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;
const int SQUARE_SIZE = 100;
SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;
SDL_Texture* banco = nullptr;
SDL_Texture* quanco = nullptr;

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

void drawTexture(SDL_Texture* texture, int x, int y) {
    int newWidth = SQUARE_SIZE * 4/ 5; // Kích thước mới cho quân cờ (5/6 so với SQUARE_SIZE)
    int newHeight = SQUARE_SIZE * 4/ 5;
    SDL_Rect destRect = { x * SQUARE_SIZE + (SQUARE_SIZE - newWidth) / 2, y * SQUARE_SIZE + (SQUARE_SIZE - newHeight) / 2, newWidth, newHeight };
    SDL_RenderCopy(gRenderer, texture, NULL, &destRect);
}

void drawBoard() {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            bool isInvalidSquare = ((x == 0 && y == 0) || (x == 1 && y == 0) || (x == 0 && y == 1) || (x == 1 && y == 1) ||
                                    (x == 6 && y == 0) || (x == 6 && y == 1) || (x == 5 && y == 1) || (x == 5 && y == 0) ||
                                    (x == 0 && y == 5) || (x == 0 && y == 6) || (x == 1 && y == 5) || (x == 1 && y == 6) ||
                                    (x == 5 && y == 5) || (x == 5 && y == 6) || (x == 6 && y == 5) || (x == 6 && y == 6));
            if (!isInvalidSquare) {
                int centerX = x * SQUARE_SIZE + SQUARE_SIZE / 2;
                int centerY = y * SQUARE_SIZE + SQUARE_SIZE / 2;
                int radius1 = SQUARE_SIZE /4 ; // Bán kính vòng ngoài
                int radius2 = SQUARE_SIZE /12; // Bán kính vòng trong
                if ((x + y) % 2 == 0) {
                    SDL_SetRenderDrawColor(gRenderer, 112, 73, 25, 255); // Màu ô sáng
                } else {
                    SDL_SetRenderDrawColor(gRenderer, 112, 73, 25, 255); // Màu ô tối
                }
                // Vẽ ô cờ nhỏ
                for (int i = 0; i < 360; ++i) {
                    float angle = i * M_PI / 180;
                    for (int j = -2; j <= 2; ++j) {
                        int circleX1 = centerX + (radius1 + j) * cos(angle);
                        int circleY1 = centerY + (radius1 + j) * sin(angle);
                        int circleX2 = centerX + (radius2 + j) * cos(angle);
                        int circleY2 = centerY + (radius2 + j) * sin(angle);
                        SDL_RenderDrawPoint(gRenderer, circleX1, circleY1);
                        SDL_RenderDrawPoint(gRenderer, circleX2, circleY2);
                    }
                }
            }
        }
    }
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


