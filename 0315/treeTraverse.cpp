#include <iostream>
#include <cstdio>

const int TREE_SZ = 50;

int tree[TREE_SZ];
int V, E;

using namespace std;

int findNode(int node) {
	for (int i = 0; i < TREE_SZ; i++) {
		if (tree[i] == node) {
			return i;
		}
	}
	return -1;
}

void preorder(int node) {
	if (node >= TREE_SZ  || tree[node] == 0) return;	// 범위를 벗어나거나 값이 없는 노드 skip

	cout << tree[node] << " ";
	preorder(2 * node);
	preorder(2 * node + 1);
}

void inorder(int node) {
	if (node >= TREE_SZ || tree[node] == 0) return;

	inorder(2 * node);
	cout << tree[node] << " ";
	inorder(2 * node + 1);
}

void postorder(int node) {
	if (node >= TREE_SZ || tree[node] == 0) return;

	postorder(2 * node);
	postorder(2 * node + 1);
	cout << tree[node] << " ";
}


void levelorder(int node) {
	int pow2[] = { 1,2,4,8,16,32,64 };
	int next_level = 1;

	for (int i = node; i < TREE_SZ; i++) {
		if (i == pow2[next_level]) {
			cout << endl;
			next_level++;
		}

		if (tree[i] > 0) {
			cout << tree[i] << " ";
		}
	}

	cout << endl;
}

void search_tree(int node, int level, int depth) {
	if (level > depth) return;
	if (tree[node] == 0) return;

	if (level == depth) {
		cout << tree[node] << " ";
	}
	search_tree(2 * node, level + 1, depth);
	search_tree(2 * node + 1, level + 1, depth);
}

void level_order2() {
	const int max_level = 5;

	for (int i = 0; i < max_level; i++) {
		search_tree(1, 0, i);
		cout << endl;
	}
	cout << endl;
}

int main() {
	freopen("tree_input.txt", "r", stdin);

	cin >> V >> E;
	for (int i = 0; i < E; i++) {
		int parent, child;
		cin >> parent >> child;

		int pIdx = findNode(parent);
		if (pIdx < 0) {
			pIdx = 1;		// root
			tree[pIdx] = parent;
		}

		if (tree[2 * pIdx] == 0)
			tree[2 * pIdx] = child;
		else
			tree[2 * pIdx + 1] = child;
			
	}

	cout << "전위 순회 : ";
	preorder(1);
	cout << endl;

	cout << "중위 순회 : ";
	inorder(1);
	cout << endl;

	cout << "후위 순회 : ";
	postorder(1);
	cout << endl;

	cout << "Level 순회 : " << endl;
	levelorder(1);
	cout << endl;


	cout << "Level 순회 : " << endl;
	level_order2();

	return 0;
}