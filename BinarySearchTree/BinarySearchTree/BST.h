#pragma once
#include <iostream>
#include <queue>
#include <cassert>
#include <ctime>
using namespace std;

template <typename Key, typename Value>
class BST {

private:
	struct Node {		// �ڵ�
		Key key;
		Value value;
		Node* left;
		Node* right;
		// �ڵ㹹��
		Node(Key key, Value value) {	
			this->key = key;
			this->value = value;
			this->left = this->right = NULL;
		}
		// �ڵ㸴�Ƶķ�ʽ����
		Node(Node* node) {
			this->key = node->key;
			this->value = node->value;
			this->left = node->left;
			this->right = node->right;
		}
	};
	Node* root;		// ���ڵ�
	int count;		// �ڵ���
	// ����nodeΪ���Ķ�����������,����ڵ�(key, value)
	// ���ز����½ڵ��Ķ����������ĸ�
	Node* insert(Node* node, Key key, Value value) {
		if (node == NULL) {
			// ���û�нڵ�Ļ����½�һ���ڵ�Ȼ�󷵻�
			count++;
			return  new Node(key, value);
		}
		if (key == node->key) {
			// �������ֵͬ�Ļ��򲻲��룬������Ҫ����ԭ��ֵ
			node->value = value;
		}
		else if (key < node->key) {
			// �����Ѱ��
			node->left = insert(node->left, key, value);
		}
		else {
			// ���ұ�Ѱ��
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
	// ǰ�����
	void preOrder(Node* node) {
		if (node != NULL) {
			cout << node->key << endl;
			preOrder(node->left);
			preOrder(node->right);
		}
		return;
	}
	// �������
	void inOrder(Node* node) {
		if (node != NULL) {
			inOrder(node->left);
			cout << node->key << endl;
			inOrder(node->right);
		}
		return;
	}
	// �������
	void postOrder(Node* node) {
		if (node != NULL) {
			postOrder(node->left);
			postOrder(node->right);
			cout << node->key << endl;
		}
		return;
	}
	// �ú���������ٽڵ�
	void destroy(Node * node) {
		if (node != NULL) {
			destroy(node->left);
			destroy(node->right);
			delete node;
			--count;
		}
		return;
	}

	// Ѱ����С��ֵ�Ľڵ�
	Node* minimum(Node* node) {
		// �����ҵ���С
		if (node->left == NULL) {
			// ����û�У����ʱ��СΪnode
			// ������������ˣ�node��Ҷ�ӽڵ㣬��nodeû������
			return node;
		}
		return minimum(node->left);		// ����ݹ���
	}
	// Ѱ������ֵ�Ľڵ�
	Node* maxmum(Node* node) {
		if (node->right == NULL) {
			return node;
		}
		return maxmum(node->right);
	}
	// ɾ������nodeΪ���Ķ����������е���С�ڵ�
	// ����ɾ���ڵ���µĶ����������ĸ�
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
	// ɾ������nodeΪ���Ķ����������е����ڵ�
	// ����ɾ���ڵ���µĶ����������ĸ�
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
	// ɾ������nodeΪ���Ķ����������м�ֵΪkey�Ľڵ�
	// ����ɾ���ڵ���µĶ����������ĸ�
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
	// ����
	~BST() {
		// TODO: ~BST()
		destroy(root);
	}
	// ���ش�С
	int size() {
		return count;
	}
	// �п�
	bool isEmpty() {
		return count == 0;
	}
	// ����ڵ�
	void insert(Key key, Value value) {
		root = insert(root, key, value);
	}
	// �Ƿ����ĳ���ڵ�
	bool contain(Key key) {
		return contain(root, key);
	}
	// ����Key,����Value
	Value* search(Key key) {
		return search(root, key);
	}
	// ǰ�����
	void preOrder() {
		preOrder(root);
		return;
	}
	// �������
	void inOrder() {
		inOrder(root);
		return;
	}
	// �������
	void postOrder() {
		postOrder(root);
		return;
	}
	// �������
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

	// Ѱ����С��ֵ
	Key minimum() {
		assert(count != 0);
		Node* minNode = minimum(root);
		return minNode->key;
	}
	// Ѱ����С��ֵ
	Key maxmum() {
		assert(count != 0);
		Node* maxNode = maxmum(root);
		return maxNode->key;

	}
	// �Ӷ�������ɾ����Сֵ���ڵĽڵ�
	void removeMin() {
		if (root) {
			root = removeMin(root);
		}
		return;
	}
	// �Ӷ�������ɾ�����ֵ���ڵĽڵ�
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
// �����������
void shuffle(int arr[], int n) {
	srand(time(NULL));
	for (int i = n - 1; i >= 0; i--) {
		int x = rand() % (i + 1);
		swap(arr[i], arr[x]);
	}
}
