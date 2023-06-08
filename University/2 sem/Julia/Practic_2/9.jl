# Построение Фарктала Келли
using GLMakie
using Colors

function kelly_fractal(iterations::Int, width::Int, height::Int)
    # Инициализация изображения
    img = zeros(RGBA{Float32}, height, width)

    # Параметры фрактала
    a, b, c, d = -0.8, 0.156, -0.156, 0.8
    e, f = 0.0, 0.0

    # Цикл по пикселям изображения
    for y in 1:height
        for x in 1:width
            # Нормализация координат
            xn = 2.0 * (x / width - 0.5)
            yn = 2.0 * (y / height - 0.5)

            x0, y0 = xn, yn

            # Итерации фрактала
            for _ in 1:iterations
                x1 = a * xn + b * yn + e
                y1 = c * xn + d * yn + f
                xn, yn = x1, y1
            end

            # Определение цвета пикселя
            distance = sqrt((xn - x0)^2 + (yn - y0)^2)
            color = distance < 0.1 ? RGBA(0, 0, 0, 1) : RGBA(1, 1, 1, 1)
            img[y, x] = color
        end
    end

    return img
end

# Параметры фрактала
iterations = 1000
width, height = 800, 800

# Создание фрактала
fractal = kelly_fractal(iterations, width, height)

# Отображение фрактала
figure = Figure(resolution = (width, height))
ax = Axis(figure, aspect = DataAspect())
image!(ax, fractal)
figure