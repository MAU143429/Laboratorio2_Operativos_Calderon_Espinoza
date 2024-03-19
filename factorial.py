import time

def factorial(n):

    # Factorial de 0
    if n == 0:
        return 1

    # Factorial de n-1.
    else:
        print ("Calculando el factorial de: " + str(n))
        return n * factorial(n-1)


numero = 900
inicio = time.time()  
resultado = factorial(numero)
fin = time.time() 
print(f"El factorial de {numero} es {resultado}")
print(f"Tiempo de ejecución: {fin - inicio} segundos")
time.sleep(1)