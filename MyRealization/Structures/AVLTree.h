#pragma once

#include <algorithm>	// for std::swap, std::max
#include <cstddef>		// for std::size_t
#include <optional>		// for std::optional


/*====================================================================
This is AVLTree realization with basic pointers. Only keys, no values.
To use it with template, Key must have:
1. operator ==
2. operator <
3. operator =
=====================================================================*/


// AVLTree's node
template<typename Key>
class AVLNode {
public:

	Key key;
	int height;
	AVLNode* left, * right;

	explicit AVLNode(const Key& k = Key{})
		: key(k)
		, height(1)
		, left(nullptr)
		, right(nullptr)
	{ }

	~AVLNode() noexcept = default;

};

// AVLTree class
template<typename Key>
class AVLTree {
private:

	// Root node
	AVLNode<Key>* root_;
	// Population size
	std::size_t cnt_;

	// Return valid height of the node
	static int n_h_(AVLNode<Key>* n) noexcept
	{
		return (n == nullptr ? 0 : n->height);
	}

	// Update height of the node
	static void update_h_(AVLNode<Key>* n) noexcept
	{
		n->height = 1 + std::max(n_h_(n->left), n_h_(n->right));
	}

	// Return valid balance of the node
	static int n_b_(AVLNode<Key>* n) noexcept
	{
		if (!n) return 0;
		return n_h_(n->left) - n_h_(n->right);
	}

	// Right rotation
	AVLNode<Key>* r_rot_(AVLNode<Key>* n) noexcept
	{
		AVLNode<Key>* nl = n->left;
		AVLNode<Key>* nlr = nl->right;

		nl->right = n;
		n->left = nlr;

		update_h_(n);
		update_h_(nl);

		return nl;
	}

	// Left rotation
	AVLNode<Key>* l_rot_(AVLNode<Key>* n) noexcept
	{
		AVLNode<Key>* nr = n->right;
		AVLNode<Key>* nrl = nr->left;

		nr->left = n;
		n->right = nrl;

		update_h_(n);
		update_h_(nr);

		return nr;
	}

	// Balance node
	AVLNode<Key>* balance_n_(AVLNode<Key>* n)
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
	const AVLNode<Key>* min_v_(const AVLNode<Key>* n) const noexcept
	{
		while (n->left) n = n->left;
		return n;
	}

	// Return ptr to max value in subtree
	const AVLNode<Key>* max_v_(const AVLNode<Key>* n) const noexcept
	{
		while (n->right) n = n->right;
		return n;
	}

	// Insert key method
	AVLNode<Key>* ins_key_(AVLNode<Key>* n, const Key& key)
	{
		if (!n) {
			++cnt_;
			return new AVLNode<Key>(key);
		}
		if (n->key < key)
			n->right = ins_key_(n->right, key);
		else if (n->key == key)
			return n;
		else
			n->left = ins_key_(n->left, key);

		return balance_n_(n);
	}

	// Delete key method
	AVLNode<Key>* del_k_(AVLNode<Key>* n, const Key& key)
	{
		if (!n) return n;

		if (n->key < key)		
			n->right = del_k_(n->right, key);
		else if (n->key == key)	{
			if (n->left == nullptr || n->right == nullptr) {
				AVLNode<Key>* tmp = (n->left == nullptr ? n->right : n->left);
				delete n;
				--cnt_;
				return tmp;
			}
			else {
				AVLNode<Key>* repl = min_v_(n->right);
				n->key = repl->key;
				n->right = del_k_(n->right, n->key);
			}
		}
		else n->left = del_k_(n->left, key);

		return balance_n_(n);
	}

	// Find key method
	bool find_k_(const Key& key) const noexcept
	{
		AVLNode<Key>* curr = root_;
		while (curr) {
			if (curr->key < key)		curr = curr->right;
			else if (curr->key == key)	return true;
			else						curr = curr->left;
		}
		return false;
	}

	// Clear tree method
	void clr_n_(AVLNode<Key>* n) noexcept
	{
		if (!n) return;
		clr_n_(n->left);
		clr_n_(n->right);
		delete n;
	}

	// Compare trees method
	static bool is_eq_(const AVLNode<Key>* a, const AVLNode<Key>* b) noexcept
	{
		if (a == b) return true;
		if (!a || !b) return false;

		if (!(a->key == b->key && a->height != b->height))
			return false;
		return is_eq_(a->left, b->left) && is_eq_(a->right, b->right);
	}

	// Copy tree method
	static AVLNode<Key>* copy_n_(AVLNode<Key>* n)
	{
		if (!n) return n;

		AVLNode<Key>* res = new AVLNode<Key>(n->key);

		res->height = n->height;
		res->left = copy_n_(n->left);
		res->right = copy_n_(n->right);

		return res;
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
	bool insert(const Key& key)
	{
		std::size_t old_cnt = cnt_;
		root_ = ins_key_(root_, key);
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

	// Return max in the tree (std::nullopt if tree is empty)
	std::optional<Key> max_opt() const
	{
		return is_empty() ? std::nullopt : std::optional<Key>(max_v_(root_)->key);
	}

	// Return min in the tree (std::nullopt if tree is empty)
	std::optional<Key> min_opt() const
	{
		return is_empty() ? std::nullopt : std::optional<Key>(min_v_(root_)->key);
	}

	// Return true if tree is empty
	bool is_empty() const noexcept
	{
		return root_ == nullptr;
	}

	// Return true if tree contains key
	bool contains(const Key& key) const noexcept
	{
		return find_k_(key);
	}

	// Clear method
	void clear() noexcept
	{
		clr_n_(root_);
		root_ = nullptr;
		cnt_ = 0;
	}

	// Basic destructor
	~AVLTree() noexcept
	{
		clear();
	}

};
