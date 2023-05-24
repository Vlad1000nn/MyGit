function quick_sort(array, low, high)
    if (low < high)
        pivot = partition(array, low, high)

        quick_sort(array, low, pivot-1)
        quick_sort(array, pivot+1, high)
    end
end

function swap(arr, i, j)
    temp = arr[i]
    arr[i] = arr[j]
    arr[j] = temp
end

function partition(array, low, high)
    pivot = array[high]

    i = low-1
    for j in low:high-1
        if (array[j] <= pivot)
            i +=1
            swap(array, i, j)
        end
    end
    swap(array, i+1, high)
    return i+1
end


array = [1,3,4,2,1,6,3,9,7,2,4,6,1,3,2,7,8,1,2,0,4,11,2]

n = size(array, 1)
quick_sort(array, 1, n)
println(array)