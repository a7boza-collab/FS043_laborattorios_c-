import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

# --------------------------
# parametros del problema
# --------------------------
Lx = 1.0       # tamaño del eje x
Ly = 1.0       # tamaño del eje y
Nx = 50        # cantidad de puntos en x
Ny = 50        # cantidad de puntos en y
kappa = 1.0    # este capa es diferente paracada material es como se calienta el material 
h = Lx / Nx    # distancia entre cada punto
r = 0.2        # numero que nos dieron para que funcione bien dijo el profesor que fuera menor a un cuarto
t_final = 0.1  # tiempo donde vamos a calcular
snapshot_interval = 20  # guardar resultado cada 20 imagenes para qse haga la animacion

# TODO: calcular dt num_steps
# --------------------------
dt = r * h * h / kappa   # paso de tiempo
num_steps = int(t_final / dt) # cuantos pasos hay que hacer

# por si queda los pasos por dt es menor que el timpo final se suma un paso para que no termine antes
if num_steps * dt < t_final:
    num_steps = num_steps + 1

# --------------------------
# Condicion inicial
# --------------------------
u = np.zeros((Nx + 1, Ny + 1))

# --------------------------
# condiciones de frontera
# lo hice punto por punto con bucles, sin atajos
# --------------------------
def aplicar_frontera(u):

    # borde izquierdo: x=0, todos elborde vale 10
    for j in range(Ny + 1):
        u[0, j] = 10.0

    # borde derecho: x=1, todo el borde vale  10
    for j in range(Ny + 1):
        u[Nx, j] = 10.0

    # borde de abajo: y=0, todos valen 5
    for i in range(Nx + 1):
        u[i, 0] = 5.0

    # borde de arriba: y=1, todos valen 5
    for i in range(Nx + 1):
        u[i, Ny] = 5.0

aplicar_frontera(u)

# --------------------------
# Evolucion temporal
# --------------------------
snapshots = []
tiempos = []

u_new = np.copy(u)

for n in range(num_steps + 1):

    # cuando el resto es cero guarda o sea 20/20
    if n %  snapshot_interval == 0:
        snapshots.append(u.copy())#.copy lo guarda profundo
        tiempos.append(n * dt)

    # calculo la temperatura en los puntos de adentro
    # no toco los bordes porque ya los puse antes
    for i in range(1, Nx):
        for j in range(1, Ny):
            # uso la formula que nos dieron en clase
            u_new[i,j] = u[i,j] + r * (
                u[i+1,j] +
                u[i-1,j] +
                u[i,j+1] +
                u[i,j-1] -
                4 * u[i,j]
            )

    # vuelvo a poner las fronteras por si se cambiaron al calcular
    aplicar_frontera(u_new)

    # paso los valores nuevos para el siguiente paso
    for i in range(Nx + 1):
        for j in range(Ny + 1):
            u[i,j] = u_new[i,j]

# --------------------------
# Animacion
# --------------------------
fig, ax = plt.subplots(figsize=(6,5))

im = ax.imshow(
    snapshots[0].T,
    origin="lower",
    extent=[0, Lx, 0, Ly],
    cmap="hot",
    vmin=0,
    vmax=np.max(snapshots[0])
)

cbar = plt.colorbar(im, ax=ax)
cbar.set_label("Temperatura")

ax.set_xlabel("x")
ax.set_ylabel("y")
ax.set_title("Ecuacion de calor 2D")
time_text = ax.text(0.02, 0.95, "t = 0.0", color="white")

time_text = ax.text(
    0.02,
    0.95,
    "",
    transform=ax.transAxes,
    color="white",
    fontsize=11,
    verticalalignment="top"
)
def actualizar(frame):
    im.set_data(snapshots[frame].T)
    time_text.set_text(f"t = {tiempos[frame]:.4f}")
    return im, time_text


anim = FuncAnimation(
    fig,
    actualizar,
    frames=len(snapshots),
    interval=80,
    blit=True
)

anim.save("calor_2d.gif", writer="pillow", fps=15)

plt.show()

print("=== Simulación de calor 2D ===")
print(f"Paso de tiempo dt = {dt:.6f}")
print(f"Número total de pasos = {num_steps}")
print("Ejecución finalizada correctamente")
print("Archivo generado: calor_2d.gif")
