"""
Compara integración de Simpson vs Monte Carlo.

I = int_0^1 ... int_0^1 prod_i sin(pi x_i) dx_1 ... dx_d
"""
import numpy as np
from scipy.integrate import simpson
import time

# Aquí se cambia el valor de d para las pruebas (ejemplo: 2, 3, 5, 10, 32)
d = 64
valor_analitico = (2.0 / np.pi)**d

print(f"--- Probando con d = {d} ---")
print(f"Analitico:{valor_analitico:.8f}")

### ---------------------------------------------------------
###MÉTODO DE MONTE CARLO
### ---------------------------------------------------------
N_mc = 10**6 
t0_mc = time.time()

# Genero puntos al azar entre 0 y 1.
puntos = np.random.uniform(0, 1, size=(N_mc, d))

# Calculo el producto de los senos de cada coordenada
# Hago sin(pi * x) y luego multiplico todas las columnas de cada fila
senos = np.sin(np.pi * puntos)
productos = np.prod(senos, axis=1)

# La integral es el promedio de esos productos (ley de grandes números)
integral_mc = np.mean(productos)

t1_mc = time.time()
error_mc = abs(integral_mc - valor_analitico)

print(
	f"Monte Carlo: {integral_mc:.8f} " 
	f"(Error: {error_mc:.8f}, Tiempo: {t1_mc - t0_mc:.4f}s)")

### ---------------------------------------------------------
### MÉTODO DE SIMPSON (Basado en el código del profe)
### ---------------------------------------------------------
N_simpson = 10 
N_total_simpson=N_simpson**d
t0_simpson = time.time()

# Se crea la cuadrícula de puntos
x_1d = np.linspace(0, 1, N_simpson)
malla = np.meshgrid(*[x_1d] * d, indexing="ij")

# Se calcula la función en toda la malla
Z = np.prod([np.sin(np.pi * m) for m in malla], axis=0)

# Se integra eje por eje usando la regla de Simpson
integral_simpson = Z
for _ in range(d):
    integral_simpson = simpson(integral_simpson, x=x_1d, axis=0)

t1_simpson = time.time()
error_simpson = abs(integral_simpson - valor_analitico)

print(
	f"Simpson:     {integral_simpson:.8f} "
 	f"(Error: {error_simpson:.8f}, Tiempo: {t1_simpson - t0_simpson:.4f}s)"
 )
