#Реализация структуры многочлен
struct Polynom{T}
    coeffs::Vector{T}

    function Polynom(coeffs::Vector{T}) where {T<:Number}
        while length(coeffs) > 1 && coeffs[end] == zero(T)
            pop!(coeffs)
        end
        return new{T}(coeffs)
    end
end

#p = Polynom([1, 2, 3])  # создание многочлена 1 + 2x + 3x^2

import Base: +, -, *, show

#Операция сложения
+(a::Polynom{T}, b::Polynom{T}) where {T<:Number} = Polynom{T}(a.coeffs + b.coeffs)

#Операция вычитания
-(a::Polynom{T}, b::Polynom{T}) where {T<:Number} = Polynom{T}(a.coeffs - b.coeffs)

#Унарный минус
-(a::Polynom{T}) where {T<:Number} = Polynom{T}(-a.coeffs)
