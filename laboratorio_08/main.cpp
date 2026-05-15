#include <iostream>
#include <iomanip>
#include <cmath>
#include "funciones.h"
#include "integracion.h"

using namespace std;

int main(){
    int n;
    double h;
    double *x;
    double *f_x;
    const double VALOR_EXACTO = M_PI;
    double res_trap, res_simp;
    double error_trap, error_simp;

    cout << "Ingrese el numero de subintervalos: ";
    cin >> n;

    // Crear arreglos dinámicos con new
    x = new double[n + 1];
    f_x = new double[n + 1];

    // Calcular el paso h = (b - a)/n → [0,1]
    h = 1.0 / n;

    // Llenar los arreglos con for
    for(int i = 0; i <= n; i++){
        x[i] = i * h;           // Puntos x_i
        f_x[i] = f(x[i]);       // Valores de f(x_i)
    }

    // Calcular integrales
    res_trap = trapecio_compuesto(f_x, n, h);
    res_simp = simpson_compuesto(f_x, n, h);

    // Calcular errores absolutos
    error_trap = fabs(res_trap - VALOR_EXACTO);
    error_simp = fabs(res_simp - VALOR_EXACTO);

    // Mostrar resultados
    cout << fixed << setprecision(6);
    cout << "\n=====================================" << endl;
    cout << "Integral de 4/(1+x^2) en [0,1]" << endl;
    cout << "=====================================" << endl;
    cout << "Trapecio compuesto: " << res_trap << endl;
    cout << "Simpson compuesto:  " << res_simp << endl;
    cout << "Valor exacto:       " << VALOR_EXACTO << endl;
    cout << "\nErrores absolutos:" << endl;
    cout << "Error trapecio:     " << error_trap << endl;
    cout << "Error Simpson:      " << error_simp << endl;

    // Liberar memoria con delete[]
    delete [] x;
    delete [] f_x;

    return 0;
}
