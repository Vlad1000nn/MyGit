#include <iostream>     // For std::cout
#include <vector>       // For std::vector
#include <string>       // For std::string
#include <utility>      // For std::pair
#include <stack>        // For std::stack

template<typename T>
class SplayNode
{
private:

    SplayNode<T>* right;
    SplayNode<T>* left;
    SplayNode<T>* parent;

    T data;

public:

    // Basic Constructors
    SplayNode<T>()
        : data()
        , right(nullptr)
        , left(nullptr)
        , parent(nullptr)
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

    // Getters
    T getData() const
    {
        return data;
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

    // Print data
    void print() const
    {
        std::cout << data;
    }

    // Destructor
    ~SplayNode<T>()
    {
        delete left; delete right;
        left = right = parent = nullptr;
    }
};



template<typename T>
class SplayTree
{
private:
    // Root of the tree
    SplayNode<T>* root;
    // Size of the tree
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
        if (tmp->getRight())
            tmp->getRight()->setParent(v);
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
        if (tmp->getLeft())
            tmp->getLeft()->setParent(v);
        tmp->setLeft(v);

        if (v->getParent())
            (v == v->getParent()->getLeft() ? v->getParent()->setLeft(tmp) : v->getParent()->setRight(tmp));

        tmp->setParent((v->getParent() ? v->getParent() : nullptr));
        v->setParent(tmp);
        return tmp;
    }

public:

    // Insert the element in a tree
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
    SplayNode<T>* findMax(SplayNode<T>* _root = nullptr)
    {
        if (!_root) _root = root;
        if (!_root) return _root;

        SplayNode<T>* curr = _root;
        while (curr->getRight()) curr = curr->getRight();
        return splay(curr);
    }

