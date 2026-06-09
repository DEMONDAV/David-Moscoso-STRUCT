#include <stdio.h>

#define ASIGNATURAS 3
#define NOTA_MINIMA 0.0
#define NOTA_MAXIMA 10.0
#define NOTA_APROBATORIA 6.0

// Funciones modulares que operan directamente sobre la memoria original usando punteros
void cargarCalificaciones(int n, float *ptr);
void procesarEstudiantes(int n, float *ptr);
void procesarAsignaturas(int n, float *ptr);

int main() {
    int numEstudiantes;
    printf("==================================================\n");
    printf("      SISTEMA DE GESTION DE CALIFICACIONES        \n");
    printf("==================================================\n");

    // Validación de la entrada del número de estudiantes
    do {
        printf("Ingrese la cantidad de estudiantes: ");
        if (scanf("%d", &numEstudiantes) != 1 || numEstudiantes <= 0) {
            printf("Error: Ingrese un entero positivo.\n");
            while (getchar() != '\n'); // Limpiar el buffer de entrada
            numEstudiantes = 0;
        }
    } while (numEstudiantes <= 0);

    // Definición de la matriz con el tamaño dinámico solicitado
    float calificaciones[numEstudiantes][ASIGNATURAS];

    // Se envía la dirección de memoria base convirtiéndola a un puntero simple (float *)
    cargarCalificaciones(numEstudiantes, (float *)calificaciones);
    procesarEstudiantes(numEstudiantes, (float *)calificaciones);
    procesarAsignaturas(numEstudiantes, (float *)calificaciones);

    return 0;
}

void cargarCalificaciones(int n, float *ptr) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Registro - Estudiante %d ---\n", i + 1);
        for (int j = 0; j < ASIGNATURAS; j++) {
            // Mapeo lineal: Calculamos la dirección exacta en la memoria física
            float *nota = ptr + (i * ASIGNATURAS) + j; 
            
            // Ciclo de validación de rango de notas (0 a 10)
            do {
                printf("  Asignatura %d: ", j + 1);
                if (scanf("%f", nota) != 1) {
                    printf("    [!] Error de lectura. Reintente.\n");
                    while (getchar() != '\n'); // Limpiar buffer en caso de letras
                    *nota = -1.0; // Forzar la repetición del bucle
                } else if (*nota < NOTA_MINIMA || *nota > NOTA_MAXIMA) {
                    printf("    [!] Rango invalido (%.1f - %.1f).\n", NOTA_MINIMA, NOTA_MAXIMA);
                }
            } while (*nota < NOTA_MINIMA || *nota > NOTA_MAXIMA);
        }
    }
}

void procesarEstudiantes(int n, float *ptr) {
    printf("\n==================================================\n");
    printf("          REPORTE GENERAL POR ESTUDIANTE          \n");
    printf("==================================================\n");
    printf("Estudiante\tPromedio\tNota Max\tNota Min\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        // Apuntamos al inicio de la "fila" matemática de este estudiante en el bloque de memoria
        float *fila = ptr + (i * ASIGNATURAS); 
        
        // Inicializamos los extremos con el primer elemento de la fila actual
        float suma = 0;
        float max = *fila; 
        float min = *fila; 

        for (int j = 0; j < ASIGNATURAS; j++) {
            float val = *(fila + j); // Acceso directo por desreferenciación aritmética
            suma += val;
            if (val > max) max = val;
            if (val < min) min = val;
        }
        
        // Cálculo del promedio e impresión de resultados individuales
        printf("Alumno %d\t%.2f\t\t%.2f\t\t%.2f\n", i + 1, suma / ASIGNATURAS, max, min);
    }
}

void procesarAsignaturas(int n, float *ptr) {
    printf("\n==================================================\n");
    printf("          REPORTE GENERAL POR ASIGNATURA          \n");
    printf("==================================================\n");

    for (int j = 0; j < ASIGNATURAS; j++) {
        // Inicializamos max y min con la nota del primer alumno (fila 0) en la columna j actual
        float suma = 0;
        float max = *(ptr + j); 
        float min = *(ptr + j);
        int aprobados = 0;

        for (int i = 0; i < n; i++) {
            // Desplazamiento vertical en la memoria: Saltamos de fila en fila (i * ASIGNATURAS)
            // manteniendo fija la columna actual (+ j)
            float val = *(ptr + (i * ASIGNATURAS) + j); 
            suma += val;
            
            if (val > max) max = val;
            if (val < min) min = val;
            if (val >= NOTA_APROBATORIA) aprobados++;
        }

        // Impresión detallada por materia aplicando aritmética básica para reprobados
        printf("Asignatura %d:\n", j + 1);
        printf("  > Promedio General  : %.2f\n", suma / n);
        printf("  > Calificacion Alta : %.2f\n", max);
        printf("  > Calificacion Baja : %.2f\n", min);
        printf("  > Aprobados: %d | Reprobados: %d\n", aprobados, n - aprobados);
        printf("--------------------------------------------------\n");
    }
}