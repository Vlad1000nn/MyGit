struct VectorTree
    data::Vector{Vector{Int}}
end

function treeHeight(tree::VectorTree, node::Int, h::Int)
    hi = h+1
    if(tree.data[node]!=[])
        for i in 1:length(tree.data[node])
            h = max(h, treeHeight(tree, tree.data[node][i], hi))
        end
        hi = h
    end
    return hi
end

function treeVal(tree::VectorTree)
    v = 0
    for i in 1:length(tree.data)
        v = max(v,length(tree.data[i]))
    end
    return v
end

function treeLeafes(tree::VectorTree, node::Int, l::T) where T
    if(tree.data[node]!=[])
        for i in 1:length(tree.data[node])
            treeLeafes(tree, tree.data[node][i], l)
        end
    else
        l.x+=1
    end
end

function treeNodes(tree::VectorTree, node::Int, n::T) where T
    if(tree.data[node]!=[])
        n.x+=1
        for i in 1:length(tree.data[node])
            treeNodes(tree, tree.data[node][i], n)
        end
    end
end

function treeMidHeight(tree::VectorTree, node::Int, h::Int, heights::T) where T
    h+=1
    if(tree.data[node]!=[])
        for i in 1:length(tree.data[node])
            treeMidHeight(tree, tree.data[node][i], h, heights)
        end
    else
        pushfirst!(heights.x, h)
    end
end
