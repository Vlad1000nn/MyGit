for n in 50:50:1000
	println("Матрица порядка ",n,"×",n,":")
	@time ReverseGauss_first!(randn(n,n),randn(n))
	@time ReverseGauss!(randn(n,n),randn(n))
end