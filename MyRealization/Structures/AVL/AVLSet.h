#pragma once

#include <algorithm>		// for std::swap, std::max
#include <cstddef>			// for std::size_t, std::ptrdiff_t
#include <stdexcept>		// for std::runtime_error, std::invalid_argument
#include <iterator>			// for std::bidirectional_iterator_tag, std::reverse_iterator
#include <utility>			// for std::pair, std::forward
#include <initializer_list> // for std::initializer_list


/*====================================================================
This is AVLTree realization with basic pointers. Only keys, no values.
To use it with template, Key must have:
1. operator ==
2. operator <
3. operator =
=====================================================================*/

// AVLTree class
template<typename Key>
class AVLSet {
private:

	// AVLTree's node
	struct AVLNode {
	public:
		Key key;
		int height;
		AVLNode* left, *right, *parent;

		explicit AVLNode(const Key& k, AVLNode* p = nullptr)
			: key(k)
			, height(1)
			, left(nullptr)
			, right(nullptr)
			, parent(p)
		{ }
	};

	// Root node
	AVLNode* root_;

	AVLNode* help_;

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
		nl->parent = n->parent;
		n->parent = nl;
		n->left = nlr;
		if (nlr) nlr->parent = n;

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
		nr->parent = n->parent;
		n->parent = nr;
		n->right = nrl;
		if (nrl) nrl->parent = n;

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
	AVLNode* ins_k_(AVLNode* n, AVLNode* p, const Key& key)
	{
		if (!n) {
			++cnt_;
			return help_ = new AVLNode(key, p);
		}
		if (n->key < key) {
			n->right = ins_k_(n->right, n, key);
			if (n->right) n->right->parent = n;
		}
		else if (n->key == key) 
			return help_ = n;
		else {
			n->left = ins_k_(n->left, n, key);
			if (n->left) n->left->parent = n;
		}

		return balance_n_(n);
	}

