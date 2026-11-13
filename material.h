#ifndef MATERIAL_H
#define MATERIAL_H

#include "rtweekend.h"
#include "hittable.h"

// La "etiqueta": que clase de material es.
typedef enum { // enum es un tipo que define ctes enteras con nombre
    LAMBERTIAN,   // mate (0)
    METAL,       // metalico (1)
    DIELECTRIC   // vidrio (Tarea 9) (2)
} material_type;

// Un unico struct que sirve para los tres materiales.
// Cada variante usa solo los campos que le interesan.
typedef struct material {
    material_type type;  
    color  albedo;             // LAMBERTIAN Y METAL: color/atenuacion
    double fuzz;               // METAL: cuanto se difumina el reflejo (0 = espejo)
    double refraction_index;   // DIELECTRIC: indice de refraccion
} material;

// Reflexion especular: refleja v respecto a la normal n.  r = v−2(v⋅n)n 
static inline vec3 reflect(vec3 v, vec3 n) {
    return vec3_sub(v, vec3_scale(n, 2 * vec3_dot(v, n)));
}

// scatter: dado un rayo entrante y un impacto, decide el rayo dispersado
// y cuanto atenua el calor. Devuelve 0 si el rayo se absorbe.
static int scatter (const material *mat, ray r_in, hit_record rec,
                    color *attenuation, ray *scattered) {
    switch (mat->type) {
    
    case LAMBERTIAN: {
        // Rebote difuso: normal + direccion aleatoria
        vec3 dir = vec3_add(rec.normal, random_unit_vector());
        if (vec3_near_zero(dir)) dir = rec.normal; // evita direccion nula
        scattered->orig = rec.p;
        scattered->dir  = dir;
        *attenuation = mat->albedo;
        return 1;
    }
    
    case METAL: {
        // Reflejo especular, opcionalmente difuminado por "fuzz"
        vec3 reflected = reflect(r_in.dir, rec.normal);
        reflected = vec3_add(vec3_unit(reflected),
                             vec3_scale(random_unit_vector(), mat->fuzz));
        scattered->orig = rec.p;
        scattered->dir  = reflected;
        *attenuation = mat->albedo;
        // Si el rayo difuminado se hunde bajo la superficie, se absorbe.
        return vec3_dot(scattered->dir, rec.normal) > 0;
    }

    case DIELECTRIC:
        // Se completa en Tarea 9
        return 0;
    }
    return 0;
}
        
#endif   
    
    
        
        
        
        
