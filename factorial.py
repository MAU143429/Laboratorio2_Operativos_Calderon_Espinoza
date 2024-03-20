import time

def factorial(n):
    # Factorial de 0
    if n == 0:
        return 1

    # Factorial de n-1.
    else:
        print("Calculando el factorial de:", n)
        return n * factorial(n-1)

def cpu_intensive_task():
    # Realiza una tarea intensiva en CPU
    for _ in range(600000000):  # Aumenta el número de iteraciones para prolongar la ejecución
        pass

numero = 900
inicio = time.time()

# Realiza la tarea intensiva en CPU
cpu_intensive_task()

resultado = factorial(numero)
fin = time.time()

print(f"El factorial de {numero} es {resultado}")
print(f"Tiempo de ejecución: {fin - inicio} segundos")