    // Find minimum in a splay tree
    SplayNode<T>* findMin(SplayNode<T>* _root = nullptr)
    {
        if (!_root) _root = root;
        if (!_root) return _root;

        SplayNode<T>* curr = _root;
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

    // Erase the element
    SplayNode<T>* erase(const T& data)
    {
        if (!root) return root;

        search(data);
        if (root->getData() != data)
            return root;

        // p.first  -> left  subTree
        // p.second -> right subTree
        std::pair<SplayNode<T>*, SplayNode<T>*> p = split(root);

        if (p.first->getLeft())
            p.first->getLeft()->setParent(nullptr);

        --size;
        return join(p.first->getLeft(), p.second);
    }

private:

    // Split tree by 2 subTrees
    std::pair<SplayNode<T>*, SplayNode<T>*> split(SplayNode<T>* x)
    {
        SplayNode<T>* Left{}, * Right{};
        if (x->getRight())
        {
            Right = x->getRight();
            Right->setParent(nullptr);
        }
        Left = x;
        Left->setRight(nullptr);
        x = nullptr;

        return { Left,Right };
    }

    // Join 2 subtrees in 1
    SplayNode<T>* join(SplayNode<T>* Left, SplayNode<T>* Right)
    {
        if (!Left)
        {
            root = Right;
            return Right;
        }

        if (!Right)
        {
            root = Left;
            return Left;
        }

        SplayNode<T>* curr = findMax(root->getLeft());

        curr->setRight(Right);
        curr->getRight()->setParent(curr);

        root = curr;
        delete root->getParent();

        return curr;
    }

public:

    // InOrder travelsal
    std::vector<T> inOrder(SplayNode<T>* _root = nullptr)   const
    {
        if (!_root) _root = root;

        std::vector<T> ans;
        SplayNode<T>* curr = _root;
        std::stack<SplayNode<T>*> s;

        while (curr || !s.empty())
        {
            while (curr)
            {
                s.push(curr);
                curr = curr->getLeft();
            }

            curr = s.top();
            s.pop();

            ans.push_back(curr->getData());
            curr = curr->getRight();
        }

        return ans;
    }

    // PreOrder travelsal
    std::vector<T> preOrder(SplayNode<T>* _root = nullptr)  const
    {
        if (!_root) _root = root;

        std::vector<T> ans;
        std::stack<SplayNode<T>*> s;

        s.push(_root);
        while (!s.empty())
        {
            auto curr = s.top();
            s.pop();

            if (curr)
                ans.push_back(curr->getData());
            else continue;
            s.push(curr->getRight());
            s.push(curr->getLeft());

        }

        return ans;
    }

    // PostOrder travelsal
    std::vector<T> postOrder(SplayNode<T>* _root = nullptr) const
    {
        if (!_root) _root = root;

        std::vector<T> ans;
        SplayNode<T>* it = _root;

        std::stack<SplayNode<T>*> s, s2;
        s.push(it);
        while (!s.empty())
        {
            auto curr = s.top();
            s.pop();

            if (!curr) continue;

            s2.push(curr);

            s.push(curr->getLeft());
            s.push(curr->getRight());
        }

        while (!s2.empty())
        {
            auto curr = s2.top();
            s2.pop();

            ans.push_back(curr->getData());
        }
        return ans;
    }

    SplayNode<T>* getRoot() const { return root; }

    int getSize() const { return size; };

private:

    // Print help function(choosing right order)
    void print_Helper(int index, SplayNode<T>* _root)   const
    {
        std::vector<T> ans;
        ans = (index == 1 ? inOrder(_root) : (index == 2 ? preOrder(_root) : postOrder(_root)));

        for (auto& it : ans)
            std::cout << it << ' ';
        std::cout << '\n';
    }

public:

    // Print functions
    void print_inOrder(SplayNode<T>* _root = nullptr)   const
    {
        print_Helper(1, _root);
    }

    void print_preOrder(SplayNode<T>* _root = nullptr)  const
    {
        print_Helper(2, _root);
    }

    void print_postOrder(SplayNode<T>* _root = nullptr) const
    {
        print_Helper(3, _root);
    }

    // Destructor
    ~SplayTree<T>()
    {
        while (size)
            erase(root->getData());
    }
};

#include <numeric>

int main()
{
    using namespace std;

    std::vector<int> vec{ 2, 5, 7, 3, 4, 10, 1, 6, 9, 8 };

    for (auto& it : vec) cout << it << ' ';
    cout << '\n';

    SplayTree<int> tree{ vec };

    std::cout << "Our start tree is:\n";
    tree.print_preOrder();
    std::cout << "Root " << tree.getRoot()->getData() << " Size " << tree.getSize() << "\n\n";

    std::cout << "Find maximum:" << tree.findMax()->getData() << '\n';
    std::cout << "Our tree now "; tree.print_preOrder(); std::cout << "Root " << tree.getRoot()->getData() << " Size " << tree.getSize() << "\n\n";

    std::cout << "Find minimum:" << tree.findMin()->getData() << '\n';
    std::cout << "Our tree now "; tree.print_preOrder(); std::cout << "Root " << tree.getRoot()->getData() << " Size " << tree.getSize() << "\n\n";

    int x = 1;

    std::cout << "Erase the " << x << '\n';
    tree.erase(x);
    std::cout << "Our tree now "; tree.print_preOrder(); std::cout << "Root " << tree.getRoot()->getData() << " Size " << tree.getSize() << "\n\n";

    x = 7;
    std::cout << "Erase the " << x << '\n';
    tree.erase(x);
    std::cout << "Our tree now "; tree.print_preOrder(); std::cout << "Root " << tree.getRoot()->getData() << " Size " << tree.getSize() << "\n\n";

    x = 10;
    std::cout << "Erase the " << x << '\n';
    tree.erase(x);
    std::cout << "Our tree now "; tree.print_preOrder(); std::cout << "Root " << tree.getRoot()->getData() << " Size " << tree.getSize() << "\n\n";

    x = 3;
    std::cout << "Search the " << x << '\n';
    tree.search(x);
    std::cout << "Our tree now "; tree.print_preOrder(); std::cout << "Root " << tree.getRoot()->getData() << " Size " << tree.getSize() << "\n\n";

    x = 10;
    std::cout << "Search the " << x << '\n';
    tree.search(x);
    std::cout << "Our tree now "; tree.print_preOrder(); std::cout << "Root " << tree.getRoot()->getData() << " Size " << tree.getSize() << "\n\n";

    using vi = vector<int>;

    vi vecc = tree.inOrder();
    std::cout << "InOrder:\t";
    for (auto& it : vecc) cout << it << ' ';
    cout << '\n';

    vecc = tree.preOrder();
    std::cout << "PreOrder:\t";
    for (auto& it : vecc) cout << it << ' ';
    cout << '\n';

    vecc = tree.postOrder();
    std::cout << "PostOrder:\t";
    for (auto& it : vecc) cout << it << ' ';
    cout << '\n';

    return 0;
}