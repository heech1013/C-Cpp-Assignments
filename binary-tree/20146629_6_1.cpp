#include <cstdlib>  // malloc()
#include <cstring>  // to_string()
#include <ctime>  // ���� ������ ���� rand() ��� 
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
	Node *p, *t;  // p�� �θ���, t�� ���� ���
	t = *head;
	p = NULL;
	// Ž�� ����
	while (t != NULL) {
		p = t;
		if (newNode->stdNum < t->stdNum)
			t = t->left;
		else
			t = t->right;
	}
	// �θ� ���� ���� 
	if (p != NULL) {
		if (newNode->stdNum < p->stdNum)
			p->left = newNode;
		else
			p->right = newNode;
	}
	// ù ��° ����� ���
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

// ���� ��ȸ
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
	bool randDic[7][STUDENTS_NUM] = { false, };  // ���� �й��� �������� �ʵ��� �̹� ������ �й��� ����ϴ� ��ųʸ��� �迭 
	string stdNum, name, phoneNum;
	int randNameLen;  // �������� �����Ǵ� �̸��� ���̸� ��� ���� 
	char rc;  // �������� �����Ǵ� ���ڸ� ��� ���� 
	int rn;  // �������� �����Ǵ� ���ڸ� ��� ���� 
	bool flag;
	Node *curr;
	
	// ��� ��� ���� 
	Node *head;
	
	srand((unsigned int)time(0));  // random �Լ��� ���� ������ ���� �ð��� Ȱ���Ͽ� �����Ѵ�. 
	
	// 10000���� ������ ���� 
	for(int i = 0; i < STUDENTS_NUM; i++) {
		// �й� 
		stdNum = "201";
		rc = (rand() % 7 + 3) + '0' ;  // '3' ~ '9' ������ ���� ���� 
		stdNum.push_back(rc);
		flag = true;  // flag�� false�� �� ��� ������ ���� �й� ���ǿ� �����ϴ� ���̴�. 
		do {  // �й� �ڿ� ���� 4�ڸ� ���ڸ� �������� �����Ѵ�. 
			rn = rand() % STUDENTS_NUM;
			if (rn > 999)  // ���� 4�ڸ����� �Ѵ�. 
				flag = randDic[rc-'0'-3][rn];  // �̹� ������ �й��� �ߺ��� ��� flag�� true, �ߺ��� �ƴ� ��� false�� �ȴ�. 
		} while(flag);  // �ߺ����� �ʴ� �й��� ���� ��� �ݺ����� ����������. 
		randDic[rc-'0'-3][rn] = true;  // ������ �й��� ��ųʸ��� ����Ѵ�. 
		stdNum += to_string(rn);
		
		// �̸�
		name = "";
		randNameLen = (rand() % (MAX_NAME_LEN)) + 1;  // �������� �̸��� ���̸� �����Ѵ�. (1�ڸ� ~ 10�ڸ�)
		for(int j = 0; j < randNameLen; j++) {
			rc = 'a' + (rand() % 26);  // ������ ���� 'a' ~ 'z' ������ ���ڰ� �������� �����ȴ�. 
			name.push_back(rc);
		}
		
		// ��ȭ��ȣ 
		phoneNum = "010";
		for(int j = 0; j < PHONE_NUM_LEN - 3; j++) {
			rn = rand() % 10;
			rc = rn + '0';  // ������ ���� '0' ~ '9' ������ ���ڰ� �������� �����ȴ�. 
			phoneNum.push_back(rc);
		}
		
		void *nodeRaw = malloc(sizeof(Node));
		Node *newNode = new(nodeRaw) Node;
	
		newNode->stdNum.replace(0, stdNum.length(), stdNum);
		newNode->name.replace(0, name.length(), name);
		newNode->phoneNum.replace(0, phoneNum.length(), phoneNum);
		newNode->left = NULL;
		newNode->right = NULL;
		
		// ���� Ʈ�� ���� 
		insertNode(&head, newNode);
	}
	
	// ���� ���̱�
	int num = 1;
	inorderLabeling(head, &num);
	
	// 100��� 1�� ����ϱ�
	inorderPrint(head);
	
	while (1) {
		int num;
		cout << "\n������ �Է��ϼ��� > ";
		cin >> num;
		numPrint(head, num);
	}
	
	return 0;
}
