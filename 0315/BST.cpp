#include <stdio.h>
#include <malloc.h>

// BST : Binary Search Tree , O(logn)

typedef struct _node {
	int data;
	struct _node *left;
	struct _node *right;
} Node;

Node *root = nullptr;

Node * makeNode(int value) {
	Node *newNode = (Node *)malloc(sizeof(Node));
	if (newNode) {
		newNode->data = value;
		newNode->left = nullptr;
		newNode->right = nullptr;
	}
	return newNode;
}

Node * searchBST(Node *node, int key) {
	if (node == nullptr) return nullptr;

	if (node->data < key)
		return searchBST(node->right, key);
	else if (node->data > key)
		return searchBST(node->left, key);
	else 
		return node;

	return nullptr;
}

Node *insertBST(Node *node, int value) {
	if (node == nullptr) {
		return makeNode(value);
	}

	if (node->data > value)
		node->left = insertBST(node->left, value);
	else if (node->data < value)
		node->right = insertBST(node->right, value);
	else {
		printf("Duplicate Key !!\n");
	}
	return node;
}

void printTree(Node *node, int depth, int level) {
	if (node == nullptr) return;
	if (depth > level) return;

	if (depth == level) printf("%d ",node->data);
	printTree(node->left, depth + 1, level);
	printTree(node->right, depth + 1, level);
}

void printBST(Node *node) {
	const int MAX_DEPTH = 5;

	for (int i = 0; i < MAX_DEPTH; i++) {
		printTree(node, 0, i);
		printf("\n");
	}
	printf("\n\n\n");
}

Node *findMostBiggestNode(Node *node) {
	while (node->right != nullptr) {
		node = node->right;
	}
	return node;
}

Node * removeBST(Node *node, int key) {
	if (node == nullptr) return nullptr;

	if (node->data < key)
		node->right = removeBST(node->right, key);
	else if (node->data > key)
		node->left = removeBST(node->left, key);
	else {
		// 삭제할 노드를 찾은 경우, 삭제 대상노드의 차수에 따라 로직이 다르다.
		if (node->left != nullptr && node->right != nullptr) {
			// degree = 2 
			// 삭제 대상 노드의 값보다 작은 노드 중에서 가장 큰 값 또는 큰 값 중에서 가장 작은 값을
			// 갖는 노드로 대체한다.
			Node *replaceNode = findMostBiggestNode(node->left);
			node->data = replaceNode->data;
			node->left = removeBST(node->left, replaceNode->data);
		}
		else {
			// degree = 0, 1
			Node *delNode = node;

			node = node->left;
			if (node == nullptr) {
				node = delNode->right;
			}

			free(delNode);
		}
	}

	return node;
}

int main() {
	root = insertBST(root, 9);
	root = insertBST(root, 12);
	root = insertBST(root, 4);
	root = insertBST(root, 15);
	root = insertBST(root, 3);
	root = insertBST(root, 6);
	root = insertBST(root, 17);
	root = insertBST(root, 13);

	Node *node = searchBST(root, 6);
	if (node) {
		printf("0x%p : %d \n", node, node->data);
	}
	else
		printf("Not Found ..!\n");

	printBST(root);

	root = removeBST(root, 13);
	printBST(root);

	root = removeBST(root, 12);
	printBST(root);

	root = removeBST(root, 9);
	printBST(root);


	return 0;
}