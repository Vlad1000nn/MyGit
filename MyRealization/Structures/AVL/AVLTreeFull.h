#pragma once

#include <algorithm>	// for std::swap, std::max
#include <cstddef>		// for std::size_t
#include <stdexcept>	// for std::runtime_error

/*====================================================================
This is AVLTree realization with basic pointers. Only keys, no values.
To use it with template, Key must have:
1. operator ==
2. operator <
3. operator =

Value must have:
1. operator =
=====================================================================*/


// AVLTree class
template<typename Key, typename Value>
class AVLTree {
private:

	// AVLTree's node
	struct AVLNode {
	public:
		Key key;
		Value val;
		int height;
		AVLNode* left, * right;

		explicit AVLNode(const Key& k, const Value& v)
			: key(k)
			, val(v)
			, height(1)
			, left(nullptr)
			, right(nullptr)
		{
		}
	};

	// Root node
	AVLNode* root_;
	// Population size
	std::size_t cnt_;

	// Return valid height of the node
	static int n_h_(AVLNode* n) noexcept
	{
		return (n == nullptr ? 0 : n->height);
	}

	// Update height of the node
	static void update_h_(AVLNode* n) noexcept
	{
		n->height = 1 + std::max(n_h_(n->left), n_h_(n->right));
	}

	// Return valid balance of the node
	static int n_b_(AVLNode* n) noexcept
	{
		if (!n) return 0;
		return n_h_(n->left) - n_h_(n->right);
	}

	// Right rotation
	static AVLNode* r_rot_(AVLNode* n) noexcept
	{
		AVLNode* nl = n->left;
		AVLNode* nlr = nl->right;

		nl->right = n;
		n->left = nlr;

		update_h_(n);
		update_h_(nl);

		return nl;
	}

	// Left rotation
	static AVLNode* l_rot_(AVLNode* n) noexcept
	{
		AVLNode* nr = n->right;
		AVLNode* nrl = nr->left;

		nr->left = n;
		n->right = nrl;

		update_h_(n);
		update_h_(nr);

		return nr;
	}

	// Balance node
	static AVLNode* balance_n_(AVLNode* n)
	{
		update_h_(n);

		int nb = n_b_(n);
		if (nb == 2) {
			if (n_b_(n->left) == -1) n->left = l_rot_(n->left);
			return r_rot_(n);
		}
		else if (nb == -2) {
			if (n_b_(n->right) == 1) n->right = r_rot_(n->right);
			return l_rot_(n);
		}

		return n;
	}

	// Return ptr to min value in subtree
	static const AVLNode* min_v_(const AVLNode* n) noexcept
	{
		while (n->left) n = n->left;
		return n;
	}

	// Return ptr to max value in subtree
	static const AVLNode* max_v_(const AVLNode* n) noexcept
	{
		while (n->right) n = n->right;
		return n;
	}

	// Insert key method
	AVLNode* ins_k_(AVLNode* n, const Key& key, const Value& val)
	{
		if (!n) {
			++cnt_;
			return new AVLNode(key, val);
		}
		if (n->key < key)
			n->right = ins_k_(n->right, key, val);
		else if (n->key == key)
			n->value = val;
		else
			n->left = ins_k_(n->left, key, val);

		return balance_n_(n);
	}

	// Delete key method
	AVLNode* del_k_(AVLNode* n, const Key& key)
	{
		if (!n) return n;

		if (n->key < key)
			n->right = del_k_(n->right, key);
		else if (n->key == key) {
			if (n->left == nullptr || n->right == nullptr) {
				AVLNode* tmp = (n->left == nullptr ? n->right : n->left);
				delete n;
				--cnt_;
				return tmp;
			}
			else {
				AVLNode* repl = min_v_(n->right);
				n->key = repl->key;
				n->value = repl->value;
				n->right = del_k_(n->right, n->key);
			}
		}
		else n->left = del_k_(n->left, key);

		return balance_n_(n);
	}

	// Find key method
	AVLNode* find_n_(const Key& key) const noexcept
	{
		AVLNode* curr = root_;
		while (curr) {
			if (curr->key < key)		curr = curr->right;
			else if (curr->key == key)	return curr;
			else						curr = curr->left;
		}
		return nullptr;
	}

	// Clear tree method
	static void clr_n_(AVLNode* n) noexcept
	{
		if (!n) return;
		clr_n_(n->left);
		clr_n_(n->right);
		delete n;
	}

	// Compare trees method
	static bool is_eq_(const AVLNode* a, const AVLNode* b) noexcept
	{
		if (a == b) return true;
		if (!a || !b) return false;

		if (!(a->key == b->key && a->val == b->val && a->height != b->height))
			return false;
		return is_eq_(a->left, b->left) && is_eq_(a->right, b->right);
	}

