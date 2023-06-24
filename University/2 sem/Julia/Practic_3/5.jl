#5 Взаимные преобразования различных способов представления деревьев
struct Node
    index :: Int
    children :: Vector{Union{Nothing,Node}}
end

function convert!( arr :: Vector, tree :: Dict{Int,Vector})
    isempty(arr) && return

    list = []

    for subarr in arr[1:end-1]
        if isempty(subarr)
            push!(list,nothing)
            continue
        end
        if typeof(subarr) <: Int
            push!(list,subarr)
            continue
        end
        push!(list,subarr[end])
        convert!(subarr,tree)
    end

    tree[arr[end]] = list

    return tree
end

function convert!(tree :: Dict{Int,Vector}; root ::  Union{Int,Nothing}) :: Union{Vector,Int}
    arr = []
    isnothing(root) && return []
    !(root in keys(tree)) && return root
    for subroot in tree[root]
        push!(arr,convert!(tree; root = subroot))
    end
    push!(arr,root)
    return arr
end

function convert!( tree :: Dict{Int,Vector}, root :: Union{Int,Nothing}) ::Union{Node,Nothing}

    isnothing(root) && return nothing
    !(root in keys(tree)) && return Node(root,[])
    node = Node(root,[])

    for sub_root in tree[root]
        push!(node.children, convert!(tree, sub_root))
    end

    return node
end

function convert!( node :: Node) :: Union{Vector,Int}
    arr = []
    length(node.children)==0 && return node.index
    for child in node.children
        if isnothing(child)
            push!(arr, [])
            continue
        end
        push!(arr,convert!(child))
    end
    push!(arr,node.index)
    return arr

end
function convert!(node :: Node, tree :: Dict{Int, Vector}) :: Union{Dict{Int,Vector},Int}
    list = []
    for child in node.children
        if isnothing(child)
            push!(list, nothing)
            continue
        end
        push!(list,child.index)
        length(child.children) != 0 && convert!(child,tree)
    end
    tree[node.index] = list
    return tree
end