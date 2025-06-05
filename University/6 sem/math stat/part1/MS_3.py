import numpy as np
import matplotlib.pyplot as plt
import scipy
import pandas as pd
import math

# Функция построения графика эмпирической функции распределения
def empirical_distribution_function(data):
    x_i = list(set(data))
    x_i.sort()
    n_i = np.array([0] * len(x_i))

    for x in data:
        n_i[x_i.index(x)] += 1
    n_i = n_i.cumsum()

    for i in range(len(n_i) - 1):
        plt.plot([x_i[i], x_i[i + 1]], [n_i[i] / len(data), n_i[i] / len(data)], color='blue')

    plt.plot([x_i[-1], x_i[-1] + 1], [1, 1], color='blue')
    plt.yticks(np.arange(0, 1 + 0.05, 0.05))

    plt.show()

# Функция построения интервального ряда и ассоциированного статистического ряда
def interval_ranges(data, m):
    a_0 = 0
    a_m = data[-1]
    step = (a_m - a_0) / m
    n_i = [0] * m
    for val in data[:-1]:
        n_i[int((val - a_0) / step)] += 1
    n_i[m - 1] += 1

    prev = 0
    curr = prev + step
    rngs = []
    while curr <= a_m:
        rngs.append((prev, curr))
        curr += step
        prev += step

    w_i = [n_i[i] / len(data) for i in range(len(n_i))]
    x_i = [(rngs[i][1] + rngs[i][0]) / 2 for i in range(len(rngs))]
    ranges = [(format(a[0], '.6f'), format(a[1], '.6f')) for a in rngs]

    ranges_table = pd.DataFrame({'Интервалы': ranges, 'n_i': n_i, 'w_i': w_i})
    print(ranges_table)
    assoc_table = pd.DataFrame({'x_i*': x_i, 'n_i': n_i, 'w_i': w_i})
    return assoc_table

# Функция плотности распределения
def f(x):
    return lambda_ * np.exp(-lambda_ * x)

# Функция построения гистограммы относительных частот и графиком плотности распределения
def relative_freq_histogram(data, f, m):
    a_0 = 0.0
    a_m = data[-1]
    h = (a_m - a_0) / m

    fig = plt.figure()
    ax = fig.add_subplot()

    ax.hist(data, weights=np.array(np.zeros(len(data), dtype=float)) + 1 / (len(data) * h), bins=m, color='blue')

    x = np.linspace(data[0], data[-1])
    plt.plot(x, f(x), color='red')

    plt.show()

# Функция построения таблицы сравнения относительных частот и теоретических вероятностей
def exp_build_compare_table(data, m, f):
    a_0 = 0.0
    a_m = data[-1]
    h = (a_m - a_0) / m

    n_i = [0] * m
    for val in data[:-1]:
        n_i[int((val - a_0) / h)] += 1
    n_i[m - 1] += 1

    prev = 0
    curr = prev + h
    rngs = []
    while curr <= a_m:
        rngs.append((prev, curr))
        curr += h
        prev += h

    w_i = [n_i[i] / len(data) for i in range(len(n_i))]
    x_i = [(rngs[i][1] + rngs[i][0]) / 2 for i in range(len(rngs))]
    ranges = [(format(a[0], '.6f'), format(a[1], '.6f')) for a in rngs]

    theoretical_weights = [f(i) * h for i in x_i]

    diff_w = []
    for i in range(len(w_i)):
        diff_w.append(np.fabs(w_i[i] - theoretical_weights[i]))

    compare_table = pd.DataFrame(
        {'интервал': ranges, 'Относительная частота': w_i, 'Теоретическая частота': theoretical_weights,
         'diff': diff_w})
    print(compare_table)

