# Сортировка Шелла

# Сравнение с рекурсией
function compare!(arr, i, g)
    if i < 0 || g < 0 
        return;
    end
    if arr[i] > arr[g]
        arr[i], arr[g] = arr[g], arr[i]
        compare!(arr, i, 2i - g)
    end
end

function shell_sort!(arr)
    len = length(arr)   
    step = div(len, 2)          

    while step >= 1
        for i in 1:len - step       
            compare!(arr,i,i + step)
        end
        step = div(step, 2)
    end
    return arr
end

arr = [1, 1, 5, 4, 3, 2, 7, 2, 8, 9]    
print(shell_sort!(arr))