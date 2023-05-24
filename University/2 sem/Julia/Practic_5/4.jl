# Сортировка слиянием
function merge(array, left, mid, right)
    subArrayOne = mid - left + 1;
    subArrayTwo = right - mid;

    leftArray = Array{Float64}(undef, subArrayOne)
    rightArray = Array{Float64}(undef, subArrayTwo)

    for i in 1:subArrayOne
        leftArray[i] = array[left + i-1]
    end

    for i in 1:subArrayTwo
        rightArray[i] = array[mid + i]
    end

    indexOfSubArrOne = 1
    indexOfSubArrTwo = 1
    indexOfMergeArray = left

    while (indexOfSubArrOne <= subArrayOne && indexOfSubArrTwo <= subArrayTwo)
        if (leftArray[indexOfSubArrOne] <= rightArray[indexOfSubArrTwo])
            array[indexOfMergeArray] = leftArray[indexOfSubArrOne]
            indexOfSubArrOne = indexOfSubArrOne + 1
        else
            array[indexOfMergeArray] = rightArray[indexOfSubArrTwo]
            indexOfSubArrTwo = indexOfSubArrTwo + 1
        end
        indexOfMergeArray += 1
    end

    while (indexOfSubArrOne <= subArrayOne) 
        array[indexOfMergeArray] = leftArray[indexOfSubArrOne];
        indexOfMergeArray +=1;
        indexOfSubArrOne +=1;
    end
    while (indexOfSubArrTwo <= subArrayTwo) 
        array[indexOfMergeArray] = rightArray[indexOfSubArrTwo];
        indexOfMergeArray+=1;
        indexOfSubArrTwo+=1;
    end

end

function merge_sort(array, first, last)
    if (first >= last)
        return
    end

    mid = first + div((last-first),2)

    merge_sort(array, first, mid);
    
    merge_sort(array, mid+1, last);
    
    merge(array, first, mid, last);
    
end

array = rand(10000)
n = size(array, 1)
@time merge_sort(array, 1, n)