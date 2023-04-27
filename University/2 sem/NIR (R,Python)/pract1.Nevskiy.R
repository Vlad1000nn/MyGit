library("lmtest")

data = swiss

data
summary(data)

#Считаем Среднее значение для Education
sum(data$Education)
data$Education
sum(data$Education)/47

#Дисперсия для Education
var(data$Education)

#СКО для Education
sd(data$Education)


#Считаем Среднее значение для Fertility
mean(data$Fertility)

#Дисперсия для Fertility
var(data$Fertility)

#СКО для Fertility
sd(data$Fertility)

#Считаем Среднее значение для Examination
mean(data$Examination)

#Дисперсию для Examination
var(data$Examination)

#СКО для Examination
sd(data$Examination)



#Зависимость y=a+bx,  y=Education, x=Fertility
model=lm(Education~Fertility,data)
model
summary(model)


#Зависимость y=a+bx,  y=Education, x=Examination
model2=lm(Education~Examination,data)
model2
summary(model2)