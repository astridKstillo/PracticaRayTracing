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
            write_color(stdout, pixel); // exporta el color
        }
    }
    fprintf(stderr, "\r¡Listo!                       \n"); 
    return 0;
}
        
        
        
        
        
        
        
        
        
        
