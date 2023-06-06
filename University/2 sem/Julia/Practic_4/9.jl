# Определитель квадратной матрицы
using LinearAlgebra
function gaussian_elimination(A)
    n = size(A, 1)
    t = size(A, 2)
    println(t)
    for k = 1:n-1
        for i = k+1:n
            factor = A[i,k] / A[k,k]
            A[i,k:end] -= factor * A[k,k:end]
            
        end
    end
        # Вычисляем определитель матрицы A как произведение элементов на главной диагонали
    det = 1
    for i = 1:n
       det = det * A[i, i]
    end
    return det
end

A = [1 2 4 ; 3 5 2 ; 2 6 7]

println(gaussian_elimination(A))
println(A)