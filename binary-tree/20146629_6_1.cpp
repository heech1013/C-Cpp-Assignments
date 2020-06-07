#include <cstdlib>  // malloc()
#include <cstring>  // to_string()
#include <ctime>  // 난수 생성을 위한 rand() 사용 
#include <iostream>
#include <string>

#define STUDENTS_NUM 10000
#define STD_NUM_LEN 8
#define MAX_NAME_LEN 10
#define PHONE_NUM_LEN 11

using namespace std;

typedef struct Node {
	int num;
	string stdNum;
	string name;
	string phoneNum;
	Node *left, *right;
} Node;

void insertNode(Node **head, Node* newNode) {
	Node *p, *t;  // p는 부모노드, t는 현재 노드
	t = *head;
	p = NULL;
	// 탐색 수행
	while (t != NULL) {
		p = t;
		if (newNode->stdNum < t->stdNum)
			t = t->left;
		else
			t = t->right;
	}
	// 부모 노드와 연결 
	if (p != NULL) {
		if (newNode->stdNum < p->stdNum)
			p->left = newNode;
		else
			p->right = newNode;
	}
	// 첫 번째 노드일 경우
	else
		*head = newNode;
}

void inorderLabeling(Node *node, int *num) {
	if (node != NULL) {
		inorderLabeling(node->left, num);
		node->num = (*num)++;
		inorderLabeling(node->right, num);
	}
}

// 중위 순회
void inorderPrint(Node *node) {
	if (node != NULL) {
		inorderPrint(node->left);
		if ((node->num) % 100 == 0)
			cout << node->stdNum << " " << node->name << " " << node->phoneNum << "\n";
		inorderPrint(node->right);
	}
}

void numPrint(Node *node, int num) {
	if (node->num == num)
		cout << node->num << ". " << node->stdNum << " " << node->name << " " << node->phoneNum << "\n";
	else {
		if (node->num < num)
			numPrint(node->right, num);
		else
			numPrint(node->left, num);
	}
}

int main() {
	bool randDic[7][STUDENTS_NUM] = { false, };  // 같은 학번이 존재하지 않도록 이미 생성된 학번을 기록하는 딕셔너리용 배열 
	string stdNum, name, phoneNum;
	int randNameLen;  // 랜덤으로 생성되는 이름의 길이를 담는 변수 
	char rc;  // 랜덤으로 생성되는 문자를 담는 변수 
	int rn;  // 랜덤으로 생성되는 숫자를 담는 변수 
	bool flag;
	Node *curr;
	
	// 헤더 노드 선언 
	Node *head;
	
	srand((unsigned int)time(0));  // random 함수에 쓰일 난수를 현재 시간을 활용하여 설정한다. 
	
	// 10000개의 데이터 생성 
	for(int i = 0; i < STUDENTS_NUM; i++) {
		// 학번 
		stdNum = "201";
		rc = (rand() % 7 + 3) + '0' ;  // '3' ~ '9' 사이의 수를 생성 
		stdNum.push_back(rc);
		flag = true;  // flag가 false가 될 경우 적합한 랜덤 학번 조건에 부합하는 것이다. 
		do {  // 학번 뒤에 붙일 4자리 숫자를 랜덤으로 생성한다. 
			rn = rand() % STUDENTS_NUM;
			if (rn > 999)  // 수는 4자리여야 한다. 
				flag = randDic[rc-'0'-3][rn];  // 이미 생성된 학번과 중복일 경우 flag는 true, 중복이 아닐 경우 false가 된다. 
		} while(flag);  // 중복되지 않는 학번이 생길 경우 반복문을 빠져나간다. 
		randDic[rc-'0'-3][rn] = true;  // 생성된 학번을 딕셔너리에 기록한다. 
		stdNum += to_string(rn);
		
		// 이름
		name = "";
		randNameLen = (rand() % (MAX_NAME_LEN)) + 1;  // 랜덤으로 이름의 길이를 결정한다. (1자리 ~ 10자리)
		for(int j = 0; j < randNameLen; j++) {
			rc = 'a' + (rand() % 26);  // 난수에 따라 'a' ~ 'z' 사이의 문자가 랜덤으로 결정된다. 
			name.push_back(rc);
		}
		
		// 전화번호 
		phoneNum = "010";
		for(int j = 0; j < PHONE_NUM_LEN - 3; j++) {
			rn = rand() % 10;
			rc = rn + '0';  // 난수에 따라 '0' ~ '9' 사이의 문자가 랜덤으로 결정된다. 
			phoneNum.push_back(rc);
		}
		
		void *nodeRaw = malloc(sizeof(Node));
		Node *newNode = new(nodeRaw) Node;
	
		newNode->stdNum.replace(0, stdNum.length(), stdNum);
		newNode->name.replace(0, name.length(), name);
		newNode->phoneNum.replace(0, phoneNum.length(), phoneNum);
		newNode->left = NULL;
		newNode->right = NULL;
		
		// 이진 트리 삽입 
		insertNode(&head, newNode);
	}
	
	// 순번 붙이기
	int num = 1;
	inorderLabeling(head, &num);
	
	// 100명당 1명 출력하기
	inorderPrint(head);
	
	while (1) {
		int num;
		cout << "\n순번을 입력하세요 > ";
		cin >> num;
		numPrint(head, num);
	}
	
	return 0;
}
