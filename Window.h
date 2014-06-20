#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>

class Window {
private:
    SDL_Window*   window;
    SDL_Renderer* renderer;
    SDL_Surface*  screen;
    int run, width, height;

public:
    Window();

    virtual ~Window();

    virtual bool initialize(int, int, const char*); //ширина, высота, заголовок окна
    virtual bool isRun() const;
    virtual void clearScreen();
    virtual void presentScreen();
    virtual void cleanup();

    virtual void stop();
    virtual SDL_Renderer* getRenderer() { return renderer; }
    virtual SDL_Surface* getScreen() { return screen; }
};

Window::Window() { window = NULL; renderer = NULL; screen = NULL; }

Window::~Window() {}

bool Window::initialize(int w, int h, const char* caption) {
    if ( window || renderer || screen ) {
        puts("Error, window has benn already initialized!");
        return false;
    }

    window = SDL_CreateWindow(caption, SDL_WINDOWPOS_CENTERED, 
                              SDL_WINDOWPOS_CENTERED, w, h, 0);
    if ( !window ) {
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if ( !renderer ) {
        SDL_DestroyWindow(window);
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

void Window::cleanup() {
    SDL_FreeSurface(screen);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

#endif