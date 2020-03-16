#pragma once
#include <iostream>
#include <queue>
#include <cassert>
#include <ctime>
using namespace std;

template <typename Key, typename Value>
class BST {

private:
	struct Node {		// 节点
		Key key;
		Value value;
		Node* left;
		Node* right;
		// 节点构造
		Node(Key key, Value value) {	
			this->key = key;
			this->value = value;
			this->left = this->right = NULL;
		}
		// 节点复制的方式构造
		Node(Node* node) {
			this->key = node->key;
			this->value = node->value;
			this->left = node->left;
			this->right = node->right;
		}
	};
	Node* root;		// 根节点
	int count;		// 节点数
	// 向以node为根的二叉搜索树中,插入节点(key, value)
	// 返回插入新节点后的二叉搜索树的根
	Node* insert(Node* node, Key key, Value value) {
		if (node == NULL) {
			// 如果没有节点的话，新建一个节点然后返回
			count++;
			return  new Node(key, value);
		}
		if (key == node->key) {
			// 如果有相同值的话则不插入，但是需要覆盖原有值
			node->value = value;
		}
		else if (key < node->key) {
			// 向左边寻找
			node->left = insert(node->left, key, value);
		}
		else {
			// 向右边寻找
			node->right = insert(node->right, key, value);
		}
		return node;
	}
	bool contain(Node* node, Key key) {
		if (node == NULL) {
			return false;
		}
		if (node->key == key) {
			return true;
		}
		if (node-> key > key) {
			return contain(node->left, key);
		}
		if (node->key < key) {
			return contain(node->right, key);
		}

	}
	Value* search(Node* node, Key key) {
		if (node == NULL) {
			return NULL;
		}
		if (node->key == key) {
			return &(node->value);
		}
		if (node->key > key) {
			return search(node->left, key);
		}
		if (node->key < key) {
			return search(node->right, key);
		}
	}
	// 前序遍历
	void preOrder(Node* node) {
		if (node != NULL) {
			cout << node->key << endl;
			preOrder(node->left);
			preOrder(node->right);
		}
		return;
	}
	// 中序遍历
	void inOrder(Node* node) {
		if (node != NULL) {
			inOrder(node->left);
			cout << node->key << endl;
			inOrder(node->right);
		}
		return;
	}
	// 后序遍历
	void postOrder(Node* node) {
		if (node != NULL) {
			postOrder(node->left);
			postOrder(node->right);
			cout << node->key << endl;
		}
		return;
	}
	// 用后序遍历销毁节点
	void destroy(Node * node) {
		if (node != NULL) {
			destroy(node->left);
			destroy(node->right);
			delete node;
			--count;
		}
		return;
	}

	// 寻找最小键值的节点
	Node* minimum(Node* node) {
		// 向左找到最小
		if (node->left == NULL) {
			// 左孩子没有，则此时最小为node
			// 这种情况包括了，node是叶子节点，和node没有左孩子
			return node;
		}
		return minimum(node->left);		// 向左递归找
	}
	// 寻找最大键值的节点
	Node* maxmum(Node* node) {
		if (node->right == NULL) {
			return node;
		}
		return maxmum(node->right);
	}
	// 删除掉以node为根的二分搜索树中的最小节点
	// 返回删除节点后新的二分搜索树的根
	Node* removeMin(Node * node) {
		if (node->left == NULL) {
			Node* rightNode = node->right;
			delete node;
			--count;
			return rightNode;
		}

		node->left = removeMin(node->left);
		return node;

	}
	// 删除掉以node为根的二分搜索树中的最大节点
	// 返回删除节点后新的二分搜索树的根
	Node* removeMax(Node* node) {
		if (node->right == NULL) {
			Node* leftNode = node->left;
			delete node;
			--count;
			return leftNode;
		}
		node->right = removeMax(node->right);
		return node;
	}
	// 删除掉以node为根的二分搜索树中键值为key的节点
	// 返回删除节点后新的二分搜索树的根
	Node* remove(Node* node, Key key) {
		if (node == NULL) {
			return NULL;
		}
		if (key < node->key) {
			node->left = remove(node->left, key);
			return node;
		}
		else if (key > node->key) {
			node->right = remove(node->right, key);
			return node;
		}
		else {
			//key == node->key
			if (node->left == NULL) {
				Node* rightNode = node->right;
				delete node;
				--count;
				return rightNode;
			}
			if (node->right == NULL) {
				Node* leftNode = node->left;
				delete node;
				--count;
				return leftNode;
			}
			// node->left!=NULL && node->right !=NULL
			Node* successor = new Node(minimum(node->right));
			++count;
			successor->left = node->left;
			successor->right = removeMin(node->right);

			delete node;
			--count;
			return successor;

		}
	}

public:
	BST() {
		root = NULL;
		count = 0;
	}
	// 销毁
	~BST() {
		// TODO: ~BST()
		destroy(root);
	}
	// 返回大小
	int size() {
		return count;
	}
	// 判空
	bool isEmpty() {
		return count == 0;
	}
	// 插入节点
	void insert(Key key, Value value) {
		root = insert(root, key, value);
	}
	// 是否包含某个节点
	bool contain(Key key) {
		return contain(root, key);
	}
	// 搜索Key,返回Value
	Value* search(Key key) {
		return search(root, key);
	}
	// 前序遍历
	void preOrder() {
		preOrder(root);
		return;
	}
	// 中序遍历
	void inOrder() {
		inOrder(root);
		return;
	}
	// 后序遍历
	void postOrder() {
		postOrder(root);
		return;
	}
	// 层序遍历
	void levelOrder() {
		queue<Node*> q;
		q.push(root);
		while (!q.empty()) {
			Node* p = q.front();
			q.pop();
			cout << p->key << endl;
			if (p->left != NULL) {
				q.push(p->left);
			}
			if (p->right != NULL) {
				q.push(p->right);
			}
		}
		return;
	}

	// 寻找最小键值
	Key minimum() {
		assert(count != 0);
		Node* minNode = minimum(root);
		return minNode->key;
	}
	// 寻找最小键值
	Key maxmum() {
		assert(count != 0);
		Node* maxNode = maxmum(root);
		return maxNode->key;

	}
	// 从二叉树中删除最小值所在的节点
	void removeMin() {
		if (root) {
			root = removeMin(root);
		}
		return;
	}
	// 从二叉树中删除最大值所在的节点
	void removeMax() {
		if (root) {
			root = removeMax(root);
		}
		return;
	}
	
	void remove(Key key) {
		root = remove(root, key);
		return;
	}
};
// 随机打乱数组
void shuffle(int arr[], int n) {
	srand(time(NULL));
	for (int i = n - 1; i >= 0; i--) {
		int x = rand() % (i + 1);
		swap(arr[i], arr[x]);
	}
}
