#include "hittable.h"
#include "rtweekend.h"
#include "material.h"
#include "camera.h"
    
int main(void) { 
    // Materiales (¡deben sobrevivir a todo el render!)
    material mat_ground = { LAMBERTIAN, v3(0.8, 0.8, 0.0), 0, 0 };
    material mat_center = { LAMBERTIAN, v3(0.1, 0.2, 0.5), 0, 0 };
    material mat_left   = { DIELECTRIC, v3(  0,   0,   0), 0, 1.50 };
    material mat_bubble = { DIELECTRIC, v3(  0,   0,   0), 0, 1.0/1.50 };
    material mat_right  = { METAL     , v3(0.8, 0.6, 0.2), 1.0, 0 };
    
    sphere spheres[] = {
        { v3( 0, -100.5, -1), 100.0, &mat_ground }, 
        { v3( 0,      0, -1.2), 0.5, &mat_center }, 
        { v3(-1,      0, -1),   0.5, &mat_left },   // esfera de vidrio
        { v3(-1,      0, -1),   0.4, &mat_bubble },  // burbuja dentro (mismo centro)
        { v3( 1,      0, -1),   0.5, &mat_right },
    };
    hittable_list world = { spheres, 5 };
   
    // Camara: fija los parametros y renderiza
    camera cam;
    cam.aspect_ratio      = 16.0 / 9.0;
    cam.image_width       = 400;
    cam.samples_per_pixel = 100;
    cam.max_depth         = 50;
    cam.vfov              = 20;
    cam.lookfrom          = v3(-1, 3, 2);
    cam.lookat            = v3(0, 0, -1);
    cam.vup               = v3(0, 1, 0);

    camera_render(&cam, world);
    return 0;
}
        
        
        
        
