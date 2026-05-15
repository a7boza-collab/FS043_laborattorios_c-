#include "integracion.h"
#include <cmath>

double trapecio_compuesto(double valores[], int n, double h) {
    double suma = 0.0;
    
    for(int i = 1; i < n; i++){
        suma = suma + 2 * valores[i];
    }
    
    suma = suma + valores[0] + valores[n];
    return (h / 2.0) * suma;
}

double simpson_compuesto(double valores[], int n, double h) {
    if(n % 2 != 0){
        return 0.0;
    }
    
    double suma = 0.0;
    
    for(int i = 0; i <= n; i++){
        if(i == 0 || i == n){
            suma = suma + valores[i];
        } else if(i % 2 == 0){
            suma = suma + 2 * valores[i];
        } else {
            suma = suma + 4 * valores[i];
        }
    }
    
    return (h / 3.0) * suma;
}
