#ifndef COLOR_RGB_H
#define COLOR_RGB_H

#include "types.h"

#define MAX_RED     255
#define MAX_GREEN   255
#define MAX_BLUE    255

typedef struct ColorRGB {
    u8 r, g, b;
} ColorRGB;

u32  ColorRGB_toNum   (const ColorRGB*                                             );
void ColorRGB_fromNum (const u32,             ColorRGB*                            );
void ColorRGB_sum     (const ColorRGB*, const ColorRGB*,       ColorRGB*           );
void ColorRGB_modulate(const f32,             ColorRGB*                            );
void ColorRGB_blend   (const f32,       const ColorRGB*, const ColorRGB*, ColorRGB*);

u32 ColorRGB_toNum(const ColorRGB* color) {
    return ( ((u32)color->r) << 16 ) + ( ((u32)color->g) << 8 ) + (u32)color->b;
}

void ColorRGB_fromNum(const u32 num, ColorRGB* color) {
    color->r = (u8)(num >> 16);
    color->g = (u8)(num >> 8);
    color->b = (u8)num;
}

void ColorRGB_sum(const ColorRGB* c1, const ColorRGB* c2, ColorRGB* res) {
    res->r = (u8)MIN(MAX_RED,   (u32)c1->r + c2->r);
    res->g = (u8)MIN(MAX_GREEN, (u32)c1->g + c2->g);
    res->b = (u8)MIN(MAX_BLUE,  (u32)c1->b + c2->b);
}

void ColorRGB_modulate(const f32 coeff, ColorRGB* color) {
    color->r = (u8)MIN(MAX_RED,   (u32)(coeff * color->r));
    color->g = (u8)MIN(MAX_GREEN, (u32)(coeff * color->g));
    color->b = (u8)MIN(MAX_BLUE,  (u32)(coeff * color->b));
}

//coeff from [0, 1]
void ColorRGB_blend(const f32 coeff, const ColorRGB* c1, const ColorRGB* c2, ColorRGB* res) {
    ColorRGB t1 = *c1;
    ColorRGB t2 = *c2;
    
    ColorRGB_modulate(coeff, &t1);    
    ColorRGB_modulate(1.0f - coeff, &t2);
    ColorRGB_sum(&t1, &t2, res);
}

#endif