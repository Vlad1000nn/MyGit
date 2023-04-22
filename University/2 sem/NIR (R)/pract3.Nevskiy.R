install.packages("devtools")
devtools::install_github("https://github.com/bdemeshev/rlms")

library("memisc")
library("GGally")
library("dplyr")
library("psych")
library("lmtest")
library("sjPlot")
library("sgof")
library("ggplot2")
library("foreign")
library("car")
library("hexbin")
library("rlms")
library("devtools")
library("rstatix")
library("sandwich")
library("haven")

data <- read.csv("r12i_os26b.csv", sep=",", dec = ".", header=TRUE)
glimpse(data)

#Выборка данных для описания соц-эконом положения граждан РФ
#hh5      Пол(1-М, 2-Ж)
#hj13.2   Среднемесячная з/п за год
#h_marst  Семейное положение
#         (1-никогда не состоял в браке,
#          2-Состоит в зарег. браке,
#          3-Живут вместе, но не зарег,
#          4-Разведен и не состоит в браке,
#          5-Вдовец(вдова),
#          6-офиц. зарег, но живут не вместе)
#h_diplom Высшее образование
#         (1-Окончил 0-6 классов,
#          2-Незаконч среднее образование(7-8кл),
#          3-2+что-то ещё,
#          4-Законч. Ср.Обр,
#          5-Законч. Ср.Спец.Обр,
#          6-Законч. Высш.Обр. и выше)
#h_age    возраст
#status   Тип населённого пункта
#         (1-Обл.Центр,
#          2-Город,
#          3-Посёлок городского типа,
#          4-Село)
#hj6.2    Длительность рабочей недели
data = select(data, hh5, h_age, h_marst, h_diplom, status, hj13.2, hj6.2)
#Убираем объекты содержащие N/A
data = na.omit(data)
#Получаем представление о наших данных
glimpse(data)

#Новая база данных для нормализованных значений
data2 = select(data) 

#Сделаем Дамми-переменные по параметру Семейное Положение

#Женат?(1-Да, 0-Нет)
data2$wed1 = 0
data2$wed1[which(data$h_marst == 2)] <- 1 
data2$wed1[which(data$h_marst == 6)] <- 1


#Разведён или вдовец?(1-Да, 0-Нет)
data2$wed2 = 0
data2$wed2[which(data$h_marst == 4)] <- 1
data2$wed2[which(data$h_marst == 5)] <- 1


#Никогда не состоял в браке?(1-Да)
data2$wed3 = 0
data2$wed3[which(data$h_marst == 1)] <- 1


# Проверим, что отсутствует линейная зависимость между семейными положениями
vif(lm(data$h_marst ~ data2$wed1 + data2$wed2 + data2$wed3)) 

#Из параметра пол делаем переменную sex(1-Мужчина, 0-Женщина)
data2["sex"] = 0
data2$sex[which(data$hh5 == 1)] <- 1


#Из параметра тип населённого пункста делаем дамми-переменную city_status
#(1-Город илил Обл.Центр, 0-В противном случае)
data2$city_status = 0
data2$city_status[which(data$status == 1)] <- 1
data2$city_status[which(data$status == 2)] <- 1


#Введём параметр higher_educ Наличие полного высшего обр(1-Да, 0-Нет)
data2$higher_educ = 0
data2$higher_educ[which(data$h_diplom == 6)] <- 1


#Возраст
age = data$h_age
data2["age"] = (age - mean(age)) / sqrt(var(age))

#Нормализованное среднее число рабочих часов в неделю
working_hours = data$hj6.2
data2$working_hours = (working_hours - mean(working_hours)) / sqrt(var(working_hours))


#Нормализованная средняя зарплата
wage = data$hj13.2
data2$wage = (wage - mean(wage)) / sqrt(var(wage))


#1
#Постройте линейную регрессию зарплаты на все параметры, которые Вы выделили
#из данных мониторинга. Не забудьте оценить коэффициент вздутия дисперсии VIF.

model1_1 = lm(data = data2, wage ~ sex + age + wed1 + wed2 + 
                wed3 + higher_educ + city_status + working_hours)
vif(model1_1)
summary(model1_1)
#Multiple R-squared - 0.02044
#Adjusted R-squared - 0.01819 

