#!/usr/bin/env python3
import time

def compute(x):
    return x*x - x*x + x*4 - x*5 + x + x

def main():
    while True:
        try:
            n = int(input("Введите количество итераций (или не число для выхода): "))
            if n <= 0:
                print("Число должно быть положительным. Попробуйте снова.")
                continue

            x = 2.0
            start = time.time()

            for _ in range(n):
                compute(x)

            end = time.time()
            duration = (end - start) * 1_000_000

            print(f"Выполнено {n} итераций за {duration:.0f} микросекунд")
            print(f"Среднее время на итерацию: {duration / n:.4f} мкс")

        except ValueError:
            print("Введено не число. Завершение программы.")
            break

if __name__ == "__main__":
    main()
