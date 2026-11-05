#include <stdio.h> // Trae las funciones de entrada/salida (printf, fprintf). Sin esto no puedes escribir la imagen.

int main(void) { // void = no recibe argumentos.
    // Tamaño de la imagen en pixeles (cuadricula 256 col. 256 fil.)
    int image_width  = 256;
    int image_height = 256;
    
    // Cabecera del formato PPM en la salida estandar: "P3", dimensiones y valor maximo de color
    printf("P3\n%d %d\n255\n", image_width, image_height); // "etiqueta" del archivo para visor
    // Esto te permite "redirigir" el archivo final desde la terminal usando el operador >. 
    // Por ejemplo, si ejecutas ./mi_programa > imagen.ppm, todo lo que imprima este printf se guardará 
    // limpiamente dentro del archivo, creando la imagen.
    
    // Recorremos la imagen fila a fila (j), y dentro cada columna (i)
    for (int j = 0; j < image_height; j++) {
    
        // Barra progreso por stderr, para no mezclarlo con la imagen de stdout (> redirige solo stdout)
        fprintf(stderr, "\rFilas restantes: %d ", image_height - j);
        fflush(stderr); // \r devuelve el cursor al inicio de la línea para sobrescribir el mensaje (no llena la pantalla de líneas). 
        // El fflush fuerza a que se muestre ya, sin esperar.
     
        for (int i = 0; i < image_width; i++) { // dentro de una fila j, recorremos las columnas i de izq a der.
         
            // Componentes en [0,1) como numeros reales. Convertimos el indice del pixel (i,j)
            // en una coordenada dentro del cuadrado unitario (POSICIÓN NORMALIZADA en [0,1]x[0,1]).
            double r = (double)i / (image_width  - 1); // div por 255, r va de 0.0 a 1.0
            double g = (double)j / (image_height - 1 );
            double b = 0.0 // 0: degradado solo rojo y verde
            // cast (double) para que división no se trunque a 0 por (int).
        
            // Convertimos a enteros [0,255]. Pasamos de la coordenada [0,1] al rango de color [0,255]
            int ir = (int)(255.999 * r); // Multiplicamos por 255.999 para que r = 1.0 de 255 y no 256 que se saldría del byte ni 255 que daria 254.
            int ig = (int)(255.999 * g);
            int ib = (int)(255.999 * b);
        
            printf("%d %d %d\n", ir, ig, ib); // casilla (R,G,B)
        }
    }
    fprintf(stderr, "\r¡Listo!                       \n"); // avisa q terminó
    return 0;
}
        
        
        
        
        
        
        
        
        
        
