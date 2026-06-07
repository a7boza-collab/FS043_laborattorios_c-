import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import metodos_lorenz # Aqui llamamos lo de C++

# Datos
h = 0.01
t_inicio = 0.0
t_final = 40.0
x0, y0, z0 = 1.0, 1.0, 1.0

#cada método
sol_euler = metodos_lorenz.euler(h, t_inicio, t_final, x0, y0, z0)
sol_rk2  = metodos_lorenz.rk2(h, t_inicio, t_final, x0, y0, z0)
sol_rk4  = metodos_lorenz.rk4(h, t_inicio, t_final, x0, y0, z0)

# estos son arreglos para graficar
sol_euler = np.array(sol_euler)
sol_rk2  = np.array(sol_rk2)
sol_rk4  = np.array(sol_rk4)

tiempo = np.linspace(t_inicio, t_final, len(sol_euler))

#Gráficas 3D
def graficar(sol, nombre, titulo):
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')
    ax.plot(sol[:,0], sol[:,1], sol[:,2], linewidth=0.7)
    ax.set_xlabel("x")
    ax.set_ylabel("y")
    ax.set_zlabel("z")
    ax.set_title(titulo)
    plt.savefig(nombre)
    plt.close()

graficar(sol_euler, "euler.png", "Euler - Lorenz")
graficar(sol_rk2,  "rk2.png",  "RK2 - Lorenz")
graficar(sol_rk4,  "rk4.png",  "RK4 - Lorenz")

#Sensibilidad condiciones iniciales
eps = 1e-8
sol_perturbada = metodos_lorenz.rk4(h, t_inicio, t_final, x0+eps, y0, z0)
sol_perturbada = np.array(sol_perturbada)

diferencia = np.linalg.norm(sol_rk4 - sol_perturbada, axis=1)

# Gráfica de separación
plt.figure()
plt.plot(tiempo, diferencia)
plt.xlabel("Tiempo")
plt.ylabel("Separación")
plt.title("Sensibilidad inicial")
plt.grid(True)
plt.savefig("sensibilidad.png")
plt.close()

#Guardar
with open("resultados.txt", "w") as f:
    f.write(f"Separación inicial: {diferencia[0]:.6e}\n")
    f.write(f"Separación final:   {diferencia[-1]:.6e}\n")

