#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>

#define MAX(x, y) (((x) >= (y)) ? (x) : (y))
#define MIN(x, y) (((x) >= (y)) ? (y) : (x))

using namespace std;

int main() {
	while(1) {
		stack<int> s1, s2;  // ����1, ����2 
		vector<int> temp1, temp2;  // �ּڰ� �Ǵ��� ���� �ӽ÷� ������ ���� �־���� vector 
		string train;  // ����ڷκ��� �޴� ���� ��ȣ 
		int trainNum,  // ���� ��ȣ string�� ���� ���� ���� ��ȣ ���ڿ��� int������ ��ȯ�Ͽ� ������ ���� 
			cnt = 0,  // �� �۾� Ƚ��
			s1Stk = 0, s2Stk = 0,  // �� ������ ���� ���緮 
			s1MaxStk = 0, s2MaxStk = 0,  // �� ������ �ִ� ���緮 
			s1Min = 99, s2Min = 99,  // �� ������ ���� ������ �ִ� �ּڰ�(������ ��� �ִ� ��� ������ �񱳸� ���� ����� ū ������ �ʱ�ȭ) 
			lastOut = 0,  // �� ���������� ���� ���� ��ȣ
			transfer;  // ȯ�¿��� ���� ���� ���� ��ȣ

		cout << "���� ��ȣ �Է� : ";
		cin >> train;

		for(int i = 0; i <= 8; i++) {  // train ���ڿ��� ��ȸ
			trainNum = train.at(i) - '0';  // ���� ��ȯ 

			cout << ++cnt << " : IN(" << trainNum << ")\n";

			/*** ������ �� ���ڰ� ������ �� ***/
			if (trainNum == lastOut + 1) {
				cout << ++cnt << " : OUT(" << trainNum << ")\n";
				++lastOut;

				/*** �߰� action ***/
				/* ���� out���� ���� ������ �� ���� ���ÿ� �ִ� ���� �ݺ� */
				while ((s1Min == lastOut + 1) || (s2Min == lastOut + 1)) {
					if (s1Min == lastOut + 1) {  // ���� 1�� �ִ� ��� 
						/* ����1�� top�� s1Min�� �� ������ ���� 2�� pop */
						while(s1.top() != s1Min) {
							transfer = s1.top();  // ����1 -> ȯ�¿� 
							s1.pop();
							cout << ++cnt << " : POP(1)\n";
							--s1Stk;
							temp1.pop_back(); 

							s2.push(transfer);  // ȯ�¿� -> ���� 2 
							cout << ++cnt << " : PUSH(2, " << transfer << ")\n";
							s2Min = MIN(s2Min, transfer);  // ���� �ּڰ� ������Ʈ
							++s2Stk;
							s2MaxStk = MAX(s2Stk, s2MaxStk);  // ���� �ִ� ���緮 ������Ʈ
							temp2.push_back(transfer);
						}
						// ���� 1 �ֻ�ܿ� out�ؾ� �� ������ ��ġ�ϰ� �ȴ�. 
						
						cout << ++cnt << " : OUT(" << s1.top() << ")\n";
						++lastOut;
						s1.pop();
						--s1Stk;
						temp1.pop_back();
						
						// ���� 1 �ּڰ� ������Ʈ
						if (s1.empty()) s1Min = 99;
						else s1Min = *min_element(temp1.begin(), temp1.end());
					}
					
					if (s2Min == lastOut + 1) {  // ���� 2�� �ִ� ��
						/* ����2�� top�� s1Min�� �� ������ ���� 1�� pop */
						while(s2.top() != s2Min) {
							transfer = s2.top();  // ����2 -> ȯ�¿� 
							s2.pop();
							cout << ++cnt << " : POP(2)\n";
							--s2Stk;
							temp2.pop_back();
							
							s1.push(transfer);  // ȯ�¿� -> ���� 1
							cout << ++cnt << " : PUSH(1, " << transfer << ")\n";
							s1Min = MIN(s1Min, transfer);  // ���� �ּڰ� ������Ʈ
							++s1Stk;
							s1MaxStk = MAX(s1Stk, s1MaxStk);  // ����2 �ִ� ���緮 ������Ʈ 
							temp1.push_back(transfer);
						}
						// ���� 2 �ֻ�ܿ� out�ؾ� �� ������ ��ġ�ϰ� �ȴ�. 
						
						cout << ++cnt << " : OUT(" << s2.top() << ")\n";
						++lastOut;
						s2.pop();
						--s2Stk;
						temp2.pop_back();
						
						// ���� 2 �ּڰ� ������Ʈ
						if (s2.empty()) s2Min = 99;
						else s2Min = *min_element(temp2.begin(), temp2.end());
					}
				}
			}
			
			/*** ���ÿ� ��ȭ�� ����(�ٷ� out�ؼ� ������ �� ���� ������ �ʾ��� ��) push�� �ϰ� ���� �� ***/
			else {
				/* (�� �� ��� �ֵ� �ϳ��� ����ֵ�) ��� �ִ� ������ ������ �� ���� push */
				if (s1.empty()) {
					s1.push(trainNum);
					cout << ++cnt << " : PUSH(1, " << trainNum << ")\n";
					s1Min = MIN(s1Min, trainNum);  // ���� �ּڰ� ������Ʈ
					++s1Stk;
					s1MaxStk = MAX(s1Stk, s1MaxStk);  // �ִ� ���緮 ������Ʈ 
					temp1.push_back(trainNum);
				} else if (s2.empty()) {
					s2.push(trainNum);
					cout << ++cnt << " : PUSH(2, " << trainNum << ")\n";
					s2Min = MIN(s2Min, trainNum);  // ���� �ּڰ� ������Ʈ
					++s2Stk;
					s2MaxStk = MAX(s2Stk, s2MaxStk);  // �ִ� ���緮 ������Ʈ 
					temp2.push_back(trainNum);
				}
				/* �� ���� ��� ������� ���� �� 
					if i < ���� 1, 2
						�� ���� ���ÿ� push
					if i < ���� 1, i > ���� 2
						���� 1�� push 
					if i < ���� 2, i > ���� 1
						���� 2�� push
					if i > ���� 1, 2 
						�� ���� ���ÿ� push */
				else {
					if (
						(trainNum < s1.top() && trainNum < s2.top())  // �� ���ú��� �۰ų� 
						||
						(trainNum > s1.top() && trainNum > s2.top())  // �� ���ú��� ũ�� 
					) {
						// �� ū ���ÿ� push 
						if (s1.top() > s2.top()) {
							s1.push(trainNum);
							cout << ++cnt << " : PUSH(1, " << trainNum << ")\n";
							s1Min = MIN(s1Min, trainNum);  // ���� �ּڰ� ������Ʈ
							++s1Stk;
							s1MaxStk = MAX(s1Stk, s1MaxStk);  // �ִ� ���緮 ������Ʈ 
							temp1.push_back(trainNum);
						} else {
							s2.push(trainNum);
							cout << ++cnt << " : PUSH(2, " << trainNum << ")\n";
							s2Min = MIN(s2Min, trainNum);  // ���� �ּڰ� ������Ʈ
							++s2Stk;
							s2MaxStk = MAX(s2Stk, s2MaxStk);  // �ִ� ���緮 ������Ʈ 
							temp2.push_back(trainNum);
						}
					}
					// ���� 1���� �۰� 2���� Ŭ �� : 1�� push 
					else if (trainNum < s1.top() && trainNum > s2.top()) {
						s1.push(trainNum);
						cout << ++cnt << " : PUSH(1, " << trainNum << ")\n";
						s1Min = MIN(s1Min, trainNum);  // ���� �ּڰ� ������Ʈ
						++s1Stk;
						s1MaxStk = MAX(s1Stk, s1MaxStk);  // �ִ� ���緮 ������Ʈ 
						temp1.push_back(trainNum);
					}
					// ���� 2���� �۰� 1���� Ŭ �� : 2�� push
					else if (trainNum > s1.top() && trainNum < s2.top()) {
						s2.push(trainNum);
						cout << ++cnt << " : PUSH(2, " << trainNum << ")\n";
						s2Min = MIN(s2Min, trainNum);  // ���� �ּڰ� ������Ʈ
						++s2Stk;
						s2MaxStk = MAX(s2Stk, s2MaxStk);  // �ִ� ���緮 ������Ʈ 
						temp2.push_back(trainNum);
					}
				}
			}
			/*** push ��, ������ ***/
		}
		// ����
		
		cout << "����(�� " << cnt << "ȸ)\n"
			 << "�ִ� ���緮 : 1�� " << s1MaxStk <<"��, 2�� " << s2MaxStk << "��\n\n";
	}
	
	return 0;
}
