#include <iostream>
#include <mpi.h>
#include <cmath>
#include <vector>
#include <fstream>

// Tamaño de los vectores
// pedido en la tarea
const int N = 128000;

// La función
double f(double x) {
    return std::sin(x);
}

int main(int argc, char** argv){
    // Iniciamos el entorno de MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    // número de
    // proceso (rank) y el total
    // (size)
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Calculamos cuántos elementos le tocan a cada proceso
    int local_n = N / size;

    // para guardar la parte que le toca a este proceso
    std::vector<double> local_A(local_n);
    std::vector<double> local_B(local_n);

    // Solo el proceso 0
    
    if (rank == 0) {
        std::vector<double> A(N);
        std::vector<double> B(N);

        // Llenamos los vectores 
        
        for (int i = 0; i < N; i++) {
            A[i] = f((double)i);
            B[i] = 2.0 * f((double)i);
        }

        // Se envia lo q le toca a cadaproceso
        
        for (int i = 1; i < size; i++) {
            int indice_inicio = i * local_n;
            // Usamos la
            // etiqueta 10 para el vector A y
            // la 20 para el B
            MPI_Send(&A[indice_inicio], local_n, MPI_DOUBLE, i, 10, MPI_COMM_WORLD);
            MPI_Send(&B[indice_inicio], local_n, MPI_DOUBLE, i, 20, MPI_COMM_WORLD);
        }

      
        for (int i = 0; i < local_n; i++) {
            local_A[i] = A[i];
            local_B[i] = B[i];
        }
    } else {
        // para los procesos que no son el 0 
        MPI_Recv(local_A.data(), local_n, MPI_DOUBLE, 0, 10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(local_B.data(), local_n, MPI_DOUBLE, 0, 20, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Usamos MPI_Wtime para saber cuánto tarda este pedazo
    double t_inicio = MPI_Wtime();

    double suma_local = 0.0;
    for (int i = 0; i < local_n; i++) {
        suma_local += local_A[i] * local_B[i];
    }

    double t_fin = MPI_Wtime();

    double suma_total = 0.0;
    // Juntamos todos los resultados en el proceso 0 con MPI_SUM
    MPI_Reduce(&suma_local, &suma_total, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Solo el proceso 0 imprime y guarda el tiempo
    if (rank == 0) {
        double tiempo_que_tardo = t_fin - t_inicio;
        std::cout << "El resultado es: " << suma_total << std::endl;

    }

    // Cerramos MPI
    MPI_Finalize();
    return 0;
}
