#include <algorithm>	// for std::swap, std::max
#include <cstddef>		// for std::size_t
#include <optional>		// for std::optional
#include <memory>		// for std::unique_ptr, strd::make_unique
#include <utility>		// for std::move, std:forward

template<typename Key>
class AVLNode {
public:

	Key key;
	int height;
	std::unique_ptr<AVLNode> left, right;

	explicit AVLNode(const Key& k = Key{})
		: key(k)
		, height(1)
		, left(nullptr)
		, right(nullptr)
	{ }

	~AVLNode() noexcept = default;

};


template<typename Key>
class AVLTree {
private:

	std::unique_ptr<AVLNode<Key>> root_; 
	std::size_t cnt_;

	// OK
	static int n_h_(const std::unique_ptr<AVLNode<Key>>& n) noexcept
	{
		return (n == nullptr ? 0 : n->height);
	}

	// OK
	static void update_h_(const std::unique_ptr<AVLNode<Key>>& n) noexcept
	{
		n->height = 1 + std::max(n_h_(n->left), n_h_(n->right));
	}

	// OK
	static int n_b_(const std::unique_ptr<AVLNode<Key>>& n) noexcept
	{
		if (!n) return 0;
		return n_h_(n->left) - n_h_(n->right);
	}

	// OK
	std::unique_ptr<AVLNode<Key>> r_rot_(std::unique_ptr<AVLNode<Key>> n) noexcept
	{
		std::unique_ptr<AVLNode<Key>> nl = std::move(n->left);
		
		n->left = std::move(nl->right);
		nl->right = std::move(n);

		update_h_(nl->right);
		update_h_(nl);

		return nl;
	}

	// OK
	std::unique_ptr<AVLNode<Key>> l_rot_(std::unique_ptr<AVLNode<Key>> n) noexcept
	{
		std::unique_ptr<AVLNode<Key>> nr = std::move(n->right);

		n->right = std::move(nr->left);
		nr->left = std::move(n);

		update_h_(nr->left);
		update_h_(nr);

		return nr;
	}

	// OK
	std::unique_ptr<AVLNode<Key>> balance_n_(std::unique_ptr<AVLNode<Key>> n)
	{
		update_h_(n);

		int nb = n_b_(n);
		if (nb == 2) {
			if (n_b_(n->left) == -1) n->left = l_rot_(std::move(n->left));
			return r_rot_(std::move(n));
		}
		else if (nb == -2) {
			if (n_b_(n->right) == 1) n->right = r_rot_(std::move(n->right));
			return l_rot_(std::move(n));
		}

		return n;
	}
	
	// OK
	const AVLNode<Key>* min_v_(const AVLNode<Key>* n) const noexcept
	{
		while (n->left) n = n->left.get();
		return n;
	}

	// OK
	const AVLNode<Key>* max_v_(const AVLNode<Key>* n) const noexcept
	{
		while (n->right) n = n->right.get();
		return n;
	}

	// OK
	template<typename T>
	std::unique_ptr<AVLNode<Key>> ins_key_(std::unique_ptr<AVLNode<Key>> n, T&& key)
	{
		if (!n) {
			++cnt_;
			return std::make_unique<AVLNode<Key>>(std::forward<T>(key));
		}
		if (n->key > key)
			n->left = ins_key_(std::move(n->left), std::forward<T>(key));
		else if (n->key < key)
			n->right = ins_key_(std::move(n->right), std::forward<T>(key));
		else
			return n;

		return balance_n_(std::move(n));
	}

	// OK
	template<typename T>
	std::unique_ptr<AVLNode<Key>>del_k_(std::unique_ptr<AVLNode<Key>> n, T&& key)
	{
		if (!n) return n;

		if (n->key > key)		n->left =  del_k_(std::move(n->left), std::forward<T>(key));
		else if (n->key < key)	n->right =  del_k_(std::move(n->right), std::forward<T>(key));
		else {
			if (n->left == nullptr || n->right == nullptr) {
				std::unique_ptr<AVLNode<Key>> tmp = (n->left == nullptr ? std::move(n->right) : std::move(n->left));
				--cnt_;
				return tmp;
			}
			else {
				const AVLNode<Key>* repl = min_v_(n->right.get());
				n->key = repl->key;
				n->right = del_k_(std::move(n->right), repl->key);
			}

		}

		return balance_n_(std::move(n));
	}

