# Сортировка Шелла
function shell_sort(array)
    n = size(array, 1)
   
    gap = div(n, 2)
    while (gap > 0)
        for i in gap+1:n
            temp = array[i]
            j = i
            while (j > gap && array[j-gap] > temp )
                
                array[j] = array[j-gap]
                
                j -= gap
            end
            array[j] = temp
        end
        gap = div(gap, 2)
    end
end

array = rand(10000)
@time shell_sort(array) 