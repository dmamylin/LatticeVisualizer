#ifndef UTILITIES_H
#define UTILITIES_H

#include <SDL2/SDL.h>
#include <math.h>

#include "ColorRGB.h"

typedef unsigned int u32;

void setPixel(SDL_Surface* s, int x, int y, u32 color) {
    ((u32*)s->pixels)[y * s->w + x] = color;
}

int _sqr(int x) {
    return x * x;
}

int _len(int x1, int y1, int x2, int y2) {
    return sqrt( _sqr(x1 - x2) + _sqr(y1 - y2) );
}

void drawLine(SDL_Surface* s, int x1, int y1, int x2, int y2, u32 c1, u32 c2) {
    int start, end_x, end_y, i;    
    double k, b, len;    
    ColorRGB col1, col2;
    int dx = x1 - x2;
    int dy = y1 - y2;
    
    ColorRGB_fromNum(c1, &col1);
    ColorRGB_fromNum(c2, &col2);
    len = _len(x1, y1, x2, y2);
    
    if ( abs(dx) >= abs(dy) ) {
        if (x1 < x2) {
            start = x1;
            end_x = x2;
            end_y = y2;
        } else {
            start = x2;
            end_x = x1;
            end_y = y1;
        }
        k     = ( (double)(y1 - y2) ) / dx;
        b     = ( (double)(x1 * y2 - x2 * y1) ) / dx;
        
        for (i = start; i <= end_x; i++) {
            ColorRGB color;
            int y = (int)(k * i + b);
            double coeff = _len(i, y, end_x, end_y) / len;
            
            ColorRGB_blend(coeff, &col1, &col2, &color);
            
            setPixel(s, i, y, ColorRGB_toNum(&color));
        }
    } else {
        if (x1 < x2) {
            start = x1;
            end_x = x2;
            end_y = y2;
        } else {
            start = x2;
            end_x = x1;
            end_y = y1;
        }
        k     = ( (double)(y1 - y2) ) / dx;
        b     = ( (double)(x1 * y2 - x2 * y1) ) / dx;
        
        for (i = start; i <= end_x; i++) {
            ColorRGB color;
            int y = (int)(k * i + b);
            double coeff = _len(i, y, end_x, end_y) / len;
            
            ColorRGB_blend(coeff, &col1, &col2, &color);
            
            setPixel(s, i, y, ColorRGB_toNum(&color));
        }
    }
}

#endif