import numpy as np
import pandas as pd
import scipy
import matplotlib.pyplot as plt

# Функция построения интервального ряда
def interval_ranges(data, m, a0, am, h):

    n_i = [0] * m
    for val in data[:-1]:
        n_i[int((val - a0) / h)] += 1
    n_i[m - 1] += 1

    prev = a0
    curr = prev + h
    rngs = []
    while curr <= am:
        rngs.append((prev, curr))
        curr += h
        prev += h

    w_i = [n_i[i] / len(data) for i in range(len(n_i))]
    x_i = [(rngs[i][1] + rngs[i][0]) / 2 for i in range(len(rngs))]
    ranges = [(format(a[0], '.6f'), format(a[1], '.6f')) for a in rngs]

    ranges_table = pd.DataFrame({'Интервалы': ranges, 'n_i': n_i, 'w_i': w_i})
    return ranges_table, rngs

# Функция распределения стандартного нормального закона
def F(x):
    return scipy.stats.norm.cdf(x)

# Функция плотности стандартного нормального распределения
def f0(x):
    return np.exp(-x**2 / 2) / np.sqrt(2 * np.pi)

# Функция построения таблицы pk*
def build_k_table(m, ranges, a, sigma):
    k = range(m + 1)
    t2 = [(ranges[i] - a) / sigma for i in k]
    t3 = [ f0(t2[i]) / sigma for i in k]
    t4 = [F(t2[i]) for i in k]
    pk = [0, t4[1]]
    for i in range(2, m):
        pk.append(t4[i] - t4[i-1])
    pk.append(1 - t4[m-1])
    k_table = pd.DataFrame({'k' : k, 'ak' : ranges, 'ak-a/o' : t2, 'f0(ak-a/o)/o' : t3, 'F(ak-a/o)' : t4, 'pk*' : pk})
    return k_table

# Функция плотности нормального распределения с параметрами a, sigma^2
def norm_func(x, a, sigma):
    return np.exp(-(x - a)**2 / (2*sigma**2)) / (sigma * np.sqrt(2 * np.pi))

# Функция построения гистограммы относительных частот и графиком плотности распределения
def relative_freq_histogram(data, f, a, sigma, h, m):
    fig = plt.figure()
    ax = fig.add_subplot()

    ax.hist(data, weights=np.array(np.zeros(len(data), dtype=float)) + 1 / (len(data) * h), bins=m, color='blue')

    x = np.linspace(data[0], data[-1])
    plt.plot(x, f(x, a, sigma), color='red')

    plt.show()

# Функция построения таблицы выборочного значения хи-квадрат
def build_hi_square(ranges, w_i, pk, m, N):
    k = range(1, m + 1)
    t4 = [np.fabs(w_i[i - 1] - pk[i]) for i in k]
    t5 = [N * (w_i[i - 1] - pk[i])**2 / pk[i] for i in k]
    print(f'Выборочный хи-квадрат:{sum(t5)}\n')
    pk = list(pk)
    pk.remove(0)
    hi_table = pd.DataFrame({'k' : k, 'Интервал' : ranges, 'wk' : w_i, 'pk*' : pk, '|wk - pk*|' : t4, 'N(wk-pk*)**2 / pk*' : t5})
    return hi_table

