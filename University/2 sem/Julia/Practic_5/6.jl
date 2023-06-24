# Медиана на основе Хоара
function median(array::AbstractVector{T})::T where T <: Number
	quick_sort!(array)

    if len(array) % 2 == 1
        return array[len(array) / 2]
    else
        return 0.5 * (array[len(array) / 2 - 1] + l[len(array) / 2])
	end
end