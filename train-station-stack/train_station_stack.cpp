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
		stack<int> s1, s2;  // 스택1, 스택2 
		vector<int> temp1, temp2;  // 최솟값 판단을 위해 임시로 스택의 값을 넣어놓는 vector 
		string train;  // 사용자로부터 받는 열차 번호 
		int trainNum,  // 열차 번호 string의 현재 순서 열차 번호 문자열을 int형으로 변환하여 보관할 변수 
			cnt = 0,  // 총 작업 횟수
			s1Stk = 0, s2Stk = 0,  // 각 스택의 현재 적재량 
			s1MaxStk = 0, s2MaxStk = 0,  // 각 스택의 최대 적재량 
			s1Min = 99, s2Min = 99,  // 각 스택이 현재 가지고 있는 최솟값(스택이 비어 있는 경우 추후의 비교를 위해 충분히 큰 값으로 초기화) 
			lastOut = 0,  // 맨 마지막으로 나간 열차 번호
			transfer;  // 환승역에 정차 중인 열차 번호

		cout << "열차 번호 입력 : ";
		cin >> train;

		for(int i = 0; i <= 8; i++) {  // train 문자열을 순회
			trainNum = train.at(i) - '0';  // 숫자 변환 

			cout << ++cnt << " : IN(" << trainNum << ")\n";

			/*** 나가야 할 숫자가 들어왔을 때 ***/
			if (trainNum == lastOut + 1) {
				cout << ++cnt << " : OUT(" << trainNum << ")\n";
				++lastOut;

				/*** 추가 action ***/
				/* 직전 out으로 인해 나가야 할 값이 스택에 있는 동안 반복 */
				while ((s1Min == lastOut + 1) || (s2Min == lastOut + 1)) {
					if (s1Min == lastOut + 1) {  // 스택 1에 있는 경우 
						/* 스택1의 top이 s1Min이 될 때까지 스택 2로 pop */
						while(s1.top() != s1Min) {
							transfer = s1.top();  // 스택1 -> 환승역 
							s1.pop();
							cout << ++cnt << " : POP(1)\n";
							--s1Stk;
							temp1.pop_back(); 

							s2.push(transfer);  // 환승역 -> 스택 2 
							cout << ++cnt << " : PUSH(2, " << transfer << ")\n";
							s2Min = MIN(s2Min, transfer);  // 스택 최솟값 업데이트
							++s2Stk;
							s2MaxStk = MAX(s2Stk, s2MaxStk);  // 스택 최대 적재량 업데이트
							temp2.push_back(transfer);
						}
						// 스택 1 최상단에 out해야 할 열차가 위치하게 된다. 
						
						cout << ++cnt << " : OUT(" << s1.top() << ")\n";
						++lastOut;
						s1.pop();
						--s1Stk;
						temp1.pop_back();
						
						// 스택 1 최솟값 업데이트
						if (s1.empty()) s1Min = 99;
						else s1Min = *min_element(temp1.begin(), temp1.end());
					}
					
					if (s2Min == lastOut + 1) {  // 스택 2에 있는 경
						/* 스택2의 top이 s1Min이 될 때까지 스택 1로 pop */
						while(s2.top() != s2Min) {
							transfer = s2.top();  // 스택2 -> 환승역 
							s2.pop();
							cout << ++cnt << " : POP(2)\n";
							--s2Stk;
							temp2.pop_back();
							
							s1.push(transfer);  // 환승역 -> 스택 1
							cout << ++cnt << " : PUSH(1, " << transfer << ")\n";
							s1Min = MIN(s1Min, transfer);  // 스택 최솟값 업데이트
							++s1Stk;
							s1MaxStk = MAX(s1Stk, s1MaxStk);  // 스택2 최대 적재량 업데이트 
							temp1.push_back(transfer);
						}
						// 스택 2 최상단에 out해야 할 열차가 위치하게 된다. 
						
						cout << ++cnt << " : OUT(" << s2.top() << ")\n";
						++lastOut;
						s2.pop();
						--s2Stk;
						temp2.pop_back();
						
						// 스택 2 최솟값 업데이트
						if (s2.empty()) s2Min = 99;
						else s2Min = *min_element(temp2.begin(), temp2.end());
					}
				}
			}
			
			/*** 스택에 변화가 없어(바로 out해서 나가야 할 수가 들어오지 않았을 때) push만 하고 끝낼 때 ***/
			else {
				/* (둘 다 비어 있든 하나만 비어있든) 비어 있는 스택이 있으면 그 곳에 push */
				if (s1.empty()) {
					s1.push(trainNum);
					cout << ++cnt << " : PUSH(1, " << trainNum << ")\n";
					s1Min = MIN(s1Min, trainNum);  // 스택 최솟값 업데이트
					++s1Stk;
					s1MaxStk = MAX(s1Stk, s1MaxStk);  // 최대 적재량 업데이트 
					temp1.push_back(trainNum);
				} else if (s2.empty()) {
					s2.push(trainNum);
					cout << ++cnt << " : PUSH(2, " << trainNum << ")\n";
					s2Min = MIN(s2Min, trainNum);  // 스택 최솟값 업데이트
					++s2Stk;
					s2MaxStk = MAX(s2Stk, s2MaxStk);  // 최대 적재량 업데이트 
					temp2.push_back(trainNum);
				}
				/* 두 스택 모두 비어있지 않을 때 
					if i < 스택 1, 2
						더 높은 스택에 push
					if i < 스택 1, i > 스택 2
						스택 1에 push 
					if i < 스택 2, i > 스택 1
						스택 2에 push
					if i > 스택 1, 2 
						더 높은 스택에 push */
				else {
					if (
						(trainNum < s1.top() && trainNum < s2.top())  // 두 스택보다 작거나 
						||
						(trainNum > s1.top() && trainNum > s2.top())  // 두 스택보다 크면 
					) {
						// 더 큰 스택에 push 
						if (s1.top() > s2.top()) {
							s1.push(trainNum);
							cout << ++cnt << " : PUSH(1, " << trainNum << ")\n";
							s1Min = MIN(s1Min, trainNum);  // 스택 최솟값 업데이트
							++s1Stk;
							s1MaxStk = MAX(s1Stk, s1MaxStk);  // 최대 적재량 업데이트 
							temp1.push_back(trainNum);
						} else {
							s2.push(trainNum);
							cout << ++cnt << " : PUSH(2, " << trainNum << ")\n";
							s2Min = MIN(s2Min, trainNum);  // 스택 최솟값 업데이트
							++s2Stk;
							s2MaxStk = MAX(s2Stk, s2MaxStk);  // 최대 적재량 업데이트 
							temp2.push_back(trainNum);
						}
					}
					// 스택 1보단 작고 2보단 클 때 : 1에 push 
					else if (trainNum < s1.top() && trainNum > s2.top()) {
						s1.push(trainNum);
						cout << ++cnt << " : PUSH(1, " << trainNum << ")\n";
						s1Min = MIN(s1Min, trainNum);  // 스택 최솟값 업데이트
						++s1Stk;
						s1MaxStk = MAX(s1Stk, s1MaxStk);  // 최대 적재량 업데이트 
						temp1.push_back(trainNum);
					}
					// 스택 2보단 작고 1보단 클 때 : 2에 push
					else if (trainNum > s1.top() && trainNum < s2.top()) {
						s2.push(trainNum);
						cout << ++cnt << " : PUSH(2, " << trainNum << ")\n";
						s2Min = MIN(s2Min, trainNum);  // 스택 최솟값 업데이트
						++s2Stk;
						s2MaxStk = MAX(s2Stk, s2MaxStk);  // 최대 적재량 업데이트 
						temp2.push_back(trainNum);
					}
				}
			}
			/*** push 끝, 마무리 ***/
		}
		// 종료
		
		cout << "종료(총 " << cnt << "회)\n"
			 << "최대 적재량 : 1번 " << s1MaxStk <<"대, 2번 " << s2MaxStk << "대\n\n";
	}
	
	return 0;
}
