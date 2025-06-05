# Задание
"""
Разработать программу, реализующей указанный метод решения для систем линейных алгебраических 
уравнений *Ax = B* с матрицей *A* произвольного порядка *n* и решить с её помощью заданную 
систему. Для полученного решения *X* прямой подстановкой вычислить невязку *R = || AX-B ||* 
по норме, указанной в варианте. В разрабатываемой программе предусмотреть вывод 
промежуточных результатов(матриц *L* и *U* для LU-разложения, матрицы *L* или *U* для метода
Холецкого и прогоночные коэффициенты *a_i* и *b_i* для метода прогонки) для визуализации и 
контроля алгоритмов. Для вариантов с LU-разложением и методом Холецкого вычислить также 
детерминант матрицы системы *|A|*.
"""

# Вариант 15
"""
LU-разложение. Невязка по норме *|| * ||inf*.
"""

import numpy as np


def LU_func(matr):
    if not len(matr):
        return  ([], [])

    A = np.asarray(matr, dtype='float64')
    L = np.asarray([[0] * len(A[0])] * len(A), dtype='float64')
    U = L.copy()
    for i in range(len(L)):
        L[i][i] = 1
    
    for i in range(len(A)):
        for j in range(len(A[0])):
            total = sum(L[i][p]*U[p][j] for p in range(j))
            if i <= j:
                U[i][j] = A[i][j] - total
            else:
                L[i][j] = (A[i][j] - total) / U[j][j]

    return (L, U)


def solve(L, U, B):
    Z = np.linalg.solve(L, B)
    print(f'Z:\n{np.round(Z,1)}')
    X = np.linalg.solve(U, Z)
    return X


def inf_norm(matr):
    A = np.asarray(matr)
    total = 0
    for i in range(len(A)):
        curr = 0
        for j in range(len(A[0])):
            curr += A[i][j]
        total = max(total, curr)
    return total


def main():
    A = [
     [1,  3,   1,  -2, 1 ],
     [-3, -10, -1, 9,  -3],
     [3,  8,   3,  -2, 5 ],
     [-3, -6,  -5, -4, -7],
     [1,  2,   9,  1,  -2]
    ]
    B = [
        [-9,  -3 ],
        [27,  5  ],
        [-30, -18],
        [32,  30 ],
        [-6,  -4 ]
        ]
    A = np.asarray(A, dtype='float64')
    B = np.asarray(B, dtype='float64')

    L, U = LU_func(A)
    print(f'L:\n{L}')
    print(f'\nU:\n{U}')

    X = solve(L, U, B)
    print(np.round(X,1))

    R = A.dot(X) - B
    print(R)

    print(inf_norm(R))


if __name__ == "__main__":
    main()