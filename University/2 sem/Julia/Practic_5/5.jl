function part_sort!(A, b)
    N = length(A)
    K=0
    L=0
    M=N
    #ИНВАРИАНТ: A[1:K] < b && A[K+1:L] == b && A[M+1:N] > b
    while L < M 
        if A[L+1] == b
            L += 1
        elseif A[L+1] > b
            A[L+1], A[M] = A[M], A[L+1]
            M -= 1
        else # if A[L+1] < b
            L += 1; K += 1
            A[L], A[K] = A[K], A[L]
        end
    end
    return K, M+1 
    # 1:K и M+1:N - эти диапазоны индексов определяют ещё не 
    # отсортированные части массива A
end

function quick_sort!(A)
    if isempty(A)
        return A
    end
    N = length(A)
    K, M = part_sort!(A, A[rand(1:N)]) # - "базовый" элемент массива выбирается случайнам образом
    quick_sort!(@view A[1:K])
    quick_sort!(@view A[M:N])
    return A
end