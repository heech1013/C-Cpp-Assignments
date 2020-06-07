#include <cstdio>  // file io
#include <cstdlib>  // malloc(), calloc()
#include <cstring>  // memset()
#include <iostream>
#include <vector>
#include <utility>
#include <string>

#define max(a,b) ((a)>(b))?(a):(b)

using namespace std;

typedef struct Node {
	string word;
	string meaning;
	Node *left, *right;
} Node;

Node* makeBST(vector<Node*> V, int start, int end, int* count) {
	if (start > end) return NULL;
	int mid = (start + end) / 2;
	
	if (mid % 1000 == 0)
		cout << mid << "��° �ܾ ó�� ���Դϴ�..." << "\n"; 
	
	Node* node = V[mid];
	(*count)++;
	
//	cout << "curr node: (" << mid << ")" << node->word << "\n";
	
	node->left = makeBST(V, start, mid - 1, count);
//	if (node->left != NULL)
//		cout << "left node: " << node->left->word << "\n";
	
	node->right = makeBST(V, mid + 1, end, count);
//	if (node->right != NULL)
//		cout << "right node: " << node->right->word << "\n";
		
	return node;
}

int getHeight(Node* root) {
	int height = 0;
	
	Node *curr = root;
	while (curr != NULL) {
		curr = curr->left;
		height++;
	}
	
	return height;
}

void search(Node *root, string input) {
	Node *curr = root;
	int level = 1;
	while (input.compare(curr->word) != 0) {
		if (input < curr->word) {
			curr = curr->left;
			level++;
		}
		else if (input > curr->word) {
			curr = curr->right;
			level++;
		}
	}
	cout << "(���� " << level << ")" << curr->meaning << "\n";
}

int main() {
	FILE *fp = fopen("dict_test.txt", "r");  // ������ �б� ���� ���� ���� �����͸� ��ȯ�Ѵ�. 
	char buffer[100];
	vector<Node*> V;
	
	int line = 0;
	while (fgets(buffer, 50, fp) != NULL) {
		string str(buffer);  // char to string
		int devideIndex = str.find(":");
		
		string word = str.substr(0, devideIndex - 1);
		string meaning = str.substr(devideIndex + 2, str.length() - 1);
		
		void *nodeRaw = malloc(sizeof(Node));
		Node *newNode = new(nodeRaw) Node;
		
		newNode->word = word;
		newNode->meaning = meaning;
		newNode->left = NULL;
		newNode->right = NULL;
		
		V.push_back(newNode);

		memset(buffer, 0, 100);
	}
	fclose(fp);  // ���� �����͸� �ݴ´�.

	Node *root = NULL;

	int count = 0, height = 0;
	root = makeBST(V, 0, V.size() - 1, &count);
	
	cout << "\n���� ������ ��� �о����ϴ�. " << count << "���� �ܾ �ֽ��ϴ�.\n";
	
	height = getHeight(root);
	cout << "Ʈ���� ��ü ���̴� " << height << "�Դϴ�.\n";
	
	while (1) {
		string input; 
		cout << "�ܾ �Է��ϼ��� : ";
		cin >> input;
		search(root, input);
	}
	
	return 0;
}
