 #include <cstdlib>
 #include <iostream>
 #include <string>
 #include <stack>
 
 using namespace std;
 
 typedef struct Node {
 	char data;
 	Node *left, *right, *up;
 } Node;
 
 /* 연산자 우선순위를 비교하는 함수
 * stack의 최상단 연산자가  새로 들어온 연산자보다 우선순위가 크거나 같을 경우 true를 반환
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
 	// root 설정 (= 후위식의 가장 마지막 문자: 연산자) 
 	Node *root = (Node *)malloc(sizeof(Node));
 	root->data = *(expr.end() - 1);
 	root->up = NULL;  // root임을 나타내는 단서가 된다. 
 	root->left = NULL;
 	root->right = NULL;
 	
 	// 현재 위치를 가리키는 포인터
	Node *curr = root;
 	
 	for (int i = expr.length() - 2; i >= 0; i--) {
 		// 오른쪽, 왼쪽 자식이 모두 차있을 경우 자식 노드가 모두 차있지 않은 부모노드까지 올라간다. 
 		while ((curr->left != NULL) && (curr->right != NULL)) {
			curr = curr->up;
		};
		
 		// 새로운 노드를 생성한다.
		Node *newNode = (Node *)malloc(sizeof(Node));
		newNode->data = expr[i];
		newNode->up = curr;
		newNode->left = NULL;
		newNode->right = NULL;

 		// 오른쪽 자식 노드가 비어있을 경우 오른쪽 자식 노드에 추가한다. 
 		if (curr->right == NULL) {
 			curr->right = newNode;
			// op일 경우 해당 노드 아래에 계속해서 노드를 매달아야 하므로 curr를 이동시킨다. 
			if (expr[i] == '*' || expr[i] == '/' || expr[i] == '+' || expr[i] == '-') {
				curr = curr->right;
			}
			// op가 아닐 경우 curr는 그대로 같은 노드를 가리킨다. 
		}
		// 오른쪽 자식은 차있고 왼쪽 자식 노드가 비어있을 경우 왼쪽 자식 노드에 추가한다. 
		else if (curr->left == NULL) {
			curr->left = newNode;
			// op일 경우 해당 노드 아래에 계속해서 노드를 매달아야 하므로 curr를 이동시킨다. 
			if (expr[i] == '*' || expr[i] == '/' || expr[i] == '+' || expr[i] == '-') {
				curr = curr->left;
			}
			// op가 아닐 경우 curr는 그대로 같은 노드를 가리킨다. 
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
 	cout << "수식을 입력하세요 : ";
 	cin >> infix;
 	
 	// 중위 표기법 -> 후위 표기법
	postfix = toPostfix(infix);
	
 	Node *root = exprBST(postfix);
 	
 	cout << "\n전위 순회 : ";
 	printPrefix(root);
 	cout << "\n중위 순회 : "; 
 	printInfix(root);
 	cout << "\n후위 순회 : "; 
 	printPostfix(root);
 	
 	return 0;
 }
