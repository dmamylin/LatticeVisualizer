#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window {
private:
    SDL_Window*   window;
    SDL_Renderer* renderer;
    SDL_Surface*  screen;
    int run, width, height;

    bool wasInited;

public:
    Window();
    Window(int, int, int, int, const char*); //width, height, x, y, caption

    virtual ~Window();

    virtual bool initialize(int, int, int, int, const char*);
    virtual bool isRun() const;
    virtual void clearScreen();
    virtual void presentScreen();

    virtual void stop();
    virtual SDL_Renderer* getRenderer() { return renderer; }
    virtual SDL_Surface* getScreen() { return screen; }
};

Window::Window() { window = NULL; renderer = NULL; screen = NULL; wasInited = false; }

Window::Window(int w, int h, int x, int y, const char* caption) {
    initialize(w, h, x, y, caption);
}

Window::~Window() {
    SDL_FreeSurface(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    if ( wasInited ) {
        SDL_Quit();
    }
}

bool Window::initialize(int w, int h, int x, int y, const char* caption) {
    window = NULL;
    renderer = NULL;
    screen = NULL;

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        wasInited = false;
        return false;
    }
    wasInited = true;

    window = SDL_CreateWindow(caption, x, y, w, h, 0);
    if ( !window ) {
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if ( !renderer ) {
        return false;
    }
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_GetWindowSize(window, &width, &height);
    screen = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);

    if ( !screen ) {
        return false;
    }

    run = 1;

    return true;
}

bool Window::isRun() const {
    return run;
}

void Window::clearScreen() {
    SDL_FillRect(screen, NULL, 0x0);
}

void Window::presentScreen() {
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, screen);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tex, NULL, NULL);
    SDL_RenderPresent(renderer);

    SDL_DestroyTexture(tex);
}

void Window::stop() {
    run = 0;
}

#endif