	// Delete key method
	AVLNode* del_k_(AVLNode* n, const Key& key)
	{
		if (!n) return n;

		if (n->key < key) {
			n->right = del_k_(n->right, key);
			if (n->right) n->right->parent = n;
		}
		else if (n->key == key) {
			if (n->left == nullptr || n->right == nullptr) {
				AVLNode* tmp = (n->left == nullptr ? n->right : n->left);
				if (tmp) tmp->parent = n->parent;
				delete n;
				--cnt_;
				return tmp;
			}
			else {
				const AVLNode* repl = min_v_(n->right);
				n->key = repl->key;
				n->right = del_k_(n->right, n->key);
				if (n->right) n->right->parent = n;
			}
		}
		else {
			n->left = del_k_(n->left, key);
			if (n->left) n->left->parent = n;
		}

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

	// Compare set's method (in-order)
	static bool is_eq_(const AVLNode* a, const AVLNode* b) noexcept
	{
		if (!a && !b) return true;
		if (!a || !b) return false;

		if (!is_eq_(a->left, b->left)) return false;
		if (!(a->key == b->key)) return false;

		return is_eq_(a->right, b->right);
	}

	// Copy tree method
	static AVLNode* copy_n_(AVLNode* n, AVLNode* p)
	{
		if (!n) return n;

		AVLNode* res = new AVLNode(n->key, p);

		res->height = n->height;
		res->left = copy_n_(n->left, n);
		res->right = copy_n_(n->right, n);

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

	// Lower_bound implementation
	const AVLNode* l_bound_(const Key& key) const noexcept
	{
		AVLNode* curr = root_;
		AVLNode* res = nullptr;

		while (curr) {
			if (curr->key < key)
				curr = curr->right;
			else {
				res = curr;
				curr = curr->left;
			}
		}

		return res;
	}

	// Upper_bound implementation
	const AVLNode* r_bound_(const Key& key) const noexcept
	{
		const AVLNode* curr = root_;
		const AVLNode* res = nullptr;
	
		while (curr) {
			if (key < curr->key) {
				res = curr;
				curr = curr->left;
			}
			else
				curr = curr->right;
		}
	
		return res;
	}

public:

	// Basic constructor
	AVLSet()
		: root_(nullptr)
		, help_(nullptr)
		, cnt_(0)
	{ }

	// Initializer-list constructor
	AVLSet(std::initializer_list<Key> init_list)
		: AVLSet()
	{
		for (const auto& k : init_list)
			insert(k);
	}

	// Iterator-based constructor
	template<typename It>
	AVLSet(It first, It last)
		: AVLSet()
	{
		for (auto it = first; it != last; ++it)
			insert(*it);
	}

	// Deep-copy constructor
	AVLSet(const AVLSet& tree)
		: root_(copy_n_(tree.root_, nullptr))
		, help_(nullptr)
		, cnt_(tree.cnt_)
	{ }

	// Move-constructor
	AVLSet(AVLSet&& tree) noexcept
		: root_(tree.root_)
		, help_(nullptr)
		, cnt_(tree.cnt_)
	{
		tree.root_ = nullptr;
		tree.cnt_ = 0;
	}

	// Operator =
	AVLSet& operator=(const AVLSet& other)
	{
		if (this != &other) {
			clear();
			root_ = copy_n_(other.root_, nullptr);
			cnt_ = other.cnt_;
		}
		return *this;
	}

	// move operator = 
	AVLSet& operator=(AVLSet&& other) noexcept
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
	void swap(AVLSet& other) noexcept
	{
		std::swap(root_, other.root_);
		std::swap(cnt_, other.cnt_);
	}

	class iterator {
	public:

		using iterator_category = std::bidirectional_iterator_tag;
		using value_type = Key;
		using difference_type = std::ptrdiff_t;
		using pointer = const value_type*;
		using reference = const value_type&;

		friend class AVLSet;

	private:

		const AVLSet* tree_;
		const AVLNode* curr_node_;

		// Initialize begin() state
		void init_begin_() noexcept
		{
			curr_node_ = tree_->root_;
			if (!curr_node_) return;

			while (curr_node_->left)
				curr_node_ = curr_node_->left;
		}

		// Initialize rbegin() state
		void init_last_() noexcept
		{
			curr_node_ = tree_->root_;
			if (!curr_node_) return;

			while (curr_node_->right)
				curr_node_ = curr_node_->right;
		}

		// Find next key > current
		void find_next_k_() noexcept
		{
			if (curr_node_ == nullptr) return;

			if (curr_node_->right != nullptr) {
				curr_node_ = curr_node_->right;
				while (curr_node_->left)
					curr_node_ = curr_node_->left;
			}
			else {
				AVLNode* p = curr_node_->parent;
				while (p && curr_node_ == p->right) {
					curr_node_ = p;
					p = p->parent;
				}

				curr_node_ = p;
			}
		}

		// Find next key < current
		void find_prev_k_() noexcept
		{
			if (curr_node_ == nullptr)
				init_last_();

			else if (curr_node_->left != nullptr) {
				curr_node_ = curr_node_->left;
				while (curr_node_->right)
					curr_node_ = curr_node_->right;
			}
			else {
				AVLNode* p = curr_node_->parent;
				while (p && curr_node_ == p->left) {
					curr_node_ = p;
					p = p->parent;
				}
				curr_node_ = p;
			}
		}

		explicit iterator(const AVLSet* tr, const AVLNode* n)
			: tree_(tr)
			, curr_node_(n)
		{ }

	public:

		iterator()
			: tree_(nullptr)
			, curr_node_(nullptr)
		{ }

		iterator(const iterator& other)
		{
			tree_ = other.tree_;
			curr_node_ = other.curr_node_;
		}

		iterator& operator=(const iterator& other)
		{
			if (this != &other) {
				tree_ = other.tree_;
				curr_node_ = other.curr_node_;
			}
			return *this;
		}

		iterator& operator++() noexcept
		{
			find_next_k_();
			return *this;
		}

		iterator& operator--() noexcept
		{
			find_prev_k_();
			return *this;
		}

		iterator operator++(int) noexcept
		{
			iterator tmp = *this;
			++(*this);
			return tmp;
		}

		iterator operator--(int) noexcept
		{
			iterator tmp = *this;
			--(*this);
			return tmp;
		}

		reference operator*() const
		{
			if (curr_node_)
				return curr_node_->key;
			throw std::runtime_error("Dereference invalid iterator");
		}

		pointer operator->() const
		{
			if (curr_node_)
				return &(curr_node_->key);
			throw std::runtime_error("Dereference invalid iterator");
		}

		bool operator==(const iterator& other) const noexcept
		{
			return tree_ == other.tree_ && curr_node_ == other.curr_node_;
		}

		bool operator!=(const iterator& other) const noexcept
		{
			return !(*this == other);
		}

	};

	friend class iterator;

	// Keys are const, so const_iterator = iterator
	using const_iterator = iterator;

	using reverse_iterator = std::reverse_iterator<iterator>;
	using const_reverse_iterator = std::reverse_iterator<const_iterator>;

	// begin() end() iterators
	iterator begin() noexcept
	{
		iterator res(this, root_);
		res.init_begin_();
		return res;
	}

	const_iterator begin()	const noexcept 
	{ 
		const_iterator res(this, root_);
		res.init_begin_();
		return res;
	}

	iterator	   end()			noexcept { return iterator(this, nullptr); }
	const_iterator end()	const	noexcept { return const_iterator(this, nullptr); }

	const_iterator cbegin() const noexcept { return const_iterator(begin()); }
	const_iterator cend()	const noexcept { return const_iterator(end()); }

	reverse_iterator    rbegin()       noexcept { return reverse_iterator(end()); }
	reverse_iterator    rend()         noexcept { return reverse_iterator(begin()); }

	const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
	const_reverse_iterator rend()   const noexcept { return const_reverse_iterator(begin()); }

	const_reverse_iterator crbegin() const noexcept { return rbegin(); }
	const_reverse_iterator crend()   const noexcept { return rend(); }

	// Operator ==
	bool operator==(const AVLSet& tree) const noexcept
	{
		if (cnt_ != tree.cnt_) return false;

		return is_eq_(root_, tree.root_);
	}

	// Operator !=
	bool operator !=(const AVLSet& tree) const noexcept
	{
		return !(*this == tree);
	}

	// Insert key in tree. Bool is false, if key was already in tree
	std::pair<iterator, bool> insert(const Key& key)
	{
		std::size_t old_cnt = cnt_;
		root_ = ins_k_(root_, nullptr, key);
		return std::make_pair(iterator(this, help_), (old_cnt != cnt_));
	}

	// Erase from set by key
	std::size_t erase(const Key& key)
	{
		std::size_t old_cnt = cnt_;
		root_ = del_k_(root_, key);
		return old_cnt - cnt_;
	}

	// Erase by iterator
	iterator erase(const_iterator where)
	{
		if (where.tree_ != this)
			throw std::invalid_argument("Iterator does not belong to this container");

		if (where == end()) return end();
		
		Key key = *where;
		iterator nxt = where;
		++nxt;
		
		erase(key);
		return nxt;
	}

	// Erase by iterator range
	iterator erase(const_iterator first, const_iterator last)
	{
		if (first.tree_ != this || last.tree_ != this)
			throw std::invalid_argument("Iterator does not belong to this container");

		iterator it = first;
		while (it != last)
			it = erase(it);
		return it;
	}

	// Extract key from tree
	std::pair<bool, Key> extract(const Key& key)
	{
		return (erase(key) ? std::make_pair(true, key) : std::make_pair(false, Key{}));
	}

	// Extract by iterator
	std::pair<bool, Key> extract(const_iterator it)
	{
		if (it.tree_ != this)
			throw std::invalid_argument("Iterator does not belong to this container");

		if (it == end()) return std::make_pair(false, Key{});
		Key key = *it;
		erase(it);
		return std::make_pair(true, key);
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
		if (empty())
			throw std::runtime_error("max() called on empty tree");
		return max_v_(root_)->key;
	}

	// Return min key in the tree
	const Key& min() const
	{
		if (empty())
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

	// Return count of key in tree
	std::size_t count(const Key& key) const noexcept
	{
		return contains(key);
	}

	// Return iterator with find key, or end()
	iterator find(const Key& key) const noexcept
	{
		AVLNode* res = find_n_(key);
		return (res ? iterator(this, res) : end());
	}

	// Emplace method
	template<typename... Vals>
	std::pair<iterator, bool> emplace(Vals&&... vals)
	{
		Key key(std::forward<Vals>(vals)...);
		return insert(key);
	}

	// Emplace with hint (ignored)
	template<typename... Vals>
	iterator emplace_hint(const_iterator hint, Vals&&... vals)
	{
		return emplace(std::forward<Vals>(vals)...).first;
	}

	// Return iterator to first >= key (end() if didn't find)
	iterator lower_bound(const Key& key) const noexcept
	{
		return iterator(this, l_bound_(key));
	}

	// Return iterator to first > key (end() if didn't find)
	iterator upper_bound(const Key& key) const noexcept
	{
		return iterator(this, r_bound_(key));
	}

	// Return pair<lower_bound, upper_bound>
	std::pair<iterator, iterator> equal_range(const Key& key)
	{
		return std::make_pair(lower_bound(key), upper_bound(key));
	}

	// Merge trees
	void merge(AVLSet& tree)
	{
		iterator it = tree.begin();
		for (; it != tree.end(); it) {
			iterator curr = it++;
			if (!contains(*curr)) 
				insert(tree.extract(curr).second);
		}
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
	~AVLSet() noexcept
	{
		clear();
	}

};
