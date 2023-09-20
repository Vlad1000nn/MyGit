#include <iostream>     // For std::cout
#include <vector>       // For std::vector
#include <utility>      // For std::pair

template<typename T>
class SplayNode
{
private:

    SplayNode<T>* right;
    SplayNode<T>* left;
    SplayNode<T>* parent;

    T data;

    int height;

public:

    // Basic Concstructors
    SplayNode<T>()
        : data()
        , right(nullptr)
        , left(nullptr)
        , parent(nullptr)
        , height(1)
    { }


    SplayNode<T>(const T& _data)
        : SplayNode<T>()
    {
        data = _data;
    }

    // Setters
    void setData(T& _data)
    {
        data = _data;
    }

    void setLeft(SplayNode<T>* _left)
    {
        left = _left;
    }

    void setRight(SplayNode<T>* _right)
    {
        right = _right;
    }

    void setParent(SplayNode<T>* _parent)
    {
        parent = _parent;
    }

    void setHeight(int _height)
    {
        height = _height;
    }

    // Getters
    T getData() const
    {
        return data;
    }

    int getHeight() const
    {
        return height;
    }

    SplayNode<T>* getLeft() const
    {
        return left;
    }

    SplayNode<T>* getRight() const
    {
        return right;
    }

    SplayNode<T>* getParent() const
    {
        return parent;
    }

    void print() const
    {
        std::cout << data;
    }

    ~SplayNode<T>()
    {
        delete left; delete right;
        left = right = parent = nullptr;
    }
};


// Node with hiding functionality for using it in Splay-tree
//template<typename T>
//class SplayNode : public Node<T>
//{
//private:
//    using Node<T>::getHeight;
//    using Node<T>::setHeight;
//public:
//
//    SplayNode<T>() : Node<T>()
//    { }
//
//    SplayNode<T>(const T& data) : Node<T>(data)
//    { }
//
//};


template<typename T>
class SplayTree
{
private:
    SplayNode<T>* root;
    int size;

public:

    // Basic constructors
    SplayTree<T>(int _size = 0)
        : root(nullptr)
        , size(_size)
    { }

    SplayTree<T>(const T& data)
        : root(data)
        , size(1)
    { }

    SplayTree<T>(const std::vector<T>& vec)
        : root(nullptr)
        , size(0)
    {
        for (auto& it : vec)
            insert(it);
    }


private:

    // Right rotation
    SplayNode<T>* zig(SplayNode<T>* v)
    {
        SplayNode<T>* tmp = v->getLeft();

        v->setLeft(tmp->getRight());
        tmp->setRight(v);

        if (v->getParent())
            (v == v->getParent()->getLeft() ? v->getParent()->setLeft(tmp) : v->getParent()->setRight(tmp));

        tmp->setParent((v->getParent() ? v->getParent() : nullptr));
        v->setParent(tmp);

        return tmp;
    }

    // Left rotation
    SplayNode<T>* zag(SplayNode<T>* v)
    {
        SplayNode<T>* tmp = v->getRight();

        v->setRight(tmp->getLeft());
        tmp->setLeft(v);

        if (v->getParent())
            (v == v->getParent()->getLeft() ? v->getParent()->setLeft(tmp) : v->getParent()->setRight(tmp));

        tmp->setParent((v->getParent() ? v->getParent() : nullptr));
        v->setParent(tmp);
        return tmp;
    }

public:

    // Insert element in a tree
    void insert(const T& data)
    {
        SplayNode<T>* newNode = new SplayNode<T>(data);
        if (!newNode) throw "nullptr";

        // If tree is empty
        if (!root)
        {
            root = newNode;
            size = 1;
            return;
        }

        SplayNode<T>* curr = root;

        while (true)
        {
            // If <, go left
            if (data < curr->getData())
            {
                // If no left child
                if (!curr->getLeft())
                {
                    curr->setLeft(newNode);
                    newNode->setParent(curr);
                    break;
                }
                else curr = curr->getLeft();
            }
            else        // If >, go right
            {
                // If no right child
                if (!curr->getRight())
                {
                    curr->setRight(newNode);
                    newNode->setParent(curr);
                    break;
                }
                else curr = curr->getRight();
            }
        }
        // Splay the element to the root
        splay(newNode);
        std::cout << root->getData() << " now is root\n";
        print(root, 0);
        ++size;
    }

