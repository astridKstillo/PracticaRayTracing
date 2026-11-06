#ifndef COLOR_H
#define COLOR_H

#include <stdio.h> 
// <...>: busca en las carpetas del sistema (librerías estándar).
#include "vec3.h" // "...": busca primero en tu carpeta (tus propios headers).

// Escribe un pixel en formato PPM (tres enteros 0..255) en el flujo "out".
static void write_color(FILE *out, color pixel_color) {
    double r = pixel_color.x;
    double g = pixel_color.y;
    double b = pixel_color.z;
    
    // Pasamos de [0,1] a bytes [0,255]
    int ir = (int)(255.999 * r);
    int ig = (int)(255.999 * g);
    int ib = (int)(255.999 * b);
     
    fprintf(out, "%d %d %d\n", ir, ig, ib);
}

#endif
    
