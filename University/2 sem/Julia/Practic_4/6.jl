# Гаусс решение СЛАУ
using LinearAlgebra
function gaussian_elimination(A, b)
    n = size(A, 1)      # Определяем размерность матрицы A
    println(n)
    for k = 1:n-1
        for i = k+1:n
            factor = A[i,k] / A[k,k]                # Вычисляем множитель factor
            A[i,k:end] -= factor * A[k,k:end]       # Обнуляем элементы в столбце k ниже строки k
            b[i] -= factor * b[k]                    # Обновляем вектор b
        end
    end
     # Вычисляем решение системы линейных уравнений с помощью обратного хода метода Гаусса
    x = zeros(n)
    x[n] = b[n] / A[n,n]
    for k = n-1:-1:1
        x[k] = (b[k] - dot(A[k,k+1:end], x[k+1:end])) / A[k,k]
    end
    
    return x
end


A = [1 2 4; 3 5 2; 2 6 7]
b = [3; 4; 1]

println(gaussian_elimination(A, b))