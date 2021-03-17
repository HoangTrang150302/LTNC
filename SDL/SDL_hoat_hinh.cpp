#include <iostream>
#include <SDL.h>
using namespace std;

//cac hang khoi tao SDL
const int SCREEN_WIDTH = 800; // chieu rong man hinh
const int SCREEN_HEIGHT = 600; // chieu cao man hinh
const string WINDOW_TITLE = "Tiny Game"; //tieu de cua cua so chuong trinh
int STEP_DELAY = 10;

struct Box
{
    int x;// x, y la toa do cua hinh chu nhat
    int y;
    int size = 20;
    int stepX = 0;
    int stepY = 0;

    Box(int _x, int _y) :x(_x), y(_y) {}

    void render(SDL_Renderer* renderer)
    {
        SDL_Rect filledRect;
        filledRect.x = x;
        filledRect.y = y;
        filledRect.h = size;
        filledRect.w = size;
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);
        SDL_RenderFillRect(renderer, &filledRect); //ve hinh chu nhat
        //day moi chi la ve trong buffer
    }

    void move()
    {
        x += stepX;
        y += stepY;
    }

    void turnLeft()
    {
        stepX = -5;
        stepY = 0;
    }
    void turnRight()
    {
        stepX = 5;
        stepY = 0;
    }
    void turnDown()
    {
        stepY = 5;
        stepX = 0;
    }
    void turnUp()
    {
        stepY = -5;
        stepX = 0;
    }
    bool inside(int minX, int minY, int maxX, int maxY)
    {
        return(minX <= x && minY <= y && x+size <= maxX && y+size <= maxY);
    }
};

//khoi tao SDL
void initSDL(SDL_Window* &window, SDL_Renderer* &renderer);
            //dai dien cho cua so ve - dai dien cho but ve
            //tham chieu toi con tro kieu SDL_Window - SDL_Renderer

//chu ki ham bao loi
void logSDLError(ostream& os, const string &msg, bool fatal = false);

//chu ki ham giai phong SDL
void quitSDL(SDL_Window* window, SDL_Renderer* renderer);

//chu ki ham doi mot phim de thoat
void waitUntilKeyPressed();

int main(int argc, char* argv[])
{
    SDL_Window* window; //khai bao con tro window - cua so
    SDL_Renderer* renderer; //khai bao con tro renderer - but ve
    initSDL(window, renderer); // goi ham khoi tao SDL de khoi tao gia tri cho window va renderer

    Box box(10, 10);

    SDL_Event e;

    while(box.inside(0,0, SCREEN_WIDTH, SCREEN_HEIGHT))
    {
        box.move();
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //set lai mau trang cho man hinh
        SDL_RenderClear(renderer);//xoa man hinh
        box.render(renderer);// ve hcn
        //hien thi ra man hinh
        SDL_RenderPresent(renderer);
        SDL_Delay(STEP_DELAY);

        // Nếu không có sự kiện gì thì tiếp tục trở về đầu vòng lặp
        if (SDL_PollEvent(&e) == 0) continue;

        // Nếu sự kiện là kết thúc (như đóng cửa sổ) thì thoát khỏi vòng lặp
        if (e.type == SDL_QUIT) break;

        // Nếu có một phím được nhấn, thì xét phím đó là gì để xử lý tiếp
        if (e.type == SDL_KEYDOWN) {
        	switch (e.key.keysym.sym) {
        		case SDLK_ESCAPE: break; // Nếu nhấn phìm ESC thì thoát khỏi vòng lặp
        		// Nếu phím mũi tên trái, dịch sang trái
    	        // (cộng chiều rộng, trừ bước, rồi lấy phần dư để giá trị luôn dương, và hiệu ứng quay vòng)
        		case SDLK_LEFT: box.turnLeft();
        			break;
        		// Tương tự với dịch phải, xuống và lên
            	case SDLK_RIGHT: box.turnRight();
            		break;
            	case SDLK_DOWN: box.turnDown();
					break;
            	case SDLK_UP: box.turnUp();
            		break;
        		default: break;
			}
		}
    }

    quitSDL(window, renderer);
    return 0;
}

void logSDLError(ostream& os, const string &msg, bool fatal)
{
    os << msg << " Error: " << SDL_GetError() << endl;
    if (fatal) {
        SDL_Quit();
        exit(1);
    }
}

void initSDL(SDL_Window* &window, SDL_Renderer* &renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)  //bao loi ham khoi tao SDL
        logSDLError(cout, "SDL_Init", true);

    //TAO CUA SO VE
    window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN); //danh cho chuong trinh chay tren may tinh thong thuong
    /*window = SDL_CreateWindow(WINDOW_TITLE.c_str(), SDL_WINDOWPOS_CENTERED,
       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP); chi danh cho chuong trinh chay tren may ao vd den phong thuc hanh*/

    if (window == nullptr) logSDLError(cout, "CreateWindow", true); // bao loi ham create window

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
