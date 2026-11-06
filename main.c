#include <stdio.h> 
#include "vec3.h"
#include "color.h"

int main(void) { 
    int image_width  = 256;
    int image_height = 256;

    printf("P3\n%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; j++) {
        fprintf(stderr, "\rFilas restantes: %d ", image_height - j);
        fflush(stderr);
        for (int i = 0; i < image_width; i++) {
            color pixel = v3((double)i / (image_width - 1),
                             (double)j / (image_height - 1),
                             0.0);
            write_color(stdout, pixel);
        }
    }
    fprintf(stderr, "\r¡Listo!                 \n");
    
    // Reto Tarea 2
    vec3 a = v3(1, 0, 0);
    vec3 b = v3(0, 1, 0);
    double p = vec3_dot(a, b);
    vec3 c = vec3_cross(a, b);
    // Imprimir por stderr
    fprintf(stderr, "vectors = (%f %f %f), (%f %f %f)\n", a.x, a.y, a.z, b.x, b.y, b.z);
    fprintf(stderr, "dot = %f\n", p);
    fprintf(stderr, "cross = (%f %f %f)\n", c.x, c.y, c.z); 
    
    return 0;
}
    
        
        
        
        
        
        
        
        
