# Задание
"""Разработать программу, реализующей указанный алгоритм метода Гаусса без выбора 
ведущего элемента для систем линейных алгебраических уравнений *Ax = b* с 
квадратной матрицей *A* произвольного порядка *n*. В разрабатываемой 
программе предусмотреть вывод расширенной матрицы на каждом шаге преобразований 
для визуализации контроля алгоритма. С помощью разработанной программы решить 
поставленную в варианте задачу. Проверить полученный результат прямой 
подстановкой с вычислением соответствующей невязки *R = ||Ax - B||* по указанной норме""" 

# Вариант 15
"""
Для заданной матрицы *A* найти обратную матрицу *A-1* используя алгоритм Гаусса. 
Проверить результат подстановкой и вычислить соответствующую невязку *R*. 
При оценке последней использовать норму *|| * ||F*.
"""


import numpy as np

def custom_print(matrix):
    if not len(matrix):
        return 
  
    mid = len(matrix[0]) // 2
    print('-' * 80)
    for i in range(len(matrix)):
        print('|', end=' ')
        for j in range(len(matrix[0])):
            if j == mid:
                print('\t|\t', end = '\t')
            print(np.round(matrix[i][j], 1), end = '\t')
        print('|')


def gaussian_func(matr):
    A = np.hstack([matr, np.eye(len(matr))])
    if not len(A):
        return []

    ans = np.asarray([[0]] * len(A))

    print('START MATRIX')
    custom_print(A)

    print('\nFORWARD:')
    for j in range(len(A[0]) - 1):
        for i in range(j+1, len(A)):
            coeff = (-1.0) * A[i][j] / A[j][j]
            A[i] += coeff * A[j]
        print(f'\n{j+1} iter:')
        custom_print(A)

    for i in range(len(A)):
        A[i] /= A[i][i]
    
    print('\nAFTER NORMALIZE:')
    custom_print(A)

    print('\nBACKWARD:')
    for j in range(1, len(A[0]) // 2):
        for i in range(j):
            A[i] -= A[j] * A[i][j]
        print(f'\n{j} iter:')
        custom_print(A)

    return A[:, len(A[0])//2:]


def check(A, A_inv):
    total = A.dot(A_inv)
    E = np.eye(len(A))
    for i in range(len(A)):
        for j in range(len(A[0])):
            if np.fabs(E[i][j] - total[i][j]) > 1e-6:
                return False
    return True


def F_norm(A):
    if not len(A):
        return 0
    
    ans = 0
    for i in range(len(A)):
        for j in range(len(A[0])):
            ans += A[i][j] * A[i][j]
    return np.sqrt(ans)


def main():
    A = [
     [13,  -23, 17,  -11, 12,  13, -6],
     [-9,  -1,  -5,  6,   -11, -3, 3 ],
     [-15, 10,  -10, -1,  -9,  0,  1 ],
     [5,   -12, 6,   -7,  4,   8,  -3],
     [4,   8,   2,   8,   2,   -8, 2 ],
     [1,   -10, 1,   -7,  1,   7,  -2],
     [0,   -6,  0,   -4,  0,   4,  -1]
    ]
    A = np.asarray(A, dtype='float64')
    A_inv = gaussian_func(A)
    print(check(A_inv, A))

    R = A.dot(A_inv) - np.eye(len(A))
    print(F_norm(R))



if __name__ == "__main__":
    main()
