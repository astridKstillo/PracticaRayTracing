#ifndef RTWEEKEND_H 
#define RTWEEKEND_H

#include <math.h>
#include <stdlib.h>  
#include "vec3.h"

#define PI 3.1415926535897932385 

static inline double degrees_to_radians(double degrees) {
    return degrees * PI / 180.0;
}

static inline double random_double(void) {
    return rand() / (RAND_MAX + 1.0);
}

static inline double random_double_range(double min, double max) {
    return min + (max - min) * random_double();
}

static inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Vector con componentes aleatorias
static inline vec3 vec3_random(void) {
    return v3(random_double(), random_double(), random_double());
}
static inline vec3 vec3_random_range(double min, double max) { // punto aleat en el cubo [-1,1]^3
    return v3(random_double_range(min, max),
              random_double_range(min, max),
              random_double_range(min, max));
}

// Vector unitario con direccion uniformemente aleatoria
static inline vec3 random_unit_vector(void) {
    while (1) {
        vec3 p = vec3_random_range(-1, 1);
        double lensq = vec3_length_squared(p);
        if (1e-160 < lensq && lensq <= 1.0)  // dentro de la esfera unit y no degenerado
            return vec3_div(p, sqrt(lensq)); 
    }
}

// Vector aleatorio en el hemisferio de la normal (una alternativa)
static inline vec3 random_on_hemisphere(vec3 normal) {
    vec3 on_unit = random_unit_vector();
    return vec3_dot(on_unit, normal) > 0.0 ? on_unit : vec3_neg(on_unit);
} // mide si on_unit apunta en mismo sentido que normal 

// ¿Es el vector practicamente cero? (lo usaremos en la Tarea 8)
static inline int vec3_near_zero(vec3 v) {
    double s = 1e-8;
    return (fabs(v.x) < s) && (fabs(v.y) < s) && (fabs(v.z) < s); // valor abs doubl
}

// Reflexion especular: refleja v respecto a la normal n.  r = v−2(v⋅n)n 
static inline vec3 reflect(vec3 v, vec3 n) {
    return vec3_sub(v, vec3_scale(n, 2 * vec3_dot(v, n)));
}

// Refraccion segun la ley de Snell.
// uv: direccion unitaria entrante; n: normal; etai_over_etat = eta / eta'
static inline vec3 refract(vec3 uv, vec3 n, double etai_over_etat) {
    double cos_theta = fmin(vec3_dot(vec3_neg(uv), n), 1.0);
    vec3 r_out_perp = vec3_scale(vec3_add(uv, vec3_scale(n, cos_theta)), etai_over_etat);
    double k = 1.0 - vec3_length_squared(r_out_perp);
    vec3 r_out_parallel = vec3_scale(n, -sqrt(fabs(k)));
    return vec3_add(r_out_perp, r_out_parallel);
}



#endif


