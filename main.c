#include <stdio.h> 
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include <math.h>  // INFINITY
#include "hittable.h"

 // COLOR
    color ray_color(ray r, hittable_list world) {
    hit_record rec;
    if (world_hit(world, r, 0.0, INFINITY, &rec)) { 
        // La normal esta en [-1,1]; la mapeamos a un color [0,1]
        return vec3_scale(vec3_add(rec.normal, v3(1,1,1)), 0.5);
    } 
     // cielo de antes si no hay impacto (devuelve 0)  
    vec3 unit_direction = vec3_unit(r.dir);
    double a = 0.5 * (unit_direction.y + 1.0);
    return vec3_add(vec3_scale(v3(1,1,1), 1.0 - a),
                    vec3_scale(v3(0.5,0.7,1.0),  a));
}
    
int main(void) { 
    // --- Imagen ---
    double aspect_ratio = 16.0 / 9.0;
    int image_width  = 400;
    int image_height = (int)(image_width / aspect_ratio);
    if (image_height < 1) image_height = 1;
    
    // --- Camara ---
    double focal_length    = 1.0;
    double viewport_height = 2.0;
    double viewport_width  = viewport_height * ((double)image_width / image_height);
    point3 camera_center   = v3(0, 0, 0);
    
    // Vectores que recorren el viewport (u: horizontal, v: vertical hacia abajo)
    vec3 viewport_u = v3(viewport_width, 0, 0);
    vec3 viewport_v = v3(0, -viewport_height, 0); // recorremos de arriba a abajo
    
    // Separacion entre pixeles
    vec3 pixel_delta_u = vec3_div(viewport_u, image_width);
    vec3 pixel_delta_v = vec3_div(viewport_v, image_height);
    
    // Esquina superior izquierda del viewport y centro del primer pixel
    point3 viewport_upper_left =
        vec3_sub(vec3_sub(vec3_sub(camera_center, v3(0,0,focal_length)),
                          vec3_scale(viewport_u, 0.5)),
                 vec3_scale(viewport_v, 0.5));
    point3 pixel00_loc = 
        vec3_add(viewport_upper_left,
                 vec3_scale(vec3_add(pixel_delta_u, pixel_delta_v), 0.5));
                       
    // El mundo: dos esfera. La grande hace de "suelo".
    sphere spheres[] = {
        { v3(0,      0, -1),   0.5, NULL }, // {centro, radio, material}
        { v3(0, -100.5, -1), 100.0, NULL }, // esfera gigante es el suelo
    };
    hittable_list world = { spheres, 2 };
     
    // --- Render ---
    printf("P3\n%d %d\n255\n", image_width, image_height);

    for (int j = 0; j < image_height; j++) {
        fprintf(stderr, "\rFilas restantes: %d ", image_height - j);
        fflush(stderr);
        for (int i = 0; i < image_width; i++) {
            point3 pixel_center =
                vec3_add(pixel00_loc,
                    vec3_add(vec3_scale(pixel_delta_u, i),
                             vec3_scale(pixel_delta_v, j)));
            vec3 ray_direction = vec3_sub(pixel_center, camera_center);
            ray r = { camera_center, ray_direction };
            // rellena los campos en orden. Tambien funcionan campos designados como
            // ray r = { .orig = camera_center, .dir = ray_direction };
            
            color pixel = ray_color(r, world);
            write_color(stdout, pixel);
        }
    }
    fprintf(stderr, "\r¡Listo!                 \n");
    return 0;
}
    
        
        
        
        
        
        
        
        
