#include <vector>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

//Sistema de Lorenz
const double sigma = 10.0;
const double rho = 28.0;
const double beta = 8.0/3.0;

// Ecuaciones
std::vector<double> lorenz(const std::vector<double>& r) {
    double x = r[0];
    double y = r[1];
    double z = r[2];
    double dx = sigma * (y - x);
    double dy = x * (rho - z) - y;
    double dz = x * y - beta * z;
    return {dx, dy, dz};
}

// Euler
std::vector<std::vector<double>> euler(double h, double t0, double tf, double x0, double y0, double z0) {
    int N = static_cast<int>((tf - t0) / h) + 1;
    std::vector<std::vector<double>> sol(N, std::vector<double>(3));
    sol[0][0] = x0;
    sol[0][1] = y0;
    sol[0][2] = z0;
    for (int i = 0; i < N-1; i++) {
        std::vector<double> f = lorenz(sol[i]);
        sol[i+1][0] = sol[i][0] + h * f[0];
        sol[i+1][1] = sol[i][1] + h * f[1];
        sol[i+1][2] = sol[i][2] + h * f[2];
    }
    return sol;
}

// Runge-Kutta 2
std::vector<std::vector<double>> rk2(double h, double t0, double tf, double x0, double y0, double z0) {
    int N = static_cast<int>((tf - t0) / h) + 1;
    std::vector<std::vector<double>> sol(N, std::vector<double>(3));
    sol[0][0] = x0;
    sol[0][1] = y0;
    sol[0][2] = z0;
    for (int i = 0; i < N-1; i++) {
        std::vector<double> r = sol[i];
        std::vector<double> k1 = lorenz(r);
        std::vector<double> r2 = {r[0]+h/2*k1[0], r[1]+h/2*k1[1], r[2]+h/2*k1[2]};
        std::vector<double> k2 = lorenz(r2);
        sol[i+1][0] = r[0] + h * k2[0];
        sol[i+1][1] = r[1] + h * k2[1];
        sol[i+1][2] = r[2] + h * k2[2];
    }
    return sol;
}

// Runge-Kutta 4
std::vector<std::vector<double>> rk4(double h, double t0, double tf, double x0, double y0, double z0) {
    int N = static_cast<int>((tf - t0) / h) + 1;
    std::vector<std::vector<double>> sol(N, std::vector<double>(3));
    sol[0][0] = x0;
    sol[0][1] = y0;
    sol[0][2] = z0;
    for (int i = 0; i < N-1; i++) {
        std::vector<double> r = sol[i];
        std::vector<double> k1 = lorenz(r);
        std::vector<double> r2 = {r[0]+h/2*k1[0], r[1]+h/2*k1[1], r[2]+h/2*k1[2]};
        std::vector<double> k2 = lorenz(r2);
        std::vector<double> r3 = {r[0]+h/2*k2[0], r[1]+h/2*k2[1], r[2]+h/2*k2[2]};
        std::vector<double> k3 = lorenz(r3);
        std::vector<double> r4 = {r[0]+h*k3[0], r[1]+h*k3[1], r[2]+h*k3[2]};
        std::vector<double> k4 = lorenz(r4);
        sol[i+1][0] = r[0] + (h/6)*(k1[0] + 2*k2[0] + 2*k3[0] + k4[0]);
        sol[i+1][1] = r[1] + (h/6)*(k1[1] + 2*k2[1] + 2*k3[1] + k4[1]);
        sol[i+1][2] = r[2] + (h/6)*(k1[2] + 2*k2[2] + 2*k3[2] + k4[2]);
    }
    return sol;
}

// Conectar con Python
PYBIND11_MODULE(metodos_lorenz, m) {
    m.def("euler", &euler);
    m.def("rk2", &rk2);
    m.def("rk4", &rk4);
}
