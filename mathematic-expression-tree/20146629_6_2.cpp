 #include <cstdlib>
 #include <iostream>
 #include <string>
 #include <stack>
 
 using namespace std;
 
 typedef struct Node {
 	char data;
 	Node *left, *right, *up;
 } Node;
 
 /* ������ �켱������ ���ϴ� �Լ�
 * stack�� �ֻ�� �����ڰ�  ���� ���� �����ں��� �켱������ ũ�ų� ���� ��� true�� ��ȯ
 */
bool cmpPriority(char top, char next) {
	switch(top) {
		case '*': top = '2'; break;
		case '/': top = '2'; break;
		case '+': top = '1'; break;
		case '-': top = '1'; break;
		default: ;
	}
	switch(next) {
		case '*': next = '2'; break;
		case '/': next = '2'; break;
		case '+': next = '1'; break;
		case '-': next = '1'; break;
		default: ;
	}
	return top >= next;
}
 
 string toPostfix(string expr) {
 	string postfix = "";
 	stack<char> S;
 	for (int i = 0; i < expr.length(); i++) {
 		char c = expr[i];
 		if (c == '*' || c == '/' || c == '+' || c == '-') {
 			while (
 				!S.empty()
				&&
				cmpPriority(S.top(), c)
			) {
 				postfix.push_back(S.top());
 				S.pop();
			}
			S.push(c);
		}
		else {
			postfix.push_back(c);
		}
	}
	while (!S.empty()) {
		postfix.push_back(S.top());
		S.pop();
	}
	return postfix;
 }
 
 Node *exprBST(string expr) {
 	// root ���� (= �������� ���� ������ ����: ������) 
 	Node *root = (Node *)malloc(sizeof(Node));
 	root->data = *(expr.end() - 1);
 	root->up = NULL;  // root���� ��Ÿ���� �ܼ��� �ȴ�. 
 	root->left = NULL;
 	root->right = NULL;
 	
 	// ���� ��ġ�� ����Ű�� ������
	Node *curr = root;
 	
 	for (int i = expr.length() - 2; i >= 0; i--) {
 		// ������, ���� �ڽ��� ��� ������ ��� �ڽ� ��尡 ��� ������ ���� �θ������ �ö󰣴�. 
 		while ((curr->left != NULL) && (curr->right != NULL)) {
			curr = curr->up;
		};
		
 		// ���ο� ��带 �����Ѵ�.
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->data = expr[i];
		newNode->up = curr;
		newNode->left = NULL;
		newNode->right = NULL;

 		// ������ �ڽ� ��尡 ������� ��� ������ �ڽ� ��忡 �߰��Ѵ�. 
 		if (curr->right == NULL) {
 			curr->right = newNode;
			// op�� ��� �ش� ��� �Ʒ��� ����ؼ� ��带 �Ŵ޾ƾ� �ϹǷ� curr�� �̵���Ų��. 
			if (expr[i] == '*' || expr[i] == '/' || expr[i] == '+' || expr[i] == '-') {
				curr = curr->right;
			}
			// op�� �ƴ� ��� curr�� �״�� ���� ��带 ����Ų��. 
		}
		// ������ �ڽ��� ���ְ� ���� �ڽ� ��尡 ������� ��� ���� �ڽ� ��忡 �߰��Ѵ�. 
		else if (curr->left == NULL) {
			curr->left = newNode;
			// op�� ��� �ش� ��� �Ʒ��� ����ؼ� ��带 �Ŵ޾ƾ� �ϹǷ� curr�� �̵���Ų��. 
			if (expr[i] == '*' || expr[i] == '/' || expr[i] == '+' || expr[i] == '-') {
				curr = curr->left;
			}
			// op�� �ƴ� ��� curr�� �״�� ���� ��带 ����Ų��. 
		}
	}
	
	return root;
 }
 
 void printPrefix(Node *node) {
 	if (node != NULL) {
 		cout << node->data << " ";
 		printPrefix(node->left);
 		printPrefix(node->right);
	}
 }
 
 void printInfix(Node *node) {
 	if (node != NULL) {
 		printInfix(node->left);
 		cout << node->data << " ";
 		printInfix(node->right);
	}
 }
 
 void printPostfix(Node *node) {
 	if (node != NULL) {
 		printPostfix(node->left);
 		printPostfix(node->right);
 		cout << node->data << " ";
	}
 }
 
 int main() {
 	string infix, postfix;
 	cout << "������ �Է��ϼ��� : ";
 	cin >> infix;
 	
 	// ���� ǥ��� -> ���� ǥ���
	postfix = toPostfix(infix);
	
 	Node *root = exprBST(postfix);
 	
 	cout << "\n���� ��ȸ : ";
 	printPrefix(root);
 	cout << "\n���� ��ȸ : "; 
 	printInfix(root);
 	cout << "\n���� ��ȸ : "; 
 	printPostfix(root);
 	
 	return 0;
 }
