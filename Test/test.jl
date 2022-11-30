function fibonacci(a::Array,n)
   if (n==0 || n==1)
    return 1
   end
   for i in 3:n
    a[i]=a[i-1]+a[i-2]
   end
   return a[n]
end

function fibonacci_recursion(n::Integer)
    if (n==1 || n==2)
        return 1
    end
    return fibonacci_recursion(n-1) + fibonacci_recursion(n-2)
end



function main1(n::Int)
a=Array{Int}(undef,n+1)
a[1]=a[2]=1
fibonacci(a,n)
end

function main2(n::Int)
    fibonacci_recursion(n)
end