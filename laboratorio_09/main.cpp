#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

// FUNCIÓN 1: f(x,t) = -x + sin(t)  (5 puntos)
double f(double x, double t) {
    return -x + sin(t);
}

// FUNCIÓN 2: Solución exacta / analítica  (5 puntos)
double exacta(double t) {
    return 0.5 * (sin(t) - cos(t)) + 1.5 * exp(-t);
}

// FUNCIÓN 3: Método de Euler, recibe vectores POR REFERENCIA  (30 puntos)
void euler(double t0, double tf, double h, double x0,
           vector<double>& t_vec,
           vector<double>& x_num,
           vector<double>& x_exa,
           vector<double>& error_abs) {

    int N = static_cast<int>( (tf - t0) / h );
    double t = t0;
    double x = x0;

    // Guardar valor inicial
    t_vec.push_back(t);
    x_num.push_back(x);
    x_exa.push_back( exacta(t) );
    error_abs.push_back( abs(x - exacta(t)) );

    // Fórmula de Euler: x_{n+1} = x_n + h * f(x_n, t_n)
    for (int n = 0; n < N; n++) {
        x = x + h * f(x, t);
        t = t + h;
        t_vec.push_back(t);
        x_num.push_back(x);
        x_exa.push_back( exacta(t) );
        error_abs.push_back( abs(x - exacta(t)) );
    }
}

int main() {
    // PARÁMETROS QUE DICE EL LABORATORIO
    double t0 = 0.0;
    double tf = 10.0;
    double h  = 0.1;
    double x0 = 1.0;

    // CONTENEDORES OBLIGATORIOS (5 puntos)
    vector<double> t;
    vector<double> sol_num;
    vector<double> sol_exa;
    vector<double> error;

    // Llamar al método
    euler(t0, tf, h, x0, t, sol_num, sol_exa, error);

    // CALCULAR ERROR GLOBAL MÁXIMO (25 puntos)
    double error_max = 0.0;
    for (double e : error) {
        if (e > error_max) error_max = e;
    }

    // IMPRIMIR TABLA EN PANTALLA
    cout << "t\tEuler\t\tExacta\t\tError\n";
    for (size_t i = 0; i < t.size(); i++) {
        printf("%.6f\t%.6f\t%.6f\t%.6f\n", t[i], sol_num[i], sol_exa[i], error[i]);
    }
    cout << "\nError global máximo = " << error_max << endl;

    // GUARDAR RESULTADOS EN ARCHIVO output.txt
    ofstream archivo("output.txt");
    archivo << "t\tEuler\t\tExacta\t\tError\n";
    for (size_t i = 0; i < t.size(); i++) {
        archivo << t[i] << "\t" << sol_num[i] << "\t" << sol_exa[i] << "\t" << error[i] << "\n";
    }
    archivo << "\nError global máximo = " << error_max << "\n";
    archivo.close();

    // ✅ GUARDAR DATOS PARA GRÁFICAS (esto es lo nuevo)
    ofstream datos("datos_graficas.txt");
    for (size_t i = 0; i < t.size(); i++) {
        datos << t[i] << " " << sol_num[i] << " " << sol_exa[i] << " " << error[i] << "\n";
    }
    datos.close();

    return 0;
}

