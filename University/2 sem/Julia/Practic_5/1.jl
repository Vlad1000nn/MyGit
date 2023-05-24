function sort_in_place(a, reverse)
    n = size(a, 1)
    if reverse
        for i in 1:n
            for j in i:n
                if a[i] > a[j]
                    temp = a[i]
                    a[i] = a[j]
                    a[j] = temp
                end
            end
        end
    else
        for i in 1:n
            for j in i:n
                if a[i] < a[j]
                    temp = a[i]
                    a[i] = a[j]
                    a[j] = temp
                end
            end
        end
    end
end



array = rand(10)
println(array)
sort_in_place(array, false)
#sort!(array)
println(array)

function sort_index(a, reverse)
    n = size(a, 1)
    arr_index = Array{Int64}(undef, n)
    for i in 1:n
        arr_index[i] = i
    end
    if reverse
        for i in 1:n
            for j in i:n
                if a[i] > a[j]
                    temp1 = arr_index[i]
                    arr_index[i] = arr_index[j]
                    arr_index[j] = temp1
                    temp2 = a[i]
                    a[i] = a[j]
                    a[j] = temp2
                end
            end
        end
    else
        for i in 1:n
            for j in i:n
                if a[i] < a[j]
                    temp1 = arr_index[i]
                    arr_index[i] = arr_index[j]
                    arr_index[j] = temp1
                    temp2 = a[i]
                    a[i] = a[j]
                    a[j] = temp2
                end
            end
        end
    end
    return arr_index
end


arr2 = [0.297288, 0.382396, -0.597634, -0.0104452, -0.839027]
sort_in_place(array, true)
println(arr2)
println(sort_index(arr2, true))