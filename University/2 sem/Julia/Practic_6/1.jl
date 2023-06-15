# Представим вектор как именованный кортеж
using LinearAlgebra

Vector2D{T<:Real} = NamedTuple{(:x, :y), Tuple{T,T}}

# Сложение векторов
Base. +(a::Vector2D{T},b::Vector2D{T}) where T = Vector2D{T}(Tuple(a) .+ Tuple(b))

# Разность векторов
Base. -(a::Vector2D{T}, b::Vector2D{T}) where T = Vector2D{T}(Tuple(a) .- Tuple(b))

# Векторное произведение векторов
Base. *(α::T, a::Vector2D{T}) where T = Vector2D{T}(α.*Tuple(a))

# Длина вектора
LinearAlgebra.norm(a::Vector2D) = norm(Tuple(a))

# Скалярное произведение векторов (a,b)=|a||b|cos(a,b)
LinearAlgebra.dot(a::Vector2D{T}, b::Vector2D{T}) where T = dot(Tuple(a), Tuple(b))

# Косое произведение    (a,b)=|a||b|sin(a,b)
xdot(a::Vector2D{T}, b::Vector2D{T}) where T = a.x*b.y-a.y*b.x

# Синус угла между векторами
Base.sin(a::Vector2D{T}, b::Vector2D{T}) where T = xdot(a,b)/norm(a)/norm(b)

# Косинус угла между векторами
Base. cos(a::Vector2D{T}, b::Vector2D{T}) where T = dot(a,b)/norm(a)/norm(b)

# Угол между векторами
Base.angle(a::Vector2D{T}, b::Vector2D{T}) where T = atan(sin(a,b),cos(a,b))

# Знак угла
Base.sign(a::Vector2D{T}, b::Vector2D{T}) where T = sign(sin(a,b))

# Отрезок 
Segment2D{T<:Real} = NamedTuple{(:A, :B), NTuple{2,Vector2D{T}}}