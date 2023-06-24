# Сортировка Хоара
function part_sort!(A, b)
    N = length(A)
    K=0
    L=0
    M=N
    while L < M 
        if A[L+1] == b
            L += 1
        elseif A[L+1] > b
            A[L+1], A[M] = A[M], A[L+1]
            M -= 1
        else 
            L += 1; K += 1
            A[L], A[K] = A[K], A[L]
        end
    end
    return K, M+1 
end

function quick_sort!(A)
    if isempty(A)
        return A
    end
    N = length(A)
    K, M = part_sort!(A, A[rand(1:N)]) 
    quick_sort!(@view A[1:K])
    quick_sort!(@view A[M:N])
    return A
end