#pragma once
#include <iostream>
#include <utility>


enum class NodeSides
{
	NoSide,
	Left,
	Right
};

template <typename Key, typename T>
struct Node
{
	Node* parent;
	Node* left;
	Node* right;
	std::pair<Key, T> keyAndValue;

	Node(Node* parent_, Node* left_, Node* right_, const std::pair<Key, T>& keyAndValue_):
		parent(parent_), left(left_), right(right_), keyAndValue(keyAndValue_)
	{}

	

	static NodeSides nodeSide(Node<Key, T>* ptr)
	{
		if (!ptr) return NodeSides::NoSide;
		if (!ptr->parent) return NodeSides::NoSide;

		if (ptr->parent->left == ptr)
		{
			return NodeSides::Left;
		}
		else
		{
			return NodeSides::Right;
		}
	}


	static Node<Key, T>* findMin(Node<Key, T>* ptr)
	{
		if (!ptr) return nullptr;

		while (ptr->left)
		{
			ptr = ptr->left;
		}

		return ptr;
	}


	static Node<Key, T>* findMax(Node<Key, T>* ptr)
	{
		if (!ptr) return nullptr;

		while (ptr->right)
		{
			ptr = ptr->right;
		}

		return ptr;
	}


	static Node<Key, T>* findNext(Node<Key, T>* ptr)
	{
		if (!ptr) return nullptr;
		if (ptr->right) return findMin(ptr->right);

		while (ptr->parent && nodeSide(ptr) == NodeSides::Right) {
			ptr = ptr->parent;
		}

		return ptr->parent; // maybe nullptr
	}


	static Node<Key, T>* findPrev(Node<Key, T>* ptr)
	{
		if (!ptr) return nullptr;
		if (ptr->left) return findMax(ptr->left);

		while (ptr->parent && nodeSide(ptr) == NodeSides::Left) {
			ptr = ptr->parent;
		}

		return ptr->parent; // maybe nullptr
	}


	~Node()
	{
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}
};


template <typename Key, typename T>
class BinaryTree
{
private:
	Node<Key,T>* root;
	int count;  ///<count of elements in binary tree


	void deleteTraversal(Node<Key,T>* ptr)
	{
		if (!ptr) return;

		deleteTraversal(ptr->left);
		deleteTraversal(ptr->right);
		delete ptr;
	}

	

public:
	BinaryTree() : root(nullptr), count(0) {}

	Node<Key, T>* getRoot() const { return root; }
	int getCount() const { return count; }


	enum class InsertStatuses
	{
		AlreadyExists,
		Inserted
	};

	std::pair< Node<Key, T>*, InsertStatuses> insert(const std::pair<Key, T>& keyAndValue)
	{
		Node<Key, T>* foundNode = find(keyAndValue.first);
		if (foundNode)
		{
			return std::make_pair(foundNode, InsertStatuses::AlreadyExists);
		}

		std::pair<Node<Key, T>*, InsertStatuses> res;

		if (!root)
		{
			root = new Node<Key, T>(nullptr, nullptr, nullptr, keyAndValue);
			res = std::make_pair(root, InsertStatuses::Inserted);
		}

		else
		{
			Node<Key, T>* parent = findTargetParent(keyAndValue.first);

			Node<Key, T>* new_node = new Node<Key, T>(parent, nullptr, nullptr, keyAndValue);

			if (keyAndValue.first < parent->keyAndValue.first)
			{
				parent->left = new_node;
			}

			else
			{
				parent->right = new_node;
			}

			res = std::make_pair(new_node, InsertStatuses::Inserted);
		}

		++count;
		return res;
	}

	enum class RemoveStatuses
	{
		NotExist,
		Removed
	};

	RemoveStatuses remove(const Key& key_)
	{
		Node<Key, T>* ptr = find(key_);
		if (!ptr) return RemoveStatuses::NotExist;

		if (ptr->left && ptr->right)  //2 children
		{
			Node<Key, T>* ptr_next = Node<Key, T>::findMin(ptr->right);

			Node<Key, T>* child = ptr_next->right;

			NodeSides side = Node<Key, T>::nodeSide(ptr_next);
			if (side == NodeSides::Left)
			{
				ptr_next->parent->left = child;
			}
			else
			{
				ptr_next->parent->right = child;
			}

			if (child)
			{
				child->parent = ptr_next->parent;
			}

			std::swap(ptr->keyAndValue.first, ptr_next->keyAndValue.first);
			std::swap(ptr->keyAndValue.second, ptr_next->keyAndValue.second);

			delete ptr_next;
		}

		else  //ptr has less than 2 children
		{
			Node<Key, T>* child;
			if (ptr->left)
			{
				child = ptr->left;
			}
			else if (ptr->right)
			{
				child = ptr->right;
			}
			else
			{
				child = nullptr;
			}

			if (child)
			{
				child->parent = ptr->parent;
			}

			NodeSides side = Node<Key, T>::nodeSide(ptr);
			if (side == NodeSides::Left)
			{
				ptr->parent->left = child;
			}
			else if (side == NodeSides::Right)
			{
				ptr->parent->right = child;
			}
			else  //ptr is root
			{
				root = child;
			}
			delete ptr;
		}

		--count;
		return RemoveStatuses::Removed;
	}


