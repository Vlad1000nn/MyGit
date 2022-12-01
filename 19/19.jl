function move_recursion!(robot,side)                #рекурсивно до упора
    if (!isborder(robot,side))
        move!(robot,side)
        move_recursion!(robot,side)
    end
end


function main!(robot,side)
move_recursion!(robot,side)
end