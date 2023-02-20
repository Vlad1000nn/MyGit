function find_marker!(robot)     #поиск маркера
    k=0
    side=Nord
    while (!ismarker(robot))
      for _i in 1:2
        along!(side,k,robot)
        side=right(side)
      end
      k+=1
    end
  end
  
  function along!(side,num_steps,robot)
    for _i in 1:num_steps
      if (!ismarker(robot))
        move!(robot,side)
      end
    end
  end
  
  
  function main!(robot)
  find_marker!(robot)
  end
  
  right(side::HorizonSide)::HorizonSide = HorizonSide(mod(Int(side)+1, 4))