	Node<Key, T>* find(const Key& key_) const ///<doesn't return a copy!
	{
		Node<Key, T>* ptr = root;

		while (ptr)
		{
			if (key_ == ptr->keyAndValue.first)
			{
				return ptr;
			}
			else if (key_ < ptr->keyAndValue.first)
			{
				ptr = ptr->left;
			}
			else
			{
				ptr = ptr->right;
			}
		}

		return nullptr;
	}

	/*
	Node<Key, T>* findMax(Node<Key, T>* ptr) const
	{
		if (!ptr) return nullptr;

		while (ptr->right)
		{
			ptr = ptr->right;
		}

		return ptr;
	}
	*/

	void draw() const
	{
		drawTraversal(root, 0);
	}

	void drawTraversal(Node<Key, T>* ptr, int offset) const
	{
		if (!ptr) return;

		drawTraversal(ptr->right, offset + 1);

		for (int i = 0; i < offset; ++i) {
			std::cout << "\t\t";
		}
		char c;
		if (Node<Key, T>::nodeSide(ptr) == NodeSides::Left) c = '\\';
		else if (Node<Key, T>::nodeSide(ptr) == NodeSides::Right) c = '/';
		else c = ' ';

		std::cout << c << " (" << ptr->keyAndValue.first << ", " << ptr->keyAndValue.second << ")\n";

		drawTraversal(ptr->left, offset + 1);
	}


	Node<Key, T>* findTargetParent(const Key& key) const
	{
		Node<Key, T>* targetParent = nullptr;
		Node<Key, T>* ptr = root;

		while (ptr)
		{
			targetParent = ptr;

			if (key < ptr->keyAndValue.first)
			{
				ptr = ptr->left;
			}
			else
			{
				ptr = ptr->right;
			}
		}

		return targetParent;
	}

	

	~BinaryTree()
	{
		deleteTraversal(root);
	}
};





template <typename Key, typename T> 
class CustomMap
{


private:
	BinaryTree<Key, T> container;

public:
	class MapIterator
	{
	private:
		//BinaryTree<Key, T>* container;
		Node<Key, T>* cur;

	public:
		MapIterator() : cur(nullptr) {};
		MapIterator(Node<Key, T>* node) :  cur(node) {};

		std::pair<Key, T> operator* () { return cur->keyAndValue; }

		friend bool operator== (const MapIterator& it_1, const MapIterator& it_2) { return (it_1.cur == it_2.cur); }
		friend bool operator!= (const MapIterator& it_1, const MapIterator& it_2) { return !(it_1.cur == it_2.cur); }
		//bool operator!= (const MapIterator& it) { return !(it.cur == cur); }

		MapIterator& operator++()
		{
			cur = Node<Key, T>::findNext(cur);
			return *this;
		}

		MapIterator operator++(int)
		{
			MapIterator prev(*this);
			cur = Node<Key, T>::findNext(cur);
			return prev;
		}

		MapIterator& operator--()
		{
			cur = Node<Key, T>::findPrev(cur);
			return *this;
		}

		MapIterator operator--(int)
		{
			MapIterator prev(*this);
			cur = Node<Key, T>::findPrev(cur);
			return prev;
		}

	};


	class ConstMapIterator
	{
	private:
		//BinaryTree<Key, T>* container;
		Node<Key, T>* cur;

	public:
		ConstMapIterator() : cur(nullptr) {};
		ConstMapIterator(Node<Key, T>* el_ptr) : cur(el_ptr) {};

		std::pair<Key, T> operator* () { return cur->keyAndValue; }

		friend bool operator== (const ConstMapIterator& it_1, const ConstMapIterator& it_2) { return (it_1.cur == it_2.cur); }
		friend bool operator!= (const ConstMapIterator& it_1, const ConstMapIterator& it_2) { return !(it_1.cur == it_2.cur); }
		//bool operator== (const ConstMapIterator& it) { return (it.cur == cur); }
		//bool operator!= (const ConstMapIterator& it) { return !(it.cur == cur); }

		ConstMapIterator& operator++()
		{
			cur = Node<Key, T>::findNext(cur);
			return *this;
		}

		ConstMapIterator operator++(int)
		{
			ConstMapIterator prev(*this);
			cur = Node<Key, T>::findNext(cur);
			return prev;
		}

		ConstMapIterator& operator--()
		{
			cur = Node<Key, T>::findPrev(cur);
			return *this;
		}

		ConstMapIterator operator--(int)
		{
			ConstMapIterator prev(*this);
			cur = Node<Key, T>::findPrev(cur);
			return prev;
		}
	};


	class MapReverseIterator
	{
	private:
		//BinaryTree<Key, T>* container;
		Node<Key, T>* cur;

