#include <iostream>
#include <SDL.h>
using namespace std;

//cac hang khoi tao SDL
const int SCREEN_WIDTH = 800; // chieu rong man hinh
const int SCREEN_HEIGHT = 600; // chieu cao man hinh
const string WINDOW_TITLE = "An Implementation of Code.org Painter"; //tieu de cua cua so chuong trinh

//khoi tao SDL
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
            //dai dien cho cua so ve - dai dien cho but ve
            //tham chieu toi con tro kieu SDL_Window - SDL_Renderer

//chu ki ham bao loi
void logSDLError(std::ostream& os, const std::string &msg, bool fatal = false);

//chu ki ham giai phong SDL
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

//chu ki ham doi mot phim de thoat
void waitUntilKeyPressed();

int main(int argc, char* argv[])
{
    SDL_Window* window; //khai bao con tro window - cua so
    SDL_Renderer* renderer; //khai bao con tro renderer - but ve
    initSDL(window, renderer); // goi ham khoi tao SDL de khoi tao gia tri cho window va renderer

    SDL_RenderClear(renderer);//xoa man hinh
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // set mau
    SDL_RenderDrawLine(renderer, 100, 100, 200, 200); // ve duong thang

    SDL_Rect filledRect;
    filledRect.x = 150;
    filledRect.y = 150;
    filledRect.h = 100;
    filledRect.w = 150;
    SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255); //mau tim la tron giua mau do va mau xanh da troi
    SDL_RenderFillRect(renderer, &filledRect); //ve hinh chu nhat
    //day moi chi la ve trong buffer

    //hien thi ra man hinh
    SDL_RenderPresent(renderer);

    waitUntilKeyPressed();
    quitSDL(window, renderer);
    return 0;
}

void logSDLError(std::ostream& os,
                 const std::string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << std::endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)  //bao loi ham khoi tao SDL
        logSDLError(std::cout, "SDL_Init", true);

    //TAO CUA SO VE
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); //danh cho chuong trinh chay tren may tinh thong thuong
    /*window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP); chi danh cho chuong trinh chay tren may ao vd den phong thuc hanh*/

    if (window == nullptr) logSDLError(std::cout, "CreateWindow", true); // bao loi ham create window

    //TAO BUT VE
    //Khi thông thường chạy với môi trường bình thường ở nhà
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    //Khi chạy ở máy thực hành WinXP ở trường (máy ảo)
    //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    //bao loi ham create renderer
    if (renderer == nullptr) logSDLError(std::cout, "CreateRenderer", true);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}

void quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
	SDL_DestroyRenderer(renderer); //thu hoi but ve
	SDL_DestroyWindow(window); // thu hoi cua so
	SDL_Quit(); // goi ham quit
}

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_WaitEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) ) //xac dinh su kien ban phim
            return;
        SDL_Delay(100);  //deday 100ms
    }
}
