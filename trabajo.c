#include <stdio.h>

#define ASIGNATURAS 3
#define NOTA_MINIMA 0.0
#define NOTA_MAXIMA 10.0
#define NOTA_APROBATORIA 6.0

typedef struct {
    float calificaciones[ASIGNATURAS];
} Estudiante;

void cargarCalificaciones(int n, Estudiante *lista);
void procesarEstudiantes(int n, Estudiante *lista);
void procesarAsignaturas(int n, Estudiante *lista);

int main() {
    int numEstudiantes;
    printf("==================================================\n");
    printf("      SISTEMA DE GESTION DE CALIFICACIONES        \n");
    printf("==================================================\n");

    do {
        printf("Ingrese la cantidad de estudiantes: ");
        if (scanf("%d", &numEstudiantes) != 1 || numEstudiantes <= 0) {
            printf("Error: Ingrese un entero positivo.\n");
            while (getchar() != '\n'); 
            numEstudiantes = 0;
        }
    } while (numEstudiantes <= 0);

    Estudiante listaEstudiantes[numEstudiantes];

    cargarCalificaciones(numEstudiantes, listaEstudiantes);
    procesarEstudiantes(numEstudiantes, listaEstudiantes);
    procesarAsignaturas(numEstudiantes, listaEstudiantes);

    return 0;
}

// MODIFICADO: Lógica 100% migrada al uso de Struct y puntero flecha
void cargarCalificaciones(int n, Estudiante *lista) {
    for (int i = 0; i < n; i++) {
        printf("\n--- Registro - Estudiante %d ---\n", i + 1);
        for (int j = 0; j < ASIGNATURAS; j++) {
            
            float *nota = &(lista + i)->calificaciones[j]; 
            
            do {
                printf("  Asignatura %d: ", j + 1);
                if (scanf("%f", nota) != 1) {
                    printf("    [!] Error de lectura. Reintente.\n");
                    while (getchar() != '\n'); 
                    *nota = -1.0; 
                } else if (*nota < NOTA_MINIMA || *nota > NOTA_MAXIMA) {
                    printf("    [!] Rango invalido (%.1f - %.1f).\n", NOTA_MINIMA, NOTA_MAXIMA);
                }
            } while (*nota < NOTA_MINIMA || *nota > NOTA_MAXIMA);
        }
    }
}

// Sigue con cast temporal
void procesarEstudiantes(int n, Estudiante *lista) {
    float *ptr = (float *)lista;
    printf("\n==================================================\n");
    printf("          REPORTE GENERAL POR ESTUDIANTE          \n");
    printf("==================================================\n");
    printf("Estudiante\tPromedio\tNota Max\tNota Min\n");
    printf("--------------------------------------------------\n");

    for (int i = 0; i < n; i++) {
        float *fila = ptr + (i * ASIGNATURAS); 
        float suma = 0;
        float max = *fila; 
        float min = *fila; 

        for (int j = 0; j < ASIGNATURAS; j++) {
            float val = *(fila + j); 
            suma += val;
            if (val > max) max = val;
            if (val < min) min = val;
        }
        printf("Alumno %d\t%.2f\t\t%.2f\t\t%.2f\n", i + 1, suma / ASIGNATURAS, max, min);
    }
}

// Sigue con cast temporal
void procesarAsignaturas(int n, Estudiante *lista) {
    float *ptr = (float *)lista;
    printf("\n==================================================\n");
    printf("          REPORTE GENERAL POR ASIGNATURA          \n");
    printf("==================================================\n");

    for (int j = 0; j < ASIGNATURAS; j++) {
        float suma = 0;
        float max = *(ptr + j); 
        float min = *(ptr + j);
        int aprobados = 0;

        for (int i = 0; i < n; i++) {
            float val = *(ptr + (i * ASIGNATURAS) + j); 
            suma += val;
            if (val > max) max = val;
            if (val < min) min = val;
            if (val >= NOTA_APROBATORIA) aprobados++;
        }

        printf("Asignatura %d:\n", j + 1);
        printf("  > Promedio General  : %.2f\n", suma / n);
        printf("  > Calificacion Alta : %.2f\n", max);
        printf("  > Calificacion Baja : %.2f\n", min);
        printf("  > Aprobados: %d | Reprobados: %d\n", aprobados, n - aprobados);
        printf("--------------------------------------------------\n");
    }
}