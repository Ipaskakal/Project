#include <iostream>

using namespace std;

class SplayTree {
private:
	typedef struct Tree {
		Tree *right, *left, *parent;
		int key;
		Tree(int Key, Tree* Left, Tree* Right, Tree* Parent) {
			key = Key;
			left = Left;
			right = Right;
			parent = Parent;
		}

	} Node, *ptrNode;
	ptrNode root = nullptr;

	void SetParent(ptrNode child, ptrNode parent) {
		if (child)
			child->parent = parent;
	}

	void SetParentForCh(ptrNode vertex) {
		if (vertex->left)
			SetParent(vertex->left, vertex);
		if (vertex->right)
			SetParent(vertex->right, vertex);
	}

	
	void Rotate(ptrNode parent, ptrNode child) {
		ptrNode grandp = parent ? parent->parent : nullptr;

		if (grandp)
			if (grandp->left == parent)
				grandp->left = child;
			else
				grandp->right = child;

		if (parent->left == child) {
			parent->left = child->right;
			child->right = parent;
		}
		else {
			parent->right = child->left;
			child->left = parent;
		}

		SetParentForCh(child);
		SetParentForCh(parent);
		child->parent = grandp;
	}

	
	ptrNode Splay(ptrNode vertex) {
		if (!vertex->parent)
			return vertex;

		ptrNode parent = vertex->parent;
		ptrNode grandp = parent ? parent->parent : nullptr;

		if (!grandp) {
			Rotate(parent, vertex);
			return vertex;
		}
		else {
			if ((grandp->left == parent) == (parent->left == vertex)) {
				Rotate(grandp, parent);
				Rotate(parent, vertex);
			}
			else {
				Rotate(parent, vertex);
				Rotate(grandp, vertex);
			}
			return Splay(vertex);
		}

	}

	ptrNode FindAndSplay(ptrNode vertex, int key) {
		if (!vertex)
			return nullptr;

		if (key == vertex->key)
			return Splay(vertex);

		if (key < vertex->key && vertex->left != nullptr)
			return FindAndSplay(vertex->left, key);


		if (key > vertex->key && vertex->right != nullptr)
			return FindAndSplay(vertex->right, key);

		return Splay(vertex);
	}

	pair<ptrNode, ptrNode> Split(int key) {
		if (!root)
			return make_pair(nullptr, nullptr);

		root = FindAndSplay(root, key);

		if (root->key == key) {
			SetParent(root->left, nullptr);
			SetParent(root->right, nullptr);
			ptrNode left = root->left, right = root->right;
			delete root;
			return make_pair(root->left, root->right);
		}

		if (root->key < key) {
			ptrNode right = root->right;
			root->right = nullptr;
			SetParent(right, nullptr);
			return make_pair(root, right);
		}
		else {
			ptrNode left = root->left;
			root->left = nullptr;
			SetParent(left, nullptr);
			return make_pair(left, root);
		}
	}


	ptrNode Merge(ptrNode left, ptrNode right) {
		if (!left)
			return right;
		if (!right)
			return left;
		right = FindAndSplay(right, left->key);
		right->left = left;
		left->parent = right;
		return right;
	}

	void Oput(ptrNode vertex) {
		cout << vertex->key;
		if (vertex->left)
			Oput(vertex->left);
		if (vertex->right)
			Oput(vertex->right);
	}

public:
	void Insert(int key) {
		pair <ptrNode, ptrNode> peaces;
		if (root) {
			peaces = Split(key);
		}

		root = new Node(key, peaces.first, peaces.second, nullptr);

		SetParentForCh(root);
	}

	void Delete(int key) {
		root = FindAndSplay(root, key);
		SetParent(root->left, nullptr);
		SetParent(root->right, nullptr);
		Merge(root->left, root->right);
	}

	bool Find(int key) {
		root = FindAndSplay(root, key);
		return (root->key == key);
	}

	void Output() {
		Oput(root);
	}
};

int main()
{
	SplayTree tree;
	int x = 1;
	while (x) {
		cout << "1 - Input\n";
		cout << "2 - Find \n";
		cout << "3 - Delete\n";
		cout << "4 - Output\n";
		cout << "0 - Exit\n";
		cin >> x;
		switch (x)
		{
		case 1: {
			cout << "Input number of values\n";
			int y, z;
			cin >> y;
			for (int i = 0; i < y; i++) {
				cin >> z;
				tree.Insert(z);
			}
			break;
		};
		case 2: {
			cout << "Input value of searching elem\n";
			int y;
			cin >> y;
			tree.Find(y);
			break;
		};
		case 3: {
			cout << "Input value of deleting elem\n";
			int y;
			cin >> y;
			tree.Delete(y);
			break;
		};
		case 4: {
			tree.Output();
			break;
		}
		}
		cout << "\n\n\n\n\n";
	}
}
