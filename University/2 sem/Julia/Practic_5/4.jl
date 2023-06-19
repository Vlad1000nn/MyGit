# Сортировка слиянием
function Base.merge!(a1, a2, a3)::Nothing 
    i1, i2, i3 = 1, 1, 1
    @inbounds while i1 <= length(a1) && i2 <= length(a2) 
        if a1[i1] < a2[i2]
            a3[i3] = a1[i1]
            i1 += 1
        else
            a3[i3] = a2[i2]
            i2 += 1
        end
        i3 += 1
    end
    @inbounds if i1 > length(a1)
        a3[i3:end] .= @view(a2[i2:end])  
    else
        a3[i3:end] .= @view(a1[i1:end])
    end
    nothing
end



function merge_sort!(a)
    b = similar(a) # - вспомогательный массив того же размера и типа, что и массив a
    N = length(a)
    n = 1 # n - текущая длина блоков
    @inbounds while n < N
        K = div(N,2n) # - число имеющихся пар блоков длины n
        for k in 0:K-1
            merge!(@view(a[(1:n).+k*2n]), @view(a[(n+1:2n).+k*2n]), @view(b[(1:2n).+k*2n]))
        end
        if N - K*2n > n # - осталось еще смержить блок длины n и более короткий остаток
            merge!(@view(a[(1:n).+K*2n]), @view(a[K*2n+n+1:end]), @view(b[K*2n+1:end]))
        elseif 0 < N - K*2n <= n # - оставшуюся короткую часть мержить не с чем
            b[K*2n+1:end] .= @view(a[K*2n+1:end])
        end
        a, b = b, a
        n *= 2
    end
    if isodd(log2(n)) # - если цикл был выполнен нечетное число раз, то b - это исходная ссылка на массив (на внешний массив), и a - это ссылка на вспомогательный массив (локальный)
        b .= a # b = copy(a) - это было бы не то же самое, т.к. при этом получилась бы ссылка на новый массив, который создает функция copy
        a = b
    end
    return a # - исходная ссылка на внешний массив (проверить, что это так, можно с помощью ===)
end