# Основная функция выполнения программы
if __name__ == "__main__":
    data = [5.18569, 3.87510, 3.22406, 4.07068, 3.67417, 1.42622, 3.33290, 5.58882, 2.92123, 3.69322,
            4.96743, 3.36244, 1.17908, 4.10015, 3.52186, 2.38884, 2.20522, 3.15971, 4.78176, 5.18924,
            1.91070, 1.42494, 1.83840, 4.25081, 3.98520, 0.61667, 0.99633, 3.66366, 5.66687, 2.19977,
            1.44281, 3.77770, -0.68600, 0.09464, 1.37114, 2.26400, 2.12304, 0.91850, 4.61751, 3.56578,
            3.73802, 4.32679, 1.32189, 1.56683, 3.95162, 3.23995, 4.03786, 1.14857, 3.35556, 4.05651,
            2.36160, 3.47860, 2.55834, 3.32872, 2.55342, 2.30530, 3.92781, 5.82680, 1.90250, 2.87836,
            5.41466, 2.13096, 4.54484, 4.47597, 2.98756, 3.91276, 1.87034, 2.68230, 4.64940, 2.03562,
            2.78722, 3.35098, 1.11154, 1.59409, 3.59500, 1.04514, 0.40305, 2.76863, 5.18837, 3.06788,
            -0.70223, 2.76158, 3.02474, 1.99849, 0.96701, 4.53338, -1.71660, 4.28000, 6.63833, 3.43934,
            2.66938, 2.05885, 3.07401, 5.21277, 2.42981, 2.70692, 1.24138, 3.17940, 2.36714, 5.22346,
            1.61203, 2.11504, 3.28459, 4.64384, 3.81723, 2.09211, 7.59684, 2.80051, 4.09919, 1.62021,
            2.46792, 4.09613, 2.46387, 0.82375, 6.13474, 2.21914, 4.90984, 2.00996, 1.91707, 2.51177,
            -0.39446, 0.73703, 1.43865, 1.63371, 2.49444, 4.60525, 2.90778, 4.15229, 4.74038, 3.78519,
            3.28195, 0.70870, 2.81538, 0.93748, 1.06712, 2.06201, 0.11105, 2.55934, 1.75501, 3.06350,
            3.84392, 3.97340, 6.86982, 3.69105, 2.30748, 0.50439, 5.17263, 4.74325, 3.40691, 0.18613,
            3.24374, 3.73896, 2.40291, 3.75200, 2.68528, 0.44800, 2.65811, 1.65668, 3.60498, 4.14376,
            1.89048, 1.70707, 0.83723, 4.81661, 2.85908, 4.11236, 0.98065, 3.34370, 3.03430, -0.17072,
            3.50780, 2.65607, 4.60909, 3.99254, 0.60295, 3.19414, 2.90956, 2.29063, 1.95263, 4.39419,
            3.11309, 6.24869, 3.41536, 4.00939, 2.13064, 2.32004, 3.86917, -1.82851, 1.92968, 2.99204,
            4.94269, -1.63926, 0.70627, 2.69859, 2.55381, 4.86132, 1.48778, 3.15560, 2.35058, 5.10668]
    print(f'ИСХОДНАЯ ВЫБОРКА:\n{data}\n')

    sorted_data = sorted(data)
    print(f'ОТСОРТИРОВАННАЯ ВЫБОРКА:\n{sorted_data}\n')

    m = 1 + int(np.log2(len(data)))
    a0 = sorted_data[0]
    am = sorted_data[-1]
    h = (am - a0) / m

    ranges_table, rngs = interval_ranges(sorted_data, m, a0, am, h)
    print(f'ИНТЕРВАЛЬНЫЙ РЯД:\n{ranges_table}\n')

    ranges = set()
    for el in rngs:
        ranges.add(el[0])
        ranges.add(el[1])
    ranges = np.round(sorted(list(ranges)), 7)

    math_exp = np.mean(data)
    math_var = sum(y * y for y in data) / len(data) - math_exp * math_exp - h * h / 12
    math_dev = np.sqrt(math_var)

    print(f'Оценка математического ожидания: {math_exp}')
    print(f'Оценка дисперсии: {math_var}')
    print(f'Оценка среднего квадратического отклонения: {math_dev}\n')

    k_table = build_k_table(m, ranges, math_exp, math_dev)
    print(f'ТАБЛИЦА pk*:\n{k_table}\n')

    relative_freq_histogram(sorted_data, norm_func, math_exp, math_dev, h, m)

    hi_table = build_hi_square(ranges_table['Интервалы'], ranges_table['w_i'], k_table['pk*'], m, len(data))
    print(f'ТАБЛИЦА ВЫБОРОЧНОГО ЗНАЧЕНИЯ хи-квадрат:\n{hi_table}\n')
