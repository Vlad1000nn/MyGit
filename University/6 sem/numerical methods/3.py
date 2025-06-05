# Задание
"""
Решить систему алгебраических уравнений *Ax=b* указанным в варианте методом с точностью
*eps*. Матрицу *A* взять в виде *A = m^(-1)R - E*, где *m* - желаемый порядок системы,
а *R* и *E* - матрица, составленная из равномерно распределённых на отрезке *[-1, 1]* 
случайных чисел, и единичная матрица соответственно. Правая часть *b* в линейном 
уравнении - единичный вектор. По результатам вычислений построить графики зависимости 
значений компонент вектора приближенного решения (Окно 1) и в логарифмической шкале 
зависимости точности решения и невязки (Окно 2) от номера итерации *n*. Для анализа 
использовать указанные нормы. 
"""

# Вариант 15
"""
Метод Якоби, *inf*-норма, *eps*=10^(-8)
"""

import numpy as np
import matplotlib.pyplot as plt


def jacobi_func(A, b, eps):
    x = np.zeros_like(b)
    diag = np.diag(A)
    A_diag = np.diagflat(diag)
    A_nodiag = A - A_diag
    A_diag_inv = np.linalg.inv(A_diag)
    
    errs = []
    Rs = []
    xs = []
    
    err = 1

    while err >= eps:
        x_new = (b - np.dot(A_nodiag, x)) / diag
        err = np.linalg.norm(x_new - x, np.inf)
        R = np.linalg.norm(np.dot(A, x_new) - b, np.inf)

        Rs.append(R)
        errs.append(err)
        xs.append(x_new)

        x = x_new
        
    return np.array(xs), np.array(errs), np.array(Rs)


def main():
    m = 10
    eps = 1e-8
    random_state = 15
    generator = np.random.default_rng(random_state)
    
    R = generator.uniform(-1, 1, (m, m))
    A = (1 / m) * R - np.eye(m)
    b = np.ones(m)

    xs, errs, Rs = jacobi_func(A, b, eps)

    plt.figure(figsize=(10, 7))

    for i in range(xs.shape[1]):
        plt.plot(xs[:, i], label=f'x{i+1}')

    plt.xticks(np.arange(len(xs)), np.arange(1, len(xs) + 1))

    plt.title("Значения компонент вектора решения")
    plt.xlabel("Номер итерации")
    plt.ylabel("Значение")
    plt.legend()
    plt.show()


    plt.plot(np.log(Rs), color='blue', label='Невязка')
    plt.plot(np.log(errs), color='red', label='Точность решения')
    plt.xlabel("Номер итерации")
    plt.legend()
    plt.show()


if __name__ == "__main__":
    main()
