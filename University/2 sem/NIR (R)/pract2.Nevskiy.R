library("lmtest")
library("GGally")

data = swiss

data
summary(data)
ggpairs(data)
                              #1
#проверим на линейную независимость регрессоры

model_test1=lm(Fertility~Agriculture+Catholic,data)
summary(model_test1)

model_test2=lm(Agriculture~Fertility+Catholic,data)
summary(model_test2)

model_test3=lm(Catholic~Agriculture+Fertility,data)
summary(model_test3)

                              #2
#Построим нашу модель
model1=lm(Examination~Agriculture+Catholic+Fertility,data)
summary(model1)
                              #3
#Добавим в нашу модель логарифмы регрессоров

model_log1=lm(Examination~Agriculture+Catholic+Fertility+I(log(Fertility)),data)
summary(model_log1)


model_log2=lm(Examination~Agriculture+Catholic+Fertility+I(log(Catholic)),data)
summary(model_log2)

model_log3=lm(Examination~Agriculture+Catholic+Fertility+I(log(Agriculture)),data)
summary(model_log3)

                              #4
#Добавим в нашу модель всевозможные произведения, а также квадраты регрессоров

model_cmp1=lm(Examination~Agriculture+Catholic+Fertility+I(Agriculture*Catholic),data)
summary(model_cmp1)

model_cmp2=lm(Examination~Agriculture+Catholic+Fertility+I(Agriculture*Fertility),data)
summary(model_cmp2)

model_cmp3=lm(Examination~Agriculture+Catholic+Fertility+I(Fertility*Catholic),data)
summary(model_cmp3)

model_sq1=lm(Examination~Agriculture+Catholic+Fertility+I(Agriculture^2),data)
summary(model_sq1)

model_sq2=lm(Examination~Agriculture+Catholic+Fertility+I(Catholic^2),data)
summary(model_sq2)

model_sq3=lm(Examination~Agriculture+Catholic+Fertility+I(Fertility^2),data)
summary(model_sq3)


                                    #2.2
# 1)

#Критерий Стьюдента
t_critical = qt(0.975, df = 43)
t_critical #t=2.017

#доверительные интервалы:
#[B-t*СКО, B+t*СКО]

#свободный
#B=43.68, СКО=4.11  
#[43.68-4.11*2.017,43.68+4.11*2.017 ]
#[35.39,51.97]

#Agriculture
#B=-0.16, СКО=0.33
#[-0.16-0.33*2.017,-0.16+0.33*2.017]
#[-0.83,0.56]

#Catholic
#B=-0.39, СКО=0.19
#[-0.39-0.19*2.017,-0.39+0.19*2.017]
#[-0.77,-0.01]

#Fertility
#B=-0.25, СКО=0.06
#[-0.25-0.06*2.017,-0.25+0.06*2.017]
#[-0.37,-0.13]


# 2)
#B нулём быть не может,т.к 0 не попадает в интервал 
#Fertility, Catholic, Свободный
#B может быть нулём,т.к 0  попадает в интервал Agriculture
#Это означает, что регрессор практически не связан с объясняемой переменной.

# 3)
new.data = data.frame(Catholic = 84.32, Agriculture=45.1, Fertility=83.1)
predict(model1, new.data, interval = "confidence")

#43.68-0.16*45.1-0.039*84.32-0.24*83.1
#   13.23152
