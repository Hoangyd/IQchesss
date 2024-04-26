
#include "banco.h"

const int SCREEN_WIDTH = 700;
const int SCREEN_HEIGHT = 700;
const int SQUARE_SIZE = SCREEN_WIDTH / 10.588;
SDL_Window *gWindow = nullptr;
SDL_Renderer *gRenderer = nullptr;
SDL_Texture *banco = nullptr;
SDL_Texture *quanco[3] = {nullptr, nullptr, nullptr};
SDL_Texture *playbtn = nullptr;
SDL_Texture *exitbtn = nullptr;
SDL_Texture *againbtn = nullptr;
SDL_Texture *infobtn = nullptr;
Mix_Music *bg_music = nullptr;
Mix_Chunk *camco = nullptr;
Mix_Chunk *datco = nullptr;
Mix_Chunk *win = nullptr;
Mix_Chunk *lose = nullptr;
TTF_Font *font = nullptr;
int soco = 0;

string luatchoi = "Luật chơi của trò IQ Chess thực sự rất đơn giản. Mỗi lần di chuyển, một quân cờ chỉ được coi là di chuyển hợp lệ nếu vị trí mà quân cờ muốn tới không có quân cờ nào, ô muốn tới và ô ban đầu cùng nằm trên một đường thẳng, và chỉ cách nhau đúng một ô. Điều quan trọng là giữa vị trí ban đầu và vị trí mà quân cờ muốn tới phải tồn tại một quân cờ. Bạn sẽ chiến thắng thử thách nếu như chỉ còn lại một quân cờ trên bàn cờ và quân cờ đó nằm chính giữa bàn cờ. Tất cả những trường hợp khác, nếu bạn không còn nước đi hợp lệ nào nữa, bạn sẽ được coi là thua cuộc.";

int board[7][7] = {
    {-1, -1, 1, 1, 1, -1, -1},
    {-1, -1, 1, 1, 1, -1, -1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {-1, -1, 1, 1, 1, -1, -1},
    {-1, -1, 1, 1, 1, -1, -1},
};

int board0[7][7] = {
    {-1, -1, 1, 1, 1, -1, -1},
    {-1, -1, 1, 1, 1, -1, -1},
    {1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1},
    {-1, -1, 1, 1, 1, -1, -1},
    {-1, -1, 1, 1, 1, -1, -1},
};

chess *cs[7][7];

SDL_Texture *loadTexture(const std::string &path)
{
    SDL_Surface *surface = IMG_Load(path.c_str());
    if (!surface)
    {
        std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
        return nullptr;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, surface);
    if (!texture)
    {
        std::cerr << "Failed to create texture from surface: " << SDL_GetError() << std::endl;
    }
    SDL_FreeSurface(surface);
    return texture;
}

void drawChess()
{
    for (int row = 0; row < 7; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            if (board[row][col] != 1)
                continue;
            SDL_Rect dest;
            dest.x = col * (SQUARE_SIZE * 1.005f) + SCREEN_WIDTH / 5.7f;
            dest.y = row * (SQUARE_SIZE * 1.005f) + SCREEN_HEIGHT / 5.7f;
            dest.w = SQUARE_SIZE - SCREEN_WIDTH / 81.8f;
            dest.h = SQUARE_SIZE - SCREEN_HEIGHT / 81.8f;
            SDL_RenderCopy(gRenderer, quanco[cs[row][col]->currentTexture], nullptr, &dest);
        }
    }
}

void drawBoard()
{
    SDL_Rect src;
    src.x = src.y = 0;
    src.w = src.h = 950;
    SDL_Rect dest;
    dest.x = dest.y = 0;
    dest.w = SCREEN_WIDTH;
    dest.h = SCREEN_HEIGHT;
    SDL_RenderCopy(gRenderer, banco, &src, &dest);
}

void resetChess()
{
    soco = 0;
    for (int row = 0; row < 7; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            if (cs[row][col])
            {
                delete cs[row][col];
                cs[row][col] = nullptr;
            }
            board[row][col] = board0[row][col];
            if (board[row][col] == 1)
            {
                cs[row][col] = new chess();
                soco++;
            }
        }
    }
}

bool isInRange(int value, int mn, int mx)
{
    return mn <= value && value < mx;
}

bool isAPiece(int row, int col)
{
    return isInRange(row, 0, 7) && isInRange(col, 0, 7) && board[row][col] == 1 && cs[row][col];
}

bool isEmpty(int row, int col)
{
    return isInRange(row, 0, 7) && isInRange(col, 0, 7) && (board[row][col] == 0 && !cs[row][col]);
}

void print(int row, int col)
{
    cout << "(" << row << "," << col << ") ";
}

int LoseOrWin()
{
    if (soco == 1)
    {
        if (board[3][3] == 1 || cs[3][3])
        {
            return 1;
        }
        else
        {
            return -1;
        }
    }

    for (int row = 0; row < 7; row++)
    {
        for (int col = 0; col < 7; col++)
        {
            if (board[row][col] != 1)
            {
                continue;
            }

            bool u = isAPiece(row - 1, col) && isEmpty(row - 2, col);
            bool d = isAPiece(row + 1, col) && isEmpty(row + 2, col);
            bool r = isAPiece(row, col + 1) && isEmpty(row, col + 2);
            bool l = isAPiece(row, col - 1) && isEmpty(row, col - 2);
            if (u || d || r || l)
            {
                return 0;
            }
        }
    }

    return -1;
}

void DisplayText(std::string text, int x, int y, int fs, int wrap)
{
    TTF_SetFontSize(font, fs);
    SDL_Surface *sf = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), {255, 255, 255, 255}, wrap);
    SDL_Rect rect;

    SDL_Texture *texture = SDL_CreateTextureFromSurface(gRenderer, sf);

    rect.x = x - sf->w / 2.0f;
    rect.y = y - sf->h / 2.0f;
    rect.w = sf->w;
    rect.h = sf->h;

    SDL_SetRenderDrawColor(gRenderer, 25, 25, 25, 128);
    SDL_RenderFillRect(gRenderer, &rect);
    SDL_RenderCopy(gRenderer, texture, NULL, &rect);

    SDL_FreeSurface(sf);
    SDL_DestroyTexture(texture);
}

std::string addzero(int n, int len)
{
    std::string strn = std::to_string(n);
    return std::string(len - strn.size(), '0') + strn;
}

std::string timeformat(int ms)
{
    float fsecond = (float)ms / 1000.0f;
    int second = fsecond;
    fsecond -= (float)second;
    fsecond *= 1000.0f;
    int hour = second / 3600.0f;
    second -= hour * 3600.0f;
    int minute = second / 60.0f;
    second -= minute * 60.0f;
    return (hour ? std::to_string(hour) : "00") + ":" + addzero(minute, 2) + ":" + addzero(second, 2) + "." +
           addzero((int)fsecond, 3) + "s";
}