	// Copy tree method
	static AVLNode* copy_n_(AVLNode* n)
	{
		if (!n) return n;

		AVLNode* res = new AVLNode(n->key, n->val);
		
		res->height = n->height;
		res->left = copy_n_(n->left);
		res->right = copy_n_(n->right);

		return res;
	}

	// Pre-order implementation
	template<typename F>
	static void preor_impl_(const AVLNode* n, const F& f)
	{
		if (!n) return;

		f(n->key);
		preor_impl_(n->left, f);
		preor_impl_(n->right, f);
	}

	// In-order implementation
	template<typename F>
	static void inor_impl_(const AVLNode* n, const F& f)
	{
		if (!n) return;

		inor_impl_(n->left, f);
		f(n->key);
		inor_impl_(n->right, f);
	}

	// Post-order implementation
	template<typename F>
	static void postor_impl_(const AVLNode* n, const F& f)
	{
		if (!n) return;

		postor_impl_(n->left, f);
		postor_impl_(n->right, f);
		f(n->key);
	}

public:

	// Basic constructor
	AVLTree()
		: root_(nullptr)
		, cnt_(0)
	{ }

	// Deep-copy constructor
	AVLTree(const AVLTree& tree)
		: root_(copy_n_(tree.root_))
		, cnt_(tree.cnt_)
	{ }

	// Move-constructor
	AVLTree(AVLTree&& tree) noexcept
		: root_(tree.root_)
		, cnt_(tree.cnt_)
	{
		tree.root_ = nullptr;
		tree.cnt_ = 0;
	}

	// Operator =
	AVLTree& operator=(const AVLTree& other)
	{
		if (this != &other) {
			clear();
			root_ = copy_n_(other.root_);
			cnt_ = other.cnt_;
		}
		return *this;
	}

	// move operator = 
	AVLTree& operator=(AVLTree&& other) noexcept
	{
		if (this != &other) {
			clear();

			root_ = other.root_;
			cnt_ = other.cnt_;

			other.root_ = nullptr;
			other.cnt_ = 0;
		}
		return *this;
	}

	// Swap trees method
	void swap(AVLTree& other) noexcept
	{
		std::swap(root_, other.root_);
		std::swap(cnt_, other.cnt_);
	}

	// Operator ==
	bool operator==(const AVLTree& tree) const noexcept
	{
		if (cnt_ != tree.cnt_) return false;

		return is_eq_(root_, tree.root_);
	}

	// Operator !=
	bool operator !=(const AVLTree& tree) const noexcept
	{
		return !(*this == tree);
	}

	// Insert key in tree. Return true if successfull, false if key was already exists
	bool insert(const Key& key, const Value& val)
	{
		std::size_t old_cnt = cnt_;
		root_ = ins_k_(root_, key, val);
		return old_cnt != cnt_;
	}

	// Remove key from tree. Return true if successfull, false if key doesn't exists
	bool remove(const Key& key)
	{
		std::size_t old_cnt = cnt_;
		root_ = del_k_(root_, key);
		return old_cnt != cnt_;
	}

	// Return size of the tree
	std::size_t size() const noexcept
	{
		return cnt_;
	}

	// Return height of the tree
	int height() const noexcept
	{
		return n_h_(root_);
	}

	// Return max key in the tree
	const Key& max() const
	{
		if (empty)
			throw std::runtime_error("max() called on empty tree");
		return max_v_(root_)->key;
	}

	// Return min key in the tree
	const Key& min() const
	{
		if (empty)
			throw std::runtime_error("min() called on empty tree");
		return min_v_(root_)->key;
	}

	// Return true if tree is empty
	bool empty() const noexcept
	{
		return root_ == nullptr;
	}

	// Return true if tree contains key
	bool contains(const Key& key) const noexcept
	{
		return find_n_(key) != nullptr;
	}

	// Clear method
	void clear() noexcept
	{
		clr_n_(root_);
		root_ = nullptr;
		cnt_ = 0;
	}

	// Apply function to tre in pre-order
	template<typename F>
	void preorder(const F& f) const
	{
		preor_impl_(root_, f);
	}

	// Apply function to tre in in-order
	template<typename F>
	void inorder(const F& f) const
	{
		inor_impl_(root_, f);
	}

	// Apply function to tre in post-order
	template<typename F>
	void postorder(const F& f) const
	{
		postor_impl_(root_, f);
	}
	
	// Basic destructor
	~AVLTree() noexcept
	{
		clear();
	}

};