	public:
		MapReverseIterator() : cur(nullptr) {};
		MapReverseIterator(Node<Key, T>* el_ptr) : cur(el_ptr) {};

		std::pair<Key, T> operator* () { return cur->keyAndValue; }

		friend bool operator== (const MapReverseIterator& it_1, const MapReverseIterator& it_2) { return (it_1.cur == it_2.cur); }
		friend bool operator!= (const MapReverseIterator& it_1, const MapReverseIterator& it_2) { return !(it_1.cur == it_2.cur); }

		//bool operator== (const MapReverseIterator& it) { return (it.cur == cur); }
		//bool operator!= (const MapReverseIterator& it) { return !(it.cur == cur); }

		MapReverseIterator& operator++()
		{
			cur = Node<Key, T>::findPrev(cur);
			return *this;
		}

		MapReverseIterator operator++(int)
		{
			MapReverseIterator prev(*this);
			cur = Node<Key, T>::findPrev(cur);
			return prev;
		}

		MapReverseIterator& operator--()
		{
			cur = Node<Key, T>::findNext(cur);
			return *this;
		}

		MapReverseIterator operator--(int)
		{
			MapReverseIterator prev(*this);
			cur = Node<Key, T>::findNext(cur);
			return prev;
		}

	};



	class ConstMapReverseIterator
	{
	private:
		//const BinaryTree<Key, T>& container;
		Node<Key, T>* cur;
		
	public:
		ConstMapReverseIterator() = delete;
		ConstMapReverseIterator(Node<Key, T>* el_ptr) : cur(el_ptr) {};

		std::pair<Key, T> operator* () const { return cur->keyAndValue; }

		friend bool operator== (const ConstMapReverseIterator& it_1, const ConstMapReverseIterator& it_2) { return (it_1.cur == it_2.cur); }
		friend bool operator!= (const ConstMapReverseIterator& it_1, const ConstMapReverseIterator& it_2) { return !(it_1.cur == it_2.cur); }

		bool operator== (const ConstMapReverseIterator& it) { return (it.cur == cur); }
		bool operator!= (const ConstMapReverseIterator& it) { return !(it.cur == cur); }

		ConstMapReverseIterator& operator++()
		{
			cur = Node<Key, T>::findPrev(cur);
			//cur = container.findPrev(cur);
			return *this;
		}

		ConstMapReverseIterator operator++(int)
		{
			ConstMapReverseIterator prev(*this);
			cur = Node<Key, T>::findPrev(cur);
			return prev;
		}

		ConstMapReverseIterator& operator--()
		{
			cur = Node<Key, T>::findNext(cur);
			return *this;
		}

		ConstMapReverseIterator operator--(int)
		{
			ConstMapReverseIterator prev(*this);
			cur = Node<Key, T>::findNext(cur);
			return prev;
		}
	};

	friend class MapIterator;
	friend class ConstMapIterator;
	friend class MapReverseIterator;
	friend class ConstMapReverseIterator;


	using iterator = MapIterator;
	using const_iterator = ConstMapIterator;
	using reverse_iterator = MapReverseIterator;
	using const_reverse_iterator = ConstMapReverseIterator;



	CustomMap() : container() {};
	CustomMap(const CustomMap& map_) : container(map_.container) {};
	
	bool empty() const
	{
		return container.getCount() == 0;
	}

	int size() const
	{
		return container.getCount();
	}

	void erase(const Key& key_)
	{
		container.remove(key_);
	}

	iterator find(const Key& key)
	{
		return iterator(container.find(key));
	}
	const_iterator find(const Key& key) const
	{
		return const_iterator(container.find(key));
	}
	
	std::pair<iterator, bool> insert(const std::pair<Key, T>& keyAndValue)
	{
	
		std::pair<Node<Key, T>*, BinaryTree<Key, T>::InsertStatuses> resp = container.insert(keyAndValue);

		if (resp.second == BinaryTree<Key, T>::InsertStatuses::Inserted)
		{
			return std::make_pair(iterator(resp.first), true);
		}
		else
		{
			return std::make_pair(iterator(resp.first), false);
		}

	}


	MapIterator begin() noexcept { return MapIterator(Node<Key, T>::findMin(container.getRoot())); }
	MapIterator end() noexcept { return MapIterator(nullptr); }

	ConstMapIterator cbegin() const noexcept { return ConstMapIterator(Node<Key, T>::findMin(container.getRoot())); }
	ConstMapIterator cend()  const noexcept { return ConstMapIterator(nullptr); }

	MapReverseIterator rbegin() noexcept { return MapReverseIterator(Node<Key, T>::findMax(container.getRoot())); }
	MapReverseIterator rend() noexcept { return MapReverseIterator(nullptr); }

	ConstMapReverseIterator crbegin() const noexcept { return ConstMapReverseIterator(Node<Key, T>::findMax(container.getRoot())); }
	ConstMapReverseIterator crend() const noexcept { return ConstMapReverseIterator(nullptr); }
	
};














