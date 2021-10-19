//------------------- Bezier Curve implementation --------------------------//
//------------------- This App Needs SDL and SDL_Image library to run -----//
//------------------- The Algorithm itself is inside drawCurve function --//
//------------------- A demo of the app is at:
//------------------- https://streamable.com/687dmw --------------------//

#include "src/core.h"
#include <SDL.h>
#include <SDL_image.h>

#include <cmath>

//Screen dimension constants
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

//dot texture width and height
#define DOT_WIDTH 20
#define DOT_HEIGHT 20

//a simple wrapper for the textures to include width and height
typedef struct
{
    SDL_Texture* texture;
    int width;
    int height;

} texture_wrapper_t;

//vector 2D class/struct
typedef struct vec2
{
    float x;
    float y;

} vec2;

typedef vec2 Point;

//-------------- Govern points ----------------//

Point P1 = { 0, 0 };
Point P2 = { SCREEN_WIDTH, 0 };
Point P3 = { SCREEN_WIDTH, SCREEN_HEIGHT };

static SDL_Window* gWindow     = NULL;
static SDL_Renderer* gRenderer = NULL;

static texture_wrapper_t gDotTexture;
static bool gIsRunning;

static bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        fprintf(stderr, "couldn't initialise SDL, error %s\n", SDL_GetError());
        return false;
    }
    else
    {
        gWindow = SDL_CreateWindow("De Casteljau Bezier Curves", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            fprintf(stderr, "couldn't create window, error %s", SDL_GetError());
            return false;
        }

        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                fprintf(stderr, "couldn't create renderer error%s\n", SDL_GetError());
                return false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    fprintf(stderr, "SDL_Image couldn't be initalised, error: %s\n", IMG_GetError());
                    return false;
                }
            }
        }
    }
    return true;
}

static SDL_Surface* loadSurface(char const* path)
{
    SDL_Surface* loadedSurface = IMG_Load(path);
    if (loadedSurface == NULL)
    {
        fprintf(stderr, "couldn't load surface, error: %s\n", SDL_GetError());
    }

    return loadedSurface;
}

static SDL_Texture* loadTexture(char const* path)
{
    SDL_Surface* tempSurface = loadSurface(path);
    SDL_Texture* texture     = NULL;
    if (tempSurface == NULL)
    {
        fprintf(stderr, "passed a null surface, can't create a texture\n");
    }
    else
    {
        texture = SDL_CreateTextureFromSurface(gRenderer, tempSurface);
        SDL_FreeSurface(tempSurface);
    }

    if (texture == NULL)
    {
        fprintf(stderr, "couldn't create exture from surface, %s\n", SDL_GetError());
    }
    return texture;
}

static bool loadMedia()
{

    //getting the texture information
    gDotTexture.texture = loadTexture("assets/dot.bmp");
    SDL_QueryTexture(gDotTexture.texture, NULL, NULL, &gDotTexture.width, &gDotTexture.height);

    if (gDotTexture.texture == NULL)
    {
        fprintf(stderr, "could load the Dot texture, error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

bool setup()
{

    if (init() && loadMedia())
    {
        gIsRunning = true;

        return true;
    }
    else
    {
        fprintf(stderr, "couldn't setup\n");
        return false;
    }
}

static void close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_DestroyTexture(gDotTexture.texture);

    gRenderer           = NULL;
    gWindow             = NULL;
    gDotTexture.texture = NULL;

    IMG_Quit();
    SDL_Quit();
}
static void renderTexture(texture_wrapper_t* texture, int x, int y, SDL_Rect* clip)
{
    SDL_Rect destRect = { x, y, texture->width, texture->height };

    if (clip != NULL)
    {
        destRect.w = clip->w;
        destRect.h = clip->h;
    }

    SDL_RenderCopy(gRenderer, texture->texture, clip, &destRect);
}

static void drawCurve(Point p1, Point p2, Point p3)
{

    vec2 P12 = { p2.x - p1.x, p2.y - p1.y };
    vec2 P23 = { p3.x - p2.x, p3.y - p2.y };

    float d1 = std::ceil(std::sqrt(P12.x * P12.x + P12.y * P12.y)); // Thanks to Pythagorean therom, we can find the distance
    float d2 = std::ceil(std::sqrt(P23.x * P23.x + P23.y * P23.y)); // or the number of pixesl between two points so we can interpolate them

    float no_of_pixels = d2 > d1 ? d2 : d1; //basically selecting the largest distance ()

    for (float t = 1.0f / no_of_pixels, lymda = t; lymda <= 1; lymda += t)
    {
        float one_minus_lymda = 1 - lymda;

        Point V1 = { one_minus_lymda * p1.x, one_minus_lymda * p1.y };
        Point V2 = { lymda * p2.x, lymda * p2.y };

        Point Q0 = { V1.x + V2.x, V1.y + V2.y };

        V1 = { one_minus_lymda * p2.x, one_minus_lymda * p2.y };
        V2 = { lymda * p3.x, lymda * p3.y };

        Point Q1 = { V1.x + V2.x, V1.y + V2.y };

        V1 = { one_minus_lymda * Q0.x, one_minus_lymda * Q0.y };
        V2 = { lymda * Q1.x, lymda * Q1.y };

        Point R0 = { V1.x + V2.x, V1.y + V2.y };

        SDL_RenderDrawPoint(gRenderer, static_cast<int>(R0.x), static_cast<int>(R0.y));
    }
}

static void render()
{
    //clearing the screen to white
    SDL_SetRenderDrawColor(gRenderer, 0XFF, 0xFF, 0XFF, 0XFF);
    SDL_RenderClear(gRenderer);

    // NULL is passed to render the whole Dot texture and not part of it
    renderTexture(&gDotTexture, (int)P1.x, (int)P1.y, NULL);
    renderTexture(&gDotTexture, (int)P2.x, (int)P2.y, NULL);
    renderTexture(&gDotTexture, (int)P3.x, (int)P3.y, NULL);

    SDL_SetRenderDrawColor(gRenderer, 0XFF, 0x0F, 0XF0, 0XFF); //curve color

    drawCurve(P1, P2, P3);
}

static void update()
{
    //flip the frame buffer
    SDL_RenderPresent(gRenderer);
}

static void event()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            gIsRunning = false;
        }

        //---- getting mouse position ----//
        int mouse_x, mouse_y;
        SDL_GetMouseState(&mouse_x, &mouse_y);

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_a:
                {
                    P1 = Point { static_cast<float>(mouse_x), static_cast<float>(mouse_y) };
                    break;
                }

                case SDLK_s:
                {
                    P2 = vec2 { static_cast<float>(mouse_x), static_cast<float>(mouse_y) };
                    break;
                }
                case SDLK_d:
                {
                    P3 = vec2 { static_cast<float>(mouse_x), static_cast<float>(mouse_y) };
                    break;
                }
            }
        }
    }
}

void run()
{

    while (gIsRunning)
    {
        event();
        update();
        render();
    }

    close();
}

int main()
{

    if (!setup())
    {
        fprintf(stderr, "failed to initialise the program\n");
        return -1;
    }
    run();
}
