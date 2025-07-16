#pragma once

#include <algorithm>	// for std::swap, std::max
#include <cstddef>		// for std::size_t
#include <optional>		// for std::optional

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
	{
	}

	~AVLNode() noexcept = default;

};


template<typename Key>
class AVLTree {
private:

	AVLNode<Key>* root_;
	std::size_t cnt_;

	// OK
	static int n_h_(AVLNode<Key>* n) noexcept
	{
		return (n == nullptr ? 0 : n->height);
	}

	// OK
	static void update_h_(AVLNode<Key>* n) noexcept
	{
		n->height = 1 + std::max(n_h_(n->left), n_h_(n->right));
	}

	// OK
	static int n_b_(AVLNode<Key>* n) noexcept
	{
		if (!n) return 0;
		return n_h_(n->left) - n_h_(n->right);
	}

	// OK
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

	// OK
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

	// OK
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

	// OK
	AVLNode<Key>* min_v_(AVLNode<Key>* n) const noexcept
	{
		while (n->left) n = n->left;
		return n;
	}

	// OK
	AVLNode<Key>* max_v_(AVLNode<Key>* n) const noexcept
	{
		while (n->right) n = n->right;
		return n;
	}

	// OK
	AVLNode<Key>* ins_key_(AVLNode<Key>* n, const Key& key)
	{
		if (!n) {
			++cnt_;
			return new AVLNode<Key>(key);
		}
		if (n->key > key)
			n->left = ins_key_(n->left, key);
		else if (n->key < key)
			n->right = ins_key_(n->right, key);
		else
			return n;

		return balance_n_(n);
	}

	// OK
	AVLNode<Key>* del_k_(AVLNode<Key>* n, const Key& key)
	{
		if (!n) return n;

		if (n->key > key)		n->left = del_k_(n->left, key);
		else if (n->key < key)	n->right = del_k_(n->right, key);
		else {
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

		return balance_n_(n);
	}

	// OK
	bool find_k_(const Key& key) const noexcept
	{
		AVLNode<Key>* curr = root_;
		while (curr) {
			if (curr->key > key)		curr = curr->left;
			else if (curr->key < key)	curr = curr->right;
			else return true;
		}
		return false;
	}

	// OK
	void clr_n_(AVLNode<Key>* n) noexcept
	{
		if (!n) return;
		clr_n_(n->left);
		clr_n_(n->right);
		delete n;
	}

public:

	// OK
	AVLTree()
		: root_(nullptr)
		, cnt_(0)
	{
	}

	// OK
	AVLTree(const AVLTree& tree)
		: root_(copy_n_(tree.root_))
		, cnt_(tree.cnt_)
	{
	}

	// OK
	AVLTree(AVLTree&& tree) noexcept
		: root_(tree.root_)
		, cnt_(tree.cnt_)
	{
		tree.root_ = nullptr;
		tree.cnt_ = 0;
	}

	// OK
	AVLTree& operator=(const AVLTree& other)
	{
		if (this != &other) {
			clear();
			root_ = copy_n_(other.root_);
			cnt_ = other.cnt_;
		}
		return *this;
	}

	// OK
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

	// OK
	static bool is_eq_(const AVLNode<Key>* a, const AVLNode<Key>* b) noexcept
	{
		if (a == b) return true;
		if (!a || !b) return false;

		if (a->key != b->key || a->height != b->height)
			return false;
		return is_eq_(a->left, b->left) && is_eq_(a->right, b->right);
	}

	// OK
	static AVLNode<Key>* copy_n_(AVLNode<Key>* n)
	{
		if (!n) return n;

		AVLNode<Key>* res = new AVLNode<Key>(n->key);

		res->height = n->height;
		res->left = copy_n_(n->left);
		res->right = copy_n_(n->right);

		return res;
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
	bool insert(const Key& key)
	{
		std::size_t old_cnt = cnt_;
		root_ = ins_key_(root_, key);
		return old_cnt != cnt_;
	}

	// OK
	bool remove(const Key& key)
	{
		std::size_t old_cnt = cnt_;
		root_ = del_k_(root_, key);
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
	std::optional<Key> max_opt() const
	{
		return is_empty() ? std::nullopt : std::optional<Key>(max_v_(root_)->key);
	}

	// OK
	std::optional<Key> min_opt() const
	{
		return is_empty() ? std::nullopt : std::optional<Key>(min_v_(root_)->key);
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
		clr_n_(root_);
		root_ = nullptr;
		cnt_ = 0;
	}

	// OK
	~AVLTree() noexcept
	{
		clear();
	}

};
