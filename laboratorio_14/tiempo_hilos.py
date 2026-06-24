# Para hacer la gráfica
import matplotlib.pyplot as plt

# Los datos que saqué
hilos = [1, 2, 4, 8]
tiempos = [26.5459, 13.6326, 12.3768, 15.1694]

# Hago la línea con puntitos
plt.plot(hilos, tiempos, 'o-', color='blue')

# Pongo los números encima de cada punto
for h, t in zip(hilos, tiempos):
    plt.text(h, t + 0.5, f'{t:.2f}', ha='center')

# Lo básico
plt.title('Tiempo vs Hilos')
plt.xlabel('Número de hilos')
plt.ylabel('Tiempo (segundos)')
plt.grid(True, linestyle='--')
plt.xticks(hilos)

# Guardo y muestro
plt.savefig('grafica_sola.png')
plt.show()
