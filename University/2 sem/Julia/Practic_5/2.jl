# Сортировка расчёской
function rascheska(arr)
    step = length(arr)
    shrink = 1.247
   while step >=1 
        for i in 1:length(arr) - step
            if arr[i] > arr[i+step]
                arr[i], arr[i+step] = arr[i+step], arr[i]
            end
        end
        step = Int(floor(step/shrink))
   end
    return arr
end

arr = [2, 1, 5, 4, 3, 2, 7, 2, 8, 9]
print(rascheska(arr))