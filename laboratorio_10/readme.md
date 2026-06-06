#laboratorio_10-poisson 1D
FS0432-Fisica computacional
##Archivos
poisson_1d_jacobi.cpp
poisson_1d_GaussSeidel.cpp
matplotlibcpp.h
imagenes png
archivos txt
##Como compilar
###Jacobi
g++ poisson_1d_Jacobi.cpp -o poisson_1d_Jacobi.x \
-I$CONDA_PREFIX/include/python3.10 \
-I$(python3 -c "import numpy; print(numpy.get_include())") \
-L$CONDA_PREFIX/lib \
-lpython3.10 \
-Wl,-rpath,$CONDA_PREFIX/lib
