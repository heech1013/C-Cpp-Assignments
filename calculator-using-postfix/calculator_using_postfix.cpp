#include <iostream>
#include <string>
#include <stack>
#include <cmath>

using namespace std;

/* 연산자 우선순위를 비교하는 함수
 * stack의 최상단 연산자가  새로 들어온 연산자보다 우선순위가 크거나 같을 경우 true를 반환
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
	cout << "** 계산기**" << '\n';
	
	while(1) {
		string expInfix, expPostfix;
		stack<char> sc;  /* 변환에 쓰일 stack */
		stack<int> si;  /* 계산에 쓰일 stack */
		
		cout << "계산식을 입력하세요 : ";
		cin >> expInfix;
		
		/* 후위 표기법으로 변환
		 * char를 원소로 가지는 stack 사용
		 * 중위 표기식의 처음 문자부터 마지막 문자까지 순회
		 */
		for(int i = 0; i < expInfix.length(); i++) {
			char ch = expInfix.at(i);  /* string.at(i) : i번째 index의 문자를 반환 */
			char preCh = (i == 0) ? 'x' : expInfix.at(i - 1);  /* 직전의 문자 */
			
			/* 숫자일 경우 */
			if ('0' <= ch && ch <= '9') {
				expPostfix.push_back(ch);  /* 후위 표기식에 그대로 추가 */
				if (
					i != expInfix.length() - 1  /* 해당 숫자가 식의 맨 마지막 피연산자가 아니며(AND) */
					&&
					(  /* 해당 숫자의 다음 문자가 숫자가 아닐 경우. 즉 한자리 수일 때 */ 
						expInfix.at(i + 1) < '0'
						||
						'9' < expInfix.at(i + 1)
					)
				) {  /* 수의 끝을 띄어쓰기로 구분한다. */
					expPostfix.push_back(' ');
				}
			}
			/* 연산자일 경우 */
			else if (ch == '+' || ch == '-' || ch == '*' || ch == '^') {
				/* (오류처리) 식이 연산자로 시작할 경우 */
				if (i == 0) {
					cout << "(!)" << expInfix
						 << "  이 위치에 오류가 있습니다. 숫자가 와야 합니다." << "\n\n";
					goto EXIT;
				}
				/* (오류처리) 식의 마지막이 연산자로 끝날 때 */
				else if (i == expInfix.length() - 1) {
					cout << expInfix << "(!)"
						 << "  이 위치에 오류가 있습니다. 숫자가 와야 합니다." << "\n\n";
					goto EXIT;
				}
				/* (오류처리) 연산자가 연속으로 2개가 붙어 있을 때 */
				else if ( preCh == '+' || preCh == '-' || preCh == '*' || preCh == '^') {
					/* string.substr(i, n) : string의 i번째 인덱스에서 n개의 문자를 반환한다. */
					cout << expInfix.substr(0, i + 1) << "(!)" << expInfix.substr(i + 1, expInfix.length() - i + 1)
						 << "  이 위치에 오류가 있습니다. 숫자가 와야 합니다." << "\n\n";
					goto EXIT;
				}
				
				while(
					!sc.empty()  /* stack이 비어있지 않고(AND, 비어 있는 경우는 비교 없이 바로 push한다.)*/
					&&
					cmpPriority(sc.top(), ch)  /* stack의 최상단 연산자가 새로 들어온 연산자보다 우선순위가 크거나 같을 경우(동안) */
				) {
					/* stack의 top 연산자를 후위 표기식에 추가하고 pop한다. */
					expPostfix.push_back(sc.top());
					sc.pop();
				}
				sc.push(ch);
			}
			else if (ch == '(') sc.push(ch);
			else if (ch == ')') {
				while(sc.top() != '(') {  /* stack의 최상단에 '('가 나올 때까지 반복한다. */
					if (sc.empty()) {  /* (오류처리) '('이 존재하지 않을 때, 즉 '(' 없이 ')'만 썼을 때 */
						cout << "(!)" << expInfix.substr(0, i + 1) << expInfix.substr(i + 1, expInfix.length() - i + 1)
							 << "  이 위치에 오류가 있습니다. (가 부족합니다." << "\n\n";
						goto EXIT;
					}
					expPostfix.push_back(sc.top());
					sc.pop();
				}
				sc.pop();  /* '('를 pop해준다. */
			}
		}
		
		/* 나머지 stack을 다 비워낸다. */
		while(!sc.empty()) {
			if (sc.top() == '(') {  /* (오류처리) stack에 ')'가 쌓여있을 때. 즉 '(' 과 ')' 짝이 맞지 않을 때. */
				cout << expInfix << "(!)"
					 << "  이 위치에 오류가 있습니다. )가 부족합니다." << "\n\n";
				goto EXIT;
			}
			expPostfix.push_back(sc.top());
			sc.pop();
		}
		cout << "후위 계산식: " << expPostfix << '\n';
		
		/* 후위 표기식 계산하기
		 * int를 원소로 가지는 stack 사용
		 * 후위 표기식의 처음 문자부터 마지막 문자까지 순회
		 */
		for(int i = 0; i < expPostfix.length(); i++) {
			int num;
			int op1, op2;
			char ch = expPostfix.at(i);
			char preCh = (i == 0) ? 'x' : expPostfix.at(i - 1);
			
			/* 숫자일 경우 */
			if ('0' <= ch && ch <= '9') {
				if (
					'0' <= preCh && preCh <= '9'  /* 직전의 문자가 숫자이고 (AND, 한 자리 숫자의 경우 직전의 문자가 ' '이다) */
					&&
					i != 0  /* 식의 첫 번째 숫자가 아닐 때(식의 첫 번째 숫자는 stack에 바로 push한다) */
				) {
					si.pop();  /* 직전에 넣은 숫자를 뺀다. */
					op1 = preCh - '0';  /* 직전의 문자(숫자)를 int로 변환한다. */
					op2 = ch - '0';  /* 현재의 문자(숫자)를 int로 변환한다. */
					/* 두 개의 독립적인 문자(숫자)를 두 자리 숫자로 변환한다. 
					 * 직전 숫자(십의 자리 수) * 10 + 현재 숫자(일의 자리 수)
					 * 두 자리 숫자 변환 후 한 자리 수의 경우와 일괄적으로 처리하기 위해 문자로 변환한다. 
					 */
					ch = ((op1 * 10) + op2) + '0';
				}
				num = ch - '0';  /* char -> int */
				si.push(num);
			}
			/* 연산자일 경우 */
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
		
		/* 오류 발견 시 현재 레이블로 이동하여 while문의 다음 iteration을 진행한다. */
		EXIT:;
	}
	return 0;
}
