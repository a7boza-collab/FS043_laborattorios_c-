#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

int main() {
    // El tamaño N que pide la tarea
    int N = 1280; 

    // Inicializar matrices como vectores de una sola dimensión segun la guia
    // Matriz A con 1.5, B con 2.0 y C en 0.0
    vector<double> A(N * N, 1.5); 
    vector<double> B(N * N, 2.0); 
    vector<double> C(N * N, 0.0); 

    // Aqui se cambia el numero de hilos a mano para cada prueba (1, 2, 4, 8, etc.)
    int hilos = 8;
    omp_set_num_threads(hilos);

    cout << "Ejecutando con " << hilos << " hilos..." << endl;

    // Empezar a medir el tiempo con OpenMP
    double t_inicio = omp_get_wtime();

    // Multiplicacion matricial con tres bucles anidados
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                // Acceso a los elementos usando la formula de la guia
                C[i * N + j] += A[i * N + k] * B[k * N + j]; 
            }
        }
    }

    // Tiempo total
    double t_fin = omp_get_wtime();
    double duracion = t_fin - t_inicio;

    cout << "Tiempo de ejecucion: " << duracion << " segundos" << endl;

    return 0;
}
