# Ранг прямоугольной матрицы
using LinearAlgebra
function rang(A)
    gaussian_elimination!(copy(A))

    # Вычисляем ранг матрицы A как количество ненулевых строк
    count = 0; i = 1
       # check = zeros(t, 0)
        while A[i, i] != 0.0
            count = count + 1
            i += 1
        end
    return count
end


A = [1.0 2.0 4.0 2.0; 3.0 5.0 2.0 11.0; 2.0 6.0 7.0 9.0]

println(gaussian_elimination(A))