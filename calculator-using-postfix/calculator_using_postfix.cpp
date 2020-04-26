#include <iostream>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

/* ������ �켱������ ���ϴ� �Լ�
 * stack�� �ֻ�� �����ڰ�  ���� ���� �����ں��� �켱������ ũ�ų� ���� ��� true�� ��ȯ
 */
bool cmpPriority(char top, char next) {
	switch(top) {
		case '^': top = '3'; break;
		case '*': top = '2'; break;
		case '+': top = '1'; break;
		case '-': top = '1'; break;
		default: ;
	}
	switch(next) {
		case '^': next = '3'; break;
		case '*': next = '2'; break;
		case '+': next = '1'; break;
		case '-': next = '1'; break;
		default: ;
	}
	return top >= next;
}

int main() {
	cout << "** ����**" << '\n';
	
	while(1) {
		string expInfix, expPostfix;
		stack<char> sc;  /* ��ȯ�� ���� stack */
		stack<int> si;  /* ��꿡 ���� stack */
		
		cout << "������ �Է��ϼ��� : ";
		cin >> expInfix;
		
		/* ���� ǥ������� ��ȯ
		 * char�� ���ҷ� ������ stack ���
		 * ���� ǥ����� ó�� ���ں��� ������ ���ڱ��� ��ȸ
		 */
		for(int i = 0; i < expInfix.length(); i++) {
			char ch = expInfix.at(i);  /* string.at(i) : i��° index�� ���ڸ� ��ȯ */
			char preCh = (i == 0) ? 'x' : expInfix.at(i - 1);  /* ������ ���� */
			
			/* ������ ��� */
			if ('0' <= ch && ch <= '9') {
				expPostfix.push_back(ch);  /* ���� ǥ��Ŀ� �״�� �߰� */
				if (
					i != expInfix.length() - 1  /* �ش� ���ڰ� ���� �� ������ �ǿ����ڰ� �ƴϸ�(AND) */
					&&
					(  /* �ش� ������ ���� ���ڰ� ���ڰ� �ƴ� ���. �� ���ڸ� ���� �� */ 
						expInfix.at(i + 1) < '0'
						||
						'9' < expInfix.at(i + 1)
					)
				) {  /* ���� ���� ����� �����Ѵ�. */
					expPostfix.push_back(' ');
				}
			}
			/* �������� ��� */
			else if (ch == '+' || ch == '-' || ch == '*' || ch == '^') {
				/* (����ó��) ���� �����ڷ� ������ ��� */
				if (i == 0) {
					cout << "(!)" << expInfix
						 << "  �� ��ġ�� ������ �ֽ��ϴ�. ���ڰ� �;� �մϴ�." << "\n\n";
					goto EXIT;
				}
				/* (����ó��) ���� �������� �����ڷ� ���� �� */
				else if (i == expInfix.length() - 1) {
					cout << expInfix << "(!)"
						 << "  �� ��ġ�� ������ �ֽ��ϴ�. ���ڰ� �;� �մϴ�." << "\n\n";
					goto EXIT;
				}
				/* (����ó��) �����ڰ� �������� 2���� �پ� ���� �� */
				else if ( preCh == '+' || preCh == '-' || preCh == '*' || preCh == '^') {
					/* string.substr(i, n) : string�� i��° �ε������� n���� ���ڸ� ��ȯ�Ѵ�. */
					cout << expInfix.substr(0, i + 1) << "(!)" << expInfix.substr(i + 1, expInfix.length() - i + 1)
						 << "  �� ��ġ�� ������ �ֽ��ϴ�. ���ڰ� �;� �մϴ�." << "\n\n";
					goto EXIT;
				}
				
				while(
					!sc.empty()  /* stack�� ������� �ʰ�(AND, ��� �ִ� ���� �� ���� �ٷ� push�Ѵ�.)*/
					&&
					cmpPriority(sc.top(), ch)  /* stack�� �ֻ�� �����ڰ� ���� ���� �����ں��� �켱������ ũ�ų� ���� ���(����) */
				) {
					/* stack�� top �����ڸ� ���� ǥ��Ŀ� �߰��ϰ� pop�Ѵ�. */
					expPostfix.push_back(sc.top());
					sc.pop();
				}
				sc.push(ch);
			}
			else if (ch == '(') sc.push(ch);
			else if (ch == ')') {
				while(sc.top() != '(') {  /* stack�� �ֻ�ܿ� '('�� ���� ������ �ݺ��Ѵ�. */
					if (sc.empty()) {  /* (����ó��) '('�� �������� ���� ��, �� '(' ���� ')'�� ���� �� */
						cout << "(!)" << expInfix.substr(0, i + 1) << expInfix.substr(i + 1, expInfix.length() - i + 1)
							 << "  �� ��ġ�� ������ �ֽ��ϴ�. (�� �����մϴ�." << "\n\n";
						goto EXIT;
					}
					expPostfix.push_back(sc.top());
					sc.pop();
				}
				sc.pop();  /* '('�� pop���ش�. */
			}
		}
		
		/* ������ stack�� �� �������. */
		while(!sc.empty()) {
			if (sc.top() == '(') {  /* (����ó��) stack�� ')'�� �׿����� ��. �� '(' �� ')' ¦�� ���� ���� ��. */
				cout << expInfix << "(!)"
					 << "  �� ��ġ�� ������ �ֽ��ϴ�. )�� �����մϴ�." << "\n\n";
				goto EXIT;
			}
			expPostfix.push_back(sc.top());
			sc.pop();
		}
		cout << "���� ����: " << expPostfix << '\n';
		
		/* ���� ǥ��� ����ϱ�
		 * int�� ���ҷ� ������ stack ���
		 * ���� ǥ����� ó�� ���ں��� ������ ���ڱ��� ��ȸ
		 */
		for(int i = 0; i < expPostfix.length(); i++) {
			int num;
			int op1, op2;
			char ch = expPostfix.at(i);
			char preCh = (i == 0) ? 'x' : expPostfix.at(i - 1);
			
			/* ������ ��� */
			if ('0' <= ch && ch <= '9') {
				if (
					'0' <= preCh && preCh <= '9'  /* ������ ���ڰ� �����̰� (AND, �� �ڸ� ������ ��� ������ ���ڰ� ' '�̴�) */
					&&
					i != 0  /* ���� ù ��° ���ڰ� �ƴ� ��(���� ù ��° ���ڴ� stack�� �ٷ� push�Ѵ�) */
				) {
					si.pop();  /* ������ ���� ���ڸ� ����. */
					op1 = preCh - '0';  /* ������ ����(����)�� int�� ��ȯ�Ѵ�. */
					op2 = ch - '0';  /* ������ ����(����)�� int�� ��ȯ�Ѵ�. */
					/* �� ���� �������� ����(����)�� �� �ڸ� ���ڷ� ��ȯ�Ѵ�. 
					 * ���� ����(���� �ڸ� ��) * 10 + ���� ����(���� �ڸ� ��)
					 * �� �ڸ� ���� ��ȯ �� �� �ڸ� ���� ���� �ϰ������� ó���ϱ� ���� ���ڷ� ��ȯ�Ѵ�. 
					 */
					ch = ((op1 * 10) + op2) + '0';
				}
				num = ch - '0';  /* char -> int */
				si.push(num);
			}
			/* �������� ��� */
			else if (ch == '+' || ch == '-' || ch == '*' || ch == '^') {
				op2 = si.top();
				si.pop();
				op1 = si.top();
				si.pop();
				switch(ch) {
					case '+': si.push(op1 + op2); break;
					case '-': si.push(op1 - op2); break;
					case '*': si.push(op1 * op2); break;
					case '^': si.push(pow(op1, op2)); break;
				}
			}
		}
		cout << "= " << si.top() << "\n\n";
		
		/* ���� �߰� �� ���� ���̺�� �̵��Ͽ� while���� ���� iteration�� �����Ѵ�. */
		EXIT:;
	}
	return 0;
}
