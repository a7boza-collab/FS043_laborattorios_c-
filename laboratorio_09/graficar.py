import matplotlib.pyplot as plt
import numpy as np

# Leer los datos que generó tu programa
data = np.loadtxt("datos_graficas.txt")
t = data[:, 0]          # Valores de tiempo
euler = data[:, 1]     # Solución numérica
exacta = data[:, 2]    # Solución exacta
error = data[:, 3]     # Error absoluto

# 1. Gráfica comparativa
plt.figure(1)
plt.plot(t, euler, label="Método de Euler", color="blue")
plt.plot(t, exacta, label="Solución Analítica", color="red", linestyle="--")
plt.title("Comparación: Euler vs Solución Exacta")
plt.xlabel("Tiempo t")
plt.ylabel("x(t)")
plt.legend()
plt.grid(True)
plt.savefig("solucion_euler.png")
print("Gráfica 1 guardada como solucion_euler.png")

# 2. Gráfica del error
plt.figure(2)
plt.plot(t, error, color="green")
plt.title("Error absoluto local |x_n - x(t_n)|")
plt.xlabel("Tiempo t")
plt.ylabel("Error")
plt.grid(True)
plt.savefig("error_local.png")
print("Gráfica 2 guardada como error_local.png")
