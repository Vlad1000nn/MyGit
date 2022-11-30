function recursive_chess!(robot,side,n)         #Рекурсивно шахматы с первой клетки
    if n%2==0
        putmarker!(robot)
    end
    if (!isborder(robot,side))
        move!(robot,side)
        recursive_chess!(robot,side,n+1)
    end
end


function recursive_chess_2!(robot,side,n)         #Рекурсивно шахматы со второй клетки
    if n%2==1
        putmarker!(robot)
    end
    if (!isborder(robot,side))
        move!(robot,side)
        recursive_chess_2!(robot,side,n+1)
    end
end

function main1!(robot,side,n=0)
recursive_chess!(robot,side,n)
end

function main2!(robot,side,n=0)
    recursive_chess_2!(robot,side,n)
end