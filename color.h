#ifndef COLOR_H
#define COLOR_H

#include <stdio.h> 
#include "vec3.h" 
#include "rtweekend.h"

// De lineal a gamma (gamma = 2) -> raiz cuadrada : aclara la imagen aplicando la inversa de la curva de la pantalla. 
static inline double linear_to_gamma(double linear) {
    return (linear > 0) ? sqrt(linear) : 0;
}

static void write_color(FILE *out, color pixel_color) {
    double r = linear_to_gamma(pixel_color.x);
    double g = linear_to_gamma(pixel_color.y);
    double b = linear_to_gamma(pixel_color.z);
    
    int ir = (int)(256 * clamp(r, 0.0, 0.999));
    int ig = (int)(256 * clamp(g, 0.0, 0.999));
    int ib = (int)(256 * clamp(b, 0.0, 0.999));
     
    fprintf(out, "%d %d %d\n", ir, ig, ib);
}

#endif
    
