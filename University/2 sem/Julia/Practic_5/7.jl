# Эффективная сортировка O(n)
function calc_sort!(array::AbstractVector{T})::AbstractVector{T} where T <: Number
    min_val, max_val = extrema(array)
    num_val = zeros(T, max_val - min_val + 1) # - число всех возможных значений

    for val in array
        num_val[val-min_val+1] += 1
    end  
    k = 0

    for (i, num) in enumerate(num_val)
        array[k+1:k+num] .= min_val+i-1
        k += num
    end

    return array
end

calc_sort(array::AbstractVector)::AbstractVector = calc_sort!(copy(array))

# Порядковые статистики, алгоритм быстрого вычисления порядковых статистик
function order_statistics!(array::AbstractVector{T}, index::Integer)::T where T
	function part_sort!(indexes_range::AbstractUnitRange, b)
		K, L, M = indexes_range[1]-1, indexes_range[begin]-1, indexes_range[end] # 0, 0, N
		#ИНВАРИАНТ: array[indexes_range[begin]:K] < b && array[K+1:L] == b && array[M+1:indexes_range[end]] > b
		while L < M 
			if array[L+1] == b
				L += 1
			elseif array[L+1] > b
				array[L+1], array[M] = array[M], array[L+1]
				M -= 1
			else # if array[L+1] < b
				L += 1; K += 1
				array[L], array[K] = array[K], array[L]
			end
		end    
		return indexes_range[begin]:K, M+1:indexes_range[end] 
		# - эти диапазоны индексов определяют ещё не отсортированные части массива array
	end

	function find(indexes_range)
		left_range, right_range = part_sort!(indexes_range, array[rand(indexes_range)]) 
		# - здесь "базовый" элемент массива выбирается случайным образом
		if index in left_range
			return find(left_range) 
		elseif index in right_range
			return find(right_range)
		else
			return array[index]
		end
	end

	find(firstindex(array):lastindex(array))
end

order_statistics(array::AbstractVector, index::Integer) = order_statistics!(copy(array), index)

# Реализация кучи на базе массива O(n)
function heap!(array::AbstractVector{T})::AbstractVector{T} where T <: Number
    N = length(array)

    for i in 1:N÷2
        if array[i] < array[2i]
            array[i], array[2i] = array[2i], array[i]
        end
        
        if 2i+1 <= N && array[i] < array[2i+1]
            array[i], array[2i+1] = array[2i+1], array[i]
        end
    end

    return array
end

heap(array::AbstractVector)::AbstractVector = heap!(copy(array))