#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#define MAX_QUEUE_SIZE 20

using namespace std;

typedef struct {
	int front;
	int rear;
	char queueArr[MAX_QUEUE_SIZE];
} Queue;

int isEmpty(Queue *q) {
	return (q->front == q->rear);
}

int isFull(Queue *q) {
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}

int enqueue(Queue *q, char item) {
	if (isFull(q)) {
		cout << "ENQUEUE(" << item << ") Fail : Queue Full  F=" << q->front << " R=" << q->rear << "\n";
		return 0;
	}
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queueArr[q->rear] = item;
	cout << "ENQUEUE(" << item << ")  F=" << q->front << " R=" << q->rear << "\n";
	return 1;
}

char dequeue(Queue *q) {
	if (isEmpty(q)) {
		cout << "DEQUEUE( ) Fail : Queue Empty  F=" << q->front << " R=" << q->rear << "\n";
		return '0';
	}
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	cout << "DNQUEUE( ) = " << q->queueArr[q->front] << "  F=" << q->front << " R=" << q->rear << "\n";
	return q->queueArr[q->front];
}

void queueRemain(Queue *q) {
	string s = "";
	int n = 0;
	
	for(int i = (q->front + 1) % MAX_QUEUE_SIZE; i != (q->rear + 1) % MAX_QUEUE_SIZE; i = (i + 1) % MAX_QUEUE_SIZE) {
		char str = q->queueArr[i];
		s.push_back(q->queueArr[i]);
		n++;
	}
	
	cout << "QUEUE = " << s << "(" << n << ")\n";
}

int main() {
	Queue q = { front: 0, rear: 0, queueArr: { 0, }};
	string input;
	vector<char> deqVec;
	int enqFlag, deqNum;
	char deqChar;
	
	cout << "**입력 큐 프로그램**\n";
	while(1) {
		cout << "\n문자나 숫자를 입력하세요(문자: 큐에 문자 입력 / 숫자: 큐에서 숫자만큼 문자 빼오기)\n>>> ";
		cin >> input;
		deqNum = atoi(input.c_str());
//		deqNum = isdigit(input.at(0)) ? input.at(0) - '0' : 0;
		deqVec.clear();
		
		// enqueue
		if (!deqNum) {
			for(unsigned int i = 0; i < input.size(); i++) {
				enqFlag = enqueue(&q, input.at(i));
				if (!enqFlag) break;
			}
		}
		// dequeue
		else {
			for(int i = 0; i < deqNum; i++) {
				deqChar = dequeue(&q);
				if (deqChar == '0') break;
				deqVec.push_back(deqChar);
			}
			cout << "RESULT = ";
			for(unsigned int i = 0; i < deqVec.size(); i++) {
				cout << deqVec.at(i);
			}
			cout << "\n";
			queueRemain(&q);
		}
	}
	
	return 0;
}