	// OK
	bool find_k_(const Key& key) const noexcept
	{
		AVLNode<Key>* curr = root_.get();
		while (curr) {
			if (curr->key > key)		curr = curr->left.get();
			else if (curr->key < key)	curr = curr->right.get();
			else return true;
		}
		return false;
	}

	// OK
	static bool is_eq_(const std::unique_ptr<AVLNode<Key>>& a, const std::unique_ptr<AVLNode<Key>>& b) noexcept
	{
		if (a == b) return true;
		if (!a || !b) return false;

		if (a->key != b->key || a->height != b->height)
			return false;
		return is_eq_(a->left, b->left) && is_eq_(a->right, b->right);
	}

	// OK
	static std::unique_ptr<AVLNode<Key>> copy_n_(const std::unique_ptr<AVLNode<Key>>& n)
	{
		if (!n) return nullptr;

		std::unique_ptr<AVLNode<Key>> res = std::make_unique<AVLNode<Key>>(n->key);

		res->height = n->height;
		res->left = copy_n_(n->left);
		res->right = copy_n_(n->right);

		return res;
	}

public:

	// OK
	AVLTree()
		: root_(nullptr)
		, cnt_(0)
	{ }

	// OK
	AVLTree(const AVLTree& tree)
		: root_(copy_n_(tree.root_))
		, cnt_(tree.cnt_)
	{ }

	// OK
	AVLTree(AVLTree&& tree) 
		: root_(std::move(tree.root_))
		, cnt_(tree.cnt_)
	{
		tree.cnt_ = 0;
	}

	// OK
	AVLTree& operator=(const AVLTree& other)
	{
		if (this != &other) {
			root_ = copy_n_(other.root_);
			cnt_ = other.cnt_;
		}
		return *this;
	}

	// OK
	AVLTree& operator=(AVLTree&& other)
	{
		if (this != &other) {

			root_ = std::move(other.root_);
			cnt_ = other.cnt_;

			other.cnt_ = 0;
		}
		return *this;
	}

	// OK
	void swap(AVLTree& other) noexcept 
	{
		std::swap(root_, other.root_);
		std::swap(cnt_, other.cnt_);
	}

	// OK
	bool operator==(const AVLTree& tree) const noexcept
	{
		if (cnt_ != tree.cnt_) return false;
		return is_eq_(root_, tree.root_);
	}

	// OK
	bool operator !=(const AVLTree& tree) const noexcept
	{
		return !(*this == tree);
	}

	// OK
	template<typename T>
	bool insert(T&& key)
	{
		std::size_t old_cnt = cnt_;
		root_ = ins_key_(std::move(root_), std::forward<T>(key));
		return old_cnt != cnt_;
	}

	// OK
	template<typename T>
	bool remove(T&& key)
	{
		std::size_t old_cnt = cnt_;
		root_ = del_k_(std::move(root_), std::forward<T>(key));
		return old_cnt != cnt_;
	}
	
	// OK
	std::size_t size() const noexcept
	{
		return cnt_;
	}

	// OK
	int height() const noexcept
	{
		return n_h_(root_);
	}

	// OK
	std::optional<Key> max_opt() const noexcept
	{
		return is_empty() ? std::nullopt : std::optional<Key>(max_v_(root_.get())->key);
	}

	// OK
	std::optional<Key> min_opt() const noexcept
	{
		return is_empty() ? std::nullopt : std::optional<Key>(min_v_(root_.get())->key);
	}

	// OK
	bool is_empty() const noexcept
	{
		return root_ == nullptr;
	}

	// OK
	bool contains(const Key& key) const noexcept
	{
		return find_k_(key);
	}

	// OK
	void clear() noexcept
	{
		root_.reset();
		cnt_ = 0;
	}

	// OK
	~AVLTree() noexcept = default;

};
