# Medir tiempos y mostrar resultados
import matplotlib.pyplot as plt
import subprocess
import numpy as np
import os

procesos = [1, 2, 4, 8]
tiempos = []

# Borrar archivo viejo
if os.path.exists("tiempos.txt"):
    os.remove("tiempos.txt")

for p in procesos:
    print("\nProbando con " + str(p) + " procesos...")
    # Ejecutar, MOSTRAR SALIDA y medir tiempo
    res = subprocess.run(
        "time -f '%e' mpiexec --oversubscribe -n " + str(p) + " ./producto_punto_mpi",
        shell=True,
        capture_output=False,  # <-- Esto hace que SALGA EN PANTALLA
        text=True
    )
    # Ahora capturamos el tiempo aparte
    res_tiempo = subprocess.run(
        "time -f '%e' mpiexec --oversubscribe -n " + str(p) + " ./producto_punto_mpi",
        shell=True,
        capture_output=True,
        text=True
    )
    t = float(res_tiempo.stderr.strip())
    tiempos.append(t)
    # Guardar bien
    f = open("tiempos.txt", "a")
    f.write(str(p) + "," + str(t) + "\n")
    f.close()

# Gráfica
plt.figure()
plt.plot(procesos, tiempos, marker='o', color='blue', linestyle='-')
plt.title("Tiempo vs Número de Procesos")
plt.xlabel("Número de procesos")
plt.ylabel("Tiempo (segundos)")
plt.grid(True)
plt.xticks(procesos)

plt.savefig("tiempo_vs_procesos.png")
print("\n✅ ¡Listo! Resultados mostrados y gráfica guardada")
plt.show()