# Функция подсчёта выборочных статистик
def exp_calc_sample_statistics(data, m):
    a_m = data[-1]
    a_0 = 0.0
    h = (a_m - a_0) / m

    n_i = [0] * m
    for val in data[:-1]:
        n_i[int((val - a_0) / h)] += 1
    n_i[m - 1] += 1

    rngs = []
    prev = 0
    curr = prev + h
    while curr < a_m:
        rngs.append((prev, curr))
        curr += h
        prev += h

    w_i = [n_i[i] / len(data) for i in range(len(n_i))]
    x_i = [(rngs[i][1] + rngs[i][0]) / 2 for i in range(len(rngs))]

    mean_val = sum(x * w for x, w in zip(x_i, w_i))
    var_val = sum(w * (x - mean_val) ** 2 for w, x in zip(w_i, x_i)) - h ** 2 / 12
    sqd_val = np.sqrt(var_val)

    mode_val = h * w_i[0] / (2 * w_i[0] - w_i[1])

    curr = w_i[0]
    k = 1
    while curr < 0.5:
        curr += w_i[k]
        k += 1
    k -= 1

    median_val = 0
    if curr != 0.5:
        median_val = a_0 + h * k + h / w_i[k] * (0.5 - curr + w_i[k])
    else:
        median_val = a_0 + h * (k + 1)

    central_moment_3 = sum(w * (x - mean_val) ** 3 for w, x in zip(w_i, x_i))
    central_moment_4 = sum(w * (x - mean_val) ** 4 for w, x in zip(w_i, x_i))

    asym_val = central_moment_3 / sqd_val ** 3
    kurtosis_val = central_moment_4 / sqd_val ** 4

    print(f'Выборочное среднее: {mean_val}')
    print(f'Выборочная дисперсия: {var_val}')
    print(f'Выборочное среднее квадратическое отклонение: {sqd_val}')
    print(f'Выборочная мода: {mode_val}')
    print(f'Выборочная медиана: {median_val}')
    print(f'Выборочный коэффициент асимметрии: {asym_val}')
    print(f'Выборочный коэффициент эксцесса: {kurtosis_val}')

    return [mean_val, var_val, sqd_val, mode_val, median_val, asym_val, kurtosis_val]

# Функция построения таблицы сравнения посчитанных характеристик с теоретическими значениями
def exp_build_compare_stats(data, sample_statistics, f, lambda_):
    expected_values = np.linspace(data[0], data[-1], num=len(data))
    expected_weights = [f(i) for i in expected_values]

    expected_mean = 1 / lambda_
    expected_var = 1 / lambda_ ** 2
    expected_sqd = np.sqrt(expected_var)

    expected_mode = 0.0
    expected_median = math.log(2) / lambda_
    expected_asym = 2.0
    expected_kurtosis = 6.0

    expected_values = [expected_mean, expected_var, expected_sqd, expected_mode, expected_median, expected_asym,
                       expected_kurtosis]
    rows = ['Среднее', 'Дисперсия', 'Среднее квадратическое отклонение', 'Мода', 'Медиана', 'Коэффициент асимметрии',
            'Коэффициент эксцесса']
    compare_table = pd.DataFrame({'Параметр': rows, 'Теоретическое': expected_values, 'Выборочное': sample_statistics})
    print(compare_table)

# Основная функция выполнения программы
if __name__ == "__main__":
    V = 178
    N = 200
    random_state = 178
    generator = np.random.default_rng(random_state)

    lambda_ = 1 + ((-1) ** V) * 0.003 * V

    np.set_printoptions(formatter={'float': '{:.6f}'.format})

    exp_data = generator.exponential(1 / lambda_, N)

    print("ИСХОДНАЯ ВЫБОРКА:\n", exp_data)

    exp_sorted_data = exp_data
    exp_sorted_data.sort()
    print("\nОТСОРТИРОВАННАЯ ВЫБОРКА:\n", exp_sorted_data)

    empirical_distribution_function(exp_data)

    m = 1 + int(np.log2(N))
    print("m =", m)

    print("\nИНТЕРВАЛЬНЫЙ РЯД:")
    exp_assoc_table = interval_ranges(exp_sorted_data, m)

    print("\nАССОЦИИРОВАННЫЙ СТАТИСТИЧЕСКИЙ РЯД:")
    print(exp_assoc_table)

    relative_freq_histogram(exp_data, f, m)

    print("\nТАБЛИЦА СРАВНЕНИЯ ОТНОСИТЕЛЬНЫХ ЧАСТОТ И ТЕОРЕТИЧЕСКИХ ВЕРОЯТНОСТЕЙ:")
    exp_build_compare_table(exp_sorted_data, m, f)

    print("\nВЫБОРОЧНЫЕ СТАТИСТИКИ:")
    exp_sample_statistics = exp_calc_sample_statistics(exp_sorted_data, m)\

    print("\nТАБЛИЦА СРАВНЕНИЯ ПОСЧИТАННЫХ ХАРАКТЕРИСТИК С ТЕОРЕТИЧЕСКИМИ ЗНАЧЕНИЯМИ:")
    exp_build_compare_stats(exp_sorted_data, exp_sample_statistics, f, lambda_)
