/* poisson_1d_Jacobi.cpp
Repositorio oficial Matplotlib-cpp:
https://github.com/lava/matplotlib-cpp

Recuerde descargar el archivo matplotlibcpp.h y
colóquelo en el mismo directorio que este código.

Compilador como:
g++ poisson_1d_Jacobi.cpp -o poisson_1d_Jacobi.x \
-I$CONDA_PREFIX/include/python3.10 \
-I$(python3 -c "import numpy; print(numpy.get_include())") \
-L$CONDA_PREFIX/lib \
-lpython3.10 \
-Wl,-rpath,$CONDA_PREFIX/lib
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "matplotlibcpp.h"

using namespace std;
namespace plt = matplotlibcpp;

double fuente(double x)
{
    return sin(M_PI * x);
}

double solucionar_exacta(double x)
{
    return -sin(M_PI * x) / (M_PI * M_PI);
}

int main()
{
    const int N = 10; // numero de subintervalos
    const double a = 0.0;
    const double b = 1.0;
    const double h = (b - a) / N;

    const double alfa = 0.0; // u(a)
    const double beta = 0.0;  // u(b)

    const int max_iter = 100000;
    const double tol = 1e-10;

    vector<double> x(N + 1);
    vector<double> u(N + 1, 0.0);
    vector<double> u_new(N + 1, 0.0); // Vector auxiliar necesario para Jacobi
    vector<double> u_exacta(N + 1);

    for (int i = 0; i <= N; i++)
    {
        x[i] = a + i * h;
        u_exacta[i] = solucionar_exacta(x[i]);
    }

    // Condiciones de frontera en ambos vectores
    u[0] = alfa;
    u[N] = beta;
    u_new[0] = alfa;
    u_new[N] = beta;

    int iter = 0;
    double error = 1.0;

    while (iter < max_iter && error > tol)
    {
        /* Su código aquí */
        double max_err = 0.0;

        // actualizar los puntos interiores i=1,...,N-1
        for (int i = 1; i < N; i++)
        {
            u_new[i] = ( u[i-1] + u[i+1] - h*h * fuente(x[i]) ) / 2.0;
            
            // calcular error maximo entre iteraciones
            double dif = u_new[i] - u[i];
            if (dif < 0) {
                dif = -dif;
            }
            if (dif > max_err) {
                max_err = dif;
            }
        }

        // guardar el error
        error = max_err;

        // copiar los valores de u_new hacia u
        for (int i = 0; i <= N; i++)
        {
            u[i] = u_new[i];
        }

        // incrementar contador
        iter = iter + 1;

    }

    cout << "Iteraciones: " << iter << endl;
    cout << "Error final: " << error << endl;

    double error_maximo = 0.0;
    for (int i = 0; i <= N; i++)
    {
        error_maximo = max(error_maximo, abs(u[i] - u_exacta[i]));
    }
    cout << "Error máximo contra solución exacta: " << error_maximo << endl;

    /* Grafique la solución numérica y
       la solución exacta usando matplotlibcpp. */

    // graficar soluciones
    plt::figure();
    plt::plot(x, u);
    plt::plot(x, u_exacta, "r--");
    plt::title("Solucion Jacobi");
    plt::xlabel("x");
    plt::ylabel("valor");
    plt::save("solucion_jacobi.png");

    // graficar error
    plt::figure();
    plt::plot({iter}, {error}, "bo");
    plt::title("Error final");
    plt::save("error_jacobi.png");


    return 0;
}