#Уберём wed3, city_status С плохой p-статистикой
model1_2 = lm(data = data2, wage ~ sex  + 
                wed1 + age  + wed2 + higher_educ + working_hours)
vif(model1_2)
summary(model1_2)

#VIF всех параметров уменьшился
#Multiple R-squared - 0.02035     ~ Такой же
#Adjusted R-squared - 0.01866     Чуть лучше


#2

#Поэкспериментируйте с функциями вещественных параметров: используйте
#логарифмы, степени (хотя бы от 0.1 до 2 с шагом 0.1), произведения вещественных
#регрессоров


#####################################Логарифмы##################################

model2_1 = lm(data = data2, wage ~ sex + wed1  + age  + wed2 + 
                higher_educ + working_hours + I(log(Mod(working_hours))) + I(log(Mod(age))))
vif(model2_1)
summary(model2_1)
#VIF огромный, значимость коэффициентов низкая
#Исключим working_hours


model2_2 = lm(data = data2, wage ~ sex + wed1  + age  + wed2 + 
                higher_educ + I(log(Mod(working_hours))) + I(log(Mod(age))))
vif(model2_2)
summary(model2_2)
#Multiple R-squared - 0.02071   
#Adjusted R-squared - 0.01874  Примерно как у нашей модели 1
#Уберём Маловажный higher_educ


model2_3 = lm(data = data2, wage ~ sex + wed1  + age +
                I(log(Mod(working_hours))) + I(log(Mod(age))) )
vif(model2_3)
summary(model2_3)
#Multiple R-squared - 0.02056   
#Adjusted R-squared - 0.01915   
#Немного лучше R^2 , коэффициенты подсчитаны более точно, VIF не превышает 1.01


#####################################Степени####################################

current_pow = 0.1
model2_4 = lm(data = data2, wage ~ sex + wed1  + age  + wed2 +
                higher_educ + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_4)
summary(model2_4)
#Уберём wed2 из-за большого VIF и higher_educ как маловажный


current_pow = 0.1
model2_5 = lm(data = data2, wage ~ sex + wed1  + age  +
                I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_5)
summary(model2_5)
#Multiple R-squared - 0.02056   
#Adjusted R-squared - 0.01916 
#VIF < 1.1


current_pow = 0.2
model2_6 = lm(data = data2, wage ~ sex + wed1  + age  + 
                I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_6)
summary(model2_6)
#Multiple R-squared - 0.02056   
#Adjusted R-squared - 0.01915
#VIF < 1.1


current_pow = 0.3
model2_7 = lm(data = data2, wage ~ sex + wed1  + age  + 
                I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_7)
summary(model2_7)
#Multiple R-squared - 0.02055  
#Adjusted R-squared - 0.01914
#VIF < 1.1


current_pow = 0.4
model2_8 = lm(data = data2, wage ~ sex + wed1  + age + 
                I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_8)
summary(model2_8)
#Multiple R-squared - 0.02053  
#Adjusted R-squared - 0.01912
#VIF < 1.1


current_pow = 0.5
model2_9 = lm(data = data2, wage ~ sex + wed1  + age   + 
                I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_9)
summary(model2_9)
#Multiple R-squared - 0.02051  
#Adjusted R-squared - 0.0191 
#VIF < 1.102


current_pow = 0.6
model2_10 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_10)
summary(model2_10)
#Multiple R-squared - 0.02048  
#Adjusted R-squared - 0.01908  
#VIF < 1.105


current_pow = 0.7
model2_11 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_11)
summary(model2_11)
#Multiple R-squared - 0.02045  
#Adjusted R-squared - 0.01905   
#VIF < 1.106


current_pow = 0.8
model2_12 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_12)
summary(model2_12)
#Multiple R-squared - 0.02042  
#Adjusted R-squared - 0.01902   
#VIF < 1.108


current_pow = 0.9
model2_13 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_13)
summary(model2_13)
#Multiple R-squared - 0.0204  
#Adjusted R-squared - 0.01899    
#VIF < 1.109


current_pow = 1.1
model2_14 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_14)
summary(model2_14)
#Multiple R-squared - 0.02034  
#Adjusted R-squared - 0.01893     
#VIF < 1.111