    // Search the element in a tree
    SplayNode<T>* search(const T& data)
    {
        if (!root) return root;

        SplayNode<T>* curr = root;

        while (true)
        {
            if (data == curr->getData())
                return splay(curr);
            else if (data < curr->getData())
            {
                if (curr->getLeft())
                    curr = curr->getLeft();
                else
                    return splay(curr);
            }
            else
            {
                if (curr->getRight())
                    curr = curr->getRight();
                else
                    return splay(curr);
            }
        }
    }

    // Find maximum in a splay tree
    SplayNode<T>* findMax()
    {
        if (!root) return root;

        SplayNode<T>* curr = root;
        while (curr->getRight()) curr = curr->getRight();

        return splay(curr);
    }

    // Find minimum in a splay tree
    SplayNode<T>* findMin()
    {
        if (!root) return root;

        SplayNode<T>* curr = root;
        while (curr->getLeft()) curr = curr->getLeft();

        return splay(curr);
    }


private:

    // Splay function
    SplayNode<T>* splay(SplayNode<T>* x)
    {
        while (x->getParent())
        {
            // If no grandfather
            if (!x->getParent()->getParent())
            {
                // Zig
                if (x == x->getParent()->getLeft())
                    zig(x->getParent());
                // Zag
                else
                    zag(x->getParent());
            }
            // Zig-Zig
            else if (x == x->getParent()->getLeft() && x->getParent() == x->getParent()->getParent()->getLeft())
            {
                zig(x->getParent()->getParent());
                zig(x->getParent());
            }
            // Zag-Zag
            else if (x == x->getParent()->getRight() && x->getParent() == x->getParent()->getParent()->getRight())
            {
                zag(x->getParent()->getParent());
                zag(x->getParent());
            }
            // Zig-Zag
            else if (x == x->getParent()->getRight() && x->getParent() == x->getParent()->getParent()->getLeft())
            {
                zag(x->getParent());
                zig(x->getParent());
            }
            // Zag-Zig
            else
            {
                zig(x->getParent());
                zag(x->getParent());
            }
        }

        root = x;
        return x;
    }

public:

    SplayNode<T>* erase(const T& data)
    {
        if (!root) return root;

        search(data);
        if (root->getData() != data)
            return root;

        // P.first  -> left  subTree
        // P.second -> right subTree
        std::pair<SplayNode<T>*, SplayNode<T>*> p = split(root);

        if (p.first->getLeft())
            p.first->getLeft()->setParent(nullptr);

        --size;

        return join(p.first->getLeft(), p.second);
    }

private:

    // Split tree by 2 subTrees
    std::pair<SplayNode<T>*, SplayNode<T>*> split(SplayNode<T>& x)
    {
        SplayNode<T>* Left, Right;
        if (x->getRight())
        {
            Right = x->getRight();
            Right->getParent = nullptr;
        }
        Left = x;
        Left->getRight = x = nullptr;

        return { Left,Right };
    }

    // Join 2 subtrees in 1
    SplayNode<T>* join(SplayNode<T>* Left, SplayNode<T>* Right)
    {
        if (!Left) return Right;
        if (!Right) return Left;

        SplayNode<T>* curr = findMax(Left);

        curr->setRight(Right);
        curr->getRight().setParent(curr);

        return curr;
    }

public:

    SplayNode<T>* getRoot() const { return root; }

    int getSize() const { return size; };

    void print(SplayNode<T>* curr, bool a)
    {
        if (curr)
        {
            std::cout << curr->getData() << ' ' << a << '\n';
            print(curr->getLeft(), 0);
            print(curr->getRight(), 1);
        }
    }
};

#include <numeric>

int main()
{
    using namespace std;

    std::vector<int> vec(10);
    vec[0] = 2;
    vec[1] = 5;
    vec[2] = 7;
    vec[3] = 3;
    vec[4] = 4;
    vec[5] = 10;
    vec[6] = 1;
    vec[7] = 6;
    vec[8] = 9;
    vec[9] = 8;

    for (auto& it : vec) cout << it << ' ';
    cout << '\n';

    SplayTree<int> tree{ vec };

    tree.print(tree.getRoot(), 0);
    cout << "root is " << tree.getRoot()->getData() << '\n';

    return 0;
}