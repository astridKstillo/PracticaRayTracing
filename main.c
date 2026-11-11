#include <stdio.h> 
#include "vec3.h"
#include "color.h"
#include "ray.h"

// ¿El rayo r golpea la esfera de centro "center" y radio "radius"?
int hit_sphere(point3 center, double radius, ray r) {
    vec3 oc = vec3_sub(center, r.orig);          // C - A
    double a = vec3_dot(r.dir, r.dir);           // b . b
    double h = vec3_dot(r.dir, oc);              // b . (C - A)
    double c = vec3_dot(oc, oc) - radius*radius; // (C-A).(C-A) - r^2
    double discriminant = h*h - a*c;
    return discriminant >= 0;                    // 1 si toca, 0 si no
}

color ray_color(ray r) {
    // Una esfera roja centrada delante de la camara
    if (hit_sphere(v3(0, 0, -1), 0.5, r))
        return v3(1, 0, 0);   // rojo
        
    // Si no, el cielo de antes
    vec3 unit_direction = vec3_unit(r.dir);
    double a = 0.5 * (unit_direction.y + 1.0);  // a en [0,1]
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
            
            color pixel = ray_color(r);
            write_color(stdout, pixel);
        }
    }
    fprintf(stderr, "\r¡Listo!                 \n");
    return 0;
}
    
        
        
        
        
        
        
        
        