current_pow = 1.2
model2_15 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_15)
summary(model2_15)
#Multiple R-squared - 0.02032  
#Adjusted R-squared - 0.01891     
#VIF < 1.112


current_pow = 1.3
model2_16 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_16)
summary(model2_16)
#Multiple R-squared - 0.0203  
#Adjusted R-squared - 0.01889      
#VIF < 1.113


current_pow = 1.4
model2_17 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_17)
summary(model2_17)
#Multiple R-squared - 0.02028  
#Adjusted R-squared - 0.01887       
#VIF < 1.113


current_pow = 1.5
model2_18 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_18)
summary(model2_18)
#Multiple R-squared - 0.02026  
#Adjusted R-squared - 0.01886        
#VIF < 1.114


current_pow = 1.6
model2_19 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_19)
summary(model2_19)
#Multiple R-squared - 0.02025  
#Adjusted R-squared - 0.01885        
#VIF < 1.114


current_pow = 1.7
model2_20 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_20)
summary(model2_20)
#Multiple R-squared - 0.02024  
#Adjusted R-squared - 0.01884        
#VIF < 1.114


current_pow = 1.8
model2_21 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_21)
summary(model2_21)
#Multiple R-squared - 0.02024  
#Adjusted R-squared - 0.01883        
#VIF < 1.114


current_pow = 1.9
model2_22 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_22)
summary(model2_22)
#Multiple R-squared - 0.02024  
#Adjusted R-squared - 0.01883        
#VIF < 1.114


current_pow = 2.0
model2_23 = lm(data = data2, wage ~ sex + wed1  + age   + 
                 I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_23)
summary(model2_23)
#Multiple R-squared - 0.02024  
#Adjusted R-squared - 0.01883        
#VIF < 1.114


#Заметим, что с увеличением стемени VIF немного увеличивается а R^2 падает

#####################################Произведениe###############################

model2_24 = lm(data = data2, wage ~ sex+ 
                 wed1  + age  + higher_educ + working_hours + I(working_hours * age))
vif(model2_24)
summary(model2_24)
#Multiple R-squared - 0.02044  
#Adjusted R-squared - 0.01847         
#Уберём wed2 как незначительный + с самым большим VIF


model2_25 = lm(data = data2, wage ~ sex+ 
                 wed1  + age + higher_educ + working_hours + I(working_hours * age))
vif(model2_25)
summary(model2_25)
#Multiple R-squared - 0.02037  
#Adjusted R-squared - 0.01868  


#3
#Лучшие модели

current_pow = 0.1
model2_5 = lm(data = data2, wage ~ sex + wed1  + age  +
                I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_5)
summary(model2_5)
#Multiple R-squared - 0.02056   
#Adjusted R-squared - 0.01916 


model2_3 = lm(data = data2, wage ~ sex + wed1  + age +
                I(log(Mod(working_hours))) + I(log(Mod(age))) )
vif(model2_3)
summary(model2_3)
#Multiple R-squared - 0.02056   
#Adjusted R-squared - 0.01915   


current_pow = 0.2
model2_6 = lm(data = data2, wage ~ sex + wed1  + age  + 
                I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
vif(model2_6)
summary(model2_6)
#Multiple R-squared - 0.02056   
#Adjusted R-squared - 0.01915
#VIF < 1.1



#Значения R^2 в этих моделях практически неотличаются, но в первой модели
#Значимость переменных выше => она лучшая


#4

#Согласно построенной нами модели наибольшую зарплату получают
#Неженатые молодые мужчины, работающие большее количество часов

#5

current_pow = 0.1

#Не вступавшие в брак
data3 = subset(data, wed3 == 1)
#Без высшего обр
data3 = subset(data3, higher_educ == 0)
model5_1 = lm(data = data3, wage ~ sex  + age + city_status +
                + I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
summary(model5_1)
#Согласно модели выше, большую зарплату получают те, кто много работает


#Городские жители
data3=subset(data2, city_status == 1)
#Состоящие в браке
data3=subset(data3, wed1 == 1)
model5_2 = lm(data = data3, wage ~ sex + age  +
                I(Mod(working_hours)^current_pow) + I(Mod(age)^current_pow))
summary(model5_2)
#Согласно модели выше, большую зарплату получают молодые и много работающие