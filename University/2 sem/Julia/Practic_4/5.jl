# Приведение матрицы к ступеньчатому виду
using LinearAlgebra
function gaussian_elimination(A)
    n = size(A, 1)
    # Forward elimination
    for k = 1:n-1
        for i = k+1:n
            factor = A[i,k] / A[k,k]
            A[i,k:end] -= factor * A[k,k:end]
            
        end
    end
    return A
end


A = [1 2 4 2; 3 5 2 11; 2 6 7 9]
println(gaussian_elimination(A))