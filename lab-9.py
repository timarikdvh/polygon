import numpy as np

def longest_increasing_subsequence(arr):
    # Получаем массив разностей соседних элементов
    diff = np.diff(arr)
    # Определяем положительные значения в массиве разности
    increasing = np.where(diff > 0, 1, 0)
    # Находим границы возрастающих последовательностей
    blocks = np.diff(np.concatenate(([0], increasing, [0])))
    starts = np.where(blocks == 1)[0]
    ends = np.where(blocks == -1)[0]
    # Вычисляем длины всех возрастающих последовательностей
    lengths = ends - starts
    # Находим индекс самой длинной последовательности
    if len(lengths) == 0:  # Если нет возрастающих последовательностей
        return np.array([])
    # Находим индекс максимального эл-та в массиве length
    max_idx = np.argmax(lengths)
    # Извлекаем самую длинную последовательность
    start, end = starts[max_idx], ends[max_idx]
    return arr[start:end + 1]  # Добавляем 1 к `end`, чтобы включить последний элемент

arr = np.array([1, 3, 2, 3, 5, 4, 6, 7, 8, 1, 2, 3, 0, 1])
result = longest_increasing_subsequence(arr)
print(result)
