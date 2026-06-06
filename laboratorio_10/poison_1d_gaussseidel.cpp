/* poisson_1d_GaussSeidel.cpp
Compila igual que el otro
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
    vector<double> u(N + 1, 0.0); // no se usa u_new
    vector<double> u_exacta(N + 1);

    for (int i = 0; i <= N; i++)
    {
        x[i] = a + i * h;
        u_exacta[i] = solucionar_exacta(x[i]);
    }

    // Condiciones de frontera
    u[0] = alfa;
    u[N] = beta;

    int iter = 0;
       double error = 1.0;

    while (iter < max_iter && error > tol)
    {
        /* Su código aquí */
        double max_err = 0.0;
        vector<double> u_ant(N+1);

        // guardo valores anteriores
        for (int i=0; i<=N; i++)
        {
            u_ant[i] = u[i];
        }

        // actualizar puntos de adentro
        for (int i = 1; i < N; i++)
        {
            u[i] = ( u[i-1] + u[i+1] - h*h * fuente(x[i]) ) / 2.0;
            
            // calculo el error
            double dif = u[i] - u_ant[i];
            if (dif < 0) {
                dif = -dif;
            }
            if (dif > max_err) {
                max_err = dif;
            }
        }

        error = max_err;
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

    plt::figure();
    plt::plot(x, u);
    plt::plot(x, u_exacta, "r--");
    plt::title("Solucion Gauss-Seidel");
    plt::xlabel("x");
    plt::ylabel("valor");
    plt::save("solucion_gauss_seidel.png");

    plt::figure();
    plt::plot({iter}, {error}, "bo");
    plt::title("Error final Gauss-Seidel");
    plt::save("error_gauss_seidel.png");


    return 0;
}
