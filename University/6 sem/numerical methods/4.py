# Задание
"""
Для функции *f(x)* найти с максимально возможной точностью любой один и тот же вещественный 
корень _x*_ нелинейного уравнения *f(x) = 0*, используя метод бисекции и метод, указанный в 
варианте. На графике функции указать местоположение найденного корня (Окно 1). Построить 
для обоих методов графики знчения приближённых корней *x_n* (Окно 2) и в логарифмической 
шкале график зависимости модуля абсолютной ошибки *eps_n = |x_n -* _x*|_ и модуля невязки 
*R_n = f(x_n)* (Окно 3) от номера шага.
"""

# Вариант 15
"""
f(x) = (1 - 3*x + x**2) / (1 + x + x**2)
"""

import numpy as np
import matplotlib.pyplot as plt


def bisection_func(f, a, b, eps):
    xs = []

    while b - a >= eps:
        mid = (a+b)/2
        
        xs.append(mid)
        if f(mid) == 0: break

        if f(a)*f(mid) < 0:
            b = mid
        else:
            a = mid
    return xs


def newton_func(f, f_deriv, x0, eps):
    xs = [x0]
    err = 1
    while err >= eps:
        x_new = xs[-1] - f(xs[-1])/f_deriv(xs[-1])
        err = np.fabs(x_new-xs[-1])
        xs.append(x_new)
    return xs


def f(x):
	return (1 - 3*x + x**2) / (1 + x + x**2)


def f_deriv(x):
    return (4 * (x**2 - 1)) / (x**2 + x + 1)**2


def main():
    x0 = 0.25
    a = -2.0
    b = 2.0
    eps=1e-16
    
    x_b = bisection_func(f, a, b, eps)
    x_n = newton_func(f, f_deriv, x0, eps)
    x_ = x_n[-1] # x*

    x = np.linspace(a, b, 10000)
    y = f(x)
    plt.plot(x, y, label='f(x)')
    plt.scatter(x_n[-1], f(x_n[-1]), label=f'Ньютон,x={x_n[-1]}', color='red', s=50)
    plt.scatter(x_b[-1], f(x_b[-1]), label=f'Бисекция,x={x_b[-1]}', color='orange')
    plt.grid(True)
    plt.legend()
    plt.show()

    plt.plot(x_b, 'o-', label='Бисекция')
    plt.plot(x_n, 'o-', label='Ньютон')
    plt.axhline(x_, color='black', label=f'x*={x_}')
    plt.grid(True)
    plt.legend()
    plt.show()

    Rs_b = np.array([f(xn) for xn in x_b])
    Rs_n = np.array([f(xn) for xn in x_n])

    err_b = np.array([np.fabs(x_ - xn) for xn in x_b])
    err_n = np.array([np.fabs(x_ - xn) for xn in x_n])

    plt.plot(range(len(err_b)), err_b, label='Бисекция ошибка')
    plt.plot(range(len(Rs_b)), np.fabs(Rs_b), label='Бисекция невязка', color='green')
    plt.plot(range(len(err_n)), err_n, label='Ньютон ошибка', color='red')
    plt.plot(range(len(Rs_n)), np.fabs(Rs_n), label='Ньютон невязка', color='orange')

    plt.yscale('log')
    plt.legend()
    plt.show()

     
if __name__ == "__main__":
     main()
