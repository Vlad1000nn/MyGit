import numpy as np
import matplotlib.pyplot as plt
import scipy
import pandas as pd
import math


# Функция построения статистического ряда
def build_stat_series(data):
    x_i = list(set(data))
    x_i.sort()
    n_i = [0] * len(x_i)

    for x in data:
        n_i[x_i.index(x)] += 1

    w_i = [n / len(data) for n in n_i]
    s_i = [sum(w_i[0:i + 1]) for i in range(len(w_i))]
    stat_series = pd.DataFrame({'Значение': x_i, 'Количество': n_i, 'Относительная частота': w_i, 's': s_i})
    print(stat_series)


# Функция построения полигона относительнх частот и полигона теоретических вероятностей
def freq_polygons(data, t_weights, t_vals):
    fig = plt.figure()

    x_i = list(set(data))
    x_i.sort()
    n_i = [0] * len(x_i)

    for x in data:
        n_i[x_i.index(x)] += 1

    vals = [x_i[0]]
    cnts = [n_i[0]]

    for i in range(1, len(n_i)):
        if x_i[i] != x_i[i - 1] + 1:
            for val in range(x_i[i - 1] + 1, x_i[i]):
                vals.append(val)
                cnts.append(0)

        vals.append(x_i[i])
        cnts.append(n_i[i])

    x_i = vals
    n_i = cnts

    for i in range(len(n_i) - 1):
        plt.plot([x_i[i], x_i[i + 1]], [n_i[i] / len(data), n_i[i + 1] / N], color='blue')

    for i in range(len(t_weights) - 1):
        plt.plot([t_vals[i], t_vals[i + 1]], [t_weights[i], t_weights[i + 1]], color='red')

    plt.show()


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


# Функция подсчёта выборочных статистик
def calc_sample_statistics(data):
    x_i = list(set(data))
    x_i.sort()
    n_i = [0] * len(x_i)

    for x in data:
        n_i[x_i.index(x)] += 1

    w_i = [n / len(data) for n in n_i]

    mean_val = data.mean()

    var_val = data.var()
    sqd_val = math.sqrt(var_val)

    max_n = max(n_i)

    max_freq_items = []
    for i in range(len(x_i)):
        if n_i[i] == max_n:
            max_freq_items.append(x_i[i])

    mode_val = sum(max_freq_items) / len(max_freq_items)
    median_val = np.median(data)
    asym_val = scipy.stats.skew(data)
    kurtosis_val = scipy.stats.kurtosis(data)

    print(f'Выборочное среднее: {mean_val}')
    print(f'Выборочная дисперсия: {var_val}')
    print(f'Выборочное среднее квадратическое отклонение: {sqd_val}')
    print(f'Выборочная мода: {mode_val}')
    print(f'Выборочная медиана: {median_val}')
    print(f'Выборочный коэффициент асимметрии: {asym_val}')
    print(f'Выборочный коэффициент эксцесса: {kurtosis_val}')
    return [mean_val, var_val, sqd_val, mode_val, median_val, asym_val, kurtosis_val]


# Функция построения таблицы сравнения относительных частот и теоретических вероятностей
def geom_build_compare_table(data):
    x_i = list(set(data))
    x_i.sort()
    n_i = [0] * len(x_i)

    for x in data:
        n_i[x_i.index(x)] += 1

    w_i = [n / len(data) for n in n_i]
    s_i = [sum(w_i[0:i + 1]) for i in range(len(w_i))]

    theoretical_weights = [p * (1 - p) ** (i - 1) for i in x_i]
    diff_w = []
    for i in range(len(w_i)):
        diff_w.append(np.fabs(w_i[i] - theoretical_weights[i]))

    compare_table = pd.DataFrame(
        {'Значение': x_i, 'Относительная частота': w_i, 'Теоретическая частота': theoretical_weights, 'diff': diff_w})
    print(compare_table)


# Функция построения таблицы сравнения посчитанных характеристик с теоретическими значениями
def geom_build_compare_stats(data, sample_statistics, p):
    expected_values = np.arange(data[0], data[-1] + 1)
    expected_weights = [p * (1 - p) ** (i - 1) for i in expected_values]

    expected_mean = sum(x * w for x, w in zip(expected_values, expected_weights))
    expected_var = (1 - p) / p ** 2
    expected_sqd = np.sqrt(expected_var)

    expected_mode = 0.0
    expected_median = np.median(expected_values)
    expected_asym = (2 - p) / (np.sqrt(1 - p))
    expected_kurtosis = 6 + (p ** 2) / (1 - p)

    expected_values = [expected_mean, expected_var, expected_sqd, expected_mode, expected_median, expected_asym,
                       expected_kurtosis]
    rows = ['Среднее', 'Дисперсия', 'Среднее квадратическое отклонение', 'Мода', 'Медиана', 'Коэффициент асимметрии',
            'Коэффициент эксцесса']
    compare_table = pd.DataFrame({'Параметр': rows, 'Теоретическое': expected_values, 'Выборочное': sample_statistics})
    print(compare_table)


# Основная функция выполнения программы
if __name__ == "__main__":
    V = 178
    p = 0.2 + 0.003 * V
    N = 200
    random_state = 178
    generator = np.random.default_rng(random_state)

    geom_data = generator.geometric(p, N)

    print("ИСХОДНАЯ ВЫБОРКА:\n", geom_data)

    geom_sorted_data = geom_data
    geom_sorted_data.sort()
    print("\nОТСОРТИРОВАННАЯ ВЫБОРКА:\n", geom_sorted_data)

    print("Чёто 1")
    build_stat_series(geom_data)

    geom_theoretical_vals = range(geom_sorted_data[0], geom_sorted_data[-1] + 1)
    geom_theoretical_weights = [p * (1 - p) ** (i - 1) for i in geom_theoretical_vals]

    freq_polygons(geom_data, geom_theoretical_weights, geom_theoretical_vals)

    empirical_distribution_function(geom_data)

    print("\nВЫБОРОЧНЫЕ СТАТИСТИКИ:")
    geom_sample_statistics = calc_sample_statistics(geom_data)

    print("\nТАБЛИЦА СРАВНЕНИЯ ОТНОСИТЕЛЬНЫХ ЧАСТОТ И ТЕОРЕТИЧЕСКИХ ВЕРОЯТНОСТЕЙ:")
    geom_build_compare_table(geom_data)

    print("\nТАБЛИЦА СРАВНЕНИЯ ПОСЧИТАННЫХ ХАРАКТЕРИСТИК С ТЕОРЕТИЧЕСКИМИ ЗНАЧЕНИЯМИ:")
    geom_build_compare_stats(geom_sorted_data, geom_sample_statistics, p)
