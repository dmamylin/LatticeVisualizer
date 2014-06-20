#ifndef UTILITIES_H
#define UTILITIES_H

#include <SDL2/SDL.h>
#include <math.h>

typedef unsigned int u32;

template<class T>
T min(T a, T b) {
    return a < b ? a : b;
}

template<class T>
T max(T a, T b) {
    return a < b ? b : a;
}

//цвет указывается в формате: 0xAARRGGBB или 0xRRGGBB
void setPixel(SDL_Surface* s, int x, int y, u32 color) {
    ((u32*)s->pixels)[y * s->w + x] = color;
}

void drawDot(SDL_Surface* s, int x, int y, int size, u32 color) {
    for ( int i = 0; i < size; i++ ) {
        for ( int j = 0; j < size; j++ ) {
            setPixel(s, x - (size/2 - i), y - (size/2 - j), color);
        }
    }
}

void drawLine(SDL_Surface* s, int x1, int y1, int x2, int y2, u32 color) {
    int start, end, i;    
    double k, b;    
    int dx = x1 - x2;
    int dy = y1 - y2;

    if ( abs(dx) >= abs(dy) ) {
        start = min(x1, x2);
        end   = max(x1, x2);

        k = ( (double)(y1 - y2) ) / dx;
        b = ( (double)(x1 * y2 - x2 * y1) ) / dx;
        
        for (i = start; i <= end; i++) {
            int y = (int)(k * i + b);
            
            setPixel(s, i, y, color);
        }
    } else {
        start = min(y1, y2);
        end   = max(y1, y2);

        k = ( (double)(dx) ) / abs(dy);
        b = -( (double)(x1 * y2 - x2 * y1) ) / abs(dy);
        
        for (i = start; i <= end; i++) {
            int x = (int)(k*i + b);
            
            setPixel(s, x, i, color);
        }
    }
}

#endif