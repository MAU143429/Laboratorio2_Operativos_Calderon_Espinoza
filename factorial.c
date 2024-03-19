#include <stdio.h>
#include <time.h>

double factorial(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int main() {
    int numero = 110;
    
    clock_t inicio = clock();  
    
    double resultado = factorial(numero);
    
    clock_t fin = clock();  

    printf("El factorial de %d es %.0lf\n", numero, resultado);
    printf("Tiempo de ejecución: %f segundos\n", (double)(fin - inicio) / CLOCKS_PER_SEC);

    return 0;
}











