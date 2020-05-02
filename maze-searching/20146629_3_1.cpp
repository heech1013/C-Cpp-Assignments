#include <iostream>
#include <stack>
#include <string>

using namespace std;

// �̷θ� �����ϴ� ĭ�� ���� ������ ��� Ÿ�� 
typedef struct {
	bool up;
	bool down;
	bool left; 
	bool right;
	bool passed;  // �̹� ������ �������� ���� ���� 
	bool ans;  // ���� �� ��Ʈ������ ���� ���� 
} square;

// ������ ���ð� ����� ���ÿ� ������ ĭ�� ������ ���� Ÿ�� 
typedef struct {
	int x;
	int y;
} fork;
		
int main() {
	int x = 0, y = 0;  // ���� ��ġ 
	const int endX = 8, endY = 11;  // ��ǥ ���� 
	square pos;  // ���� ��ġ�� ���� ������ ��� �ִ� ĭ
	stack<fork> forkStk;  // �������� ��� ���� 
	stack<fork> ansStk;  // ������� ��� ���� 
	string nextDir;  // ���� ������ �濡 ���� ���� 
	int xNow, yNow;  // ���� ��ġ�� ��� ���� ���� 
	square upSqr, downSqr, leftSqr, rightSqr;
	square unavail = { up: false, down: false, left: false, right: false, passed: false, ans: false };  // ���� �Ұ����� ĭ 
	fork f;
	
	square maze[108] = {
		{ up: false, down: true, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: false, down: true, left: true, right: false, passed: false, ans: false },
		{ up: false, down: false, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: false, down: true, left: true, right: true, passed: false, ans: false },
		{ up: false, down: true, left: true, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: false, passed: false, ans: false },
		
		{ up: true, down: false, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: false, down: true, left: true, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: true, down: true, left: true, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		
		{ up: false, down: true, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: true, down: true, left: true, right: false, passed: false, ans: false },
		{ up: true, down: false, left: false, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: false, passed: false, ans: false },
		{ up: true, down: false, left: false, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: false, passed: false, ans: false },
		{ up: true, down: false, left: false, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: true, passed: false, ans: false },
		{ up: true, down: true, left: true, right: false, passed: false, ans: false },
		{ up: true, down: false, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		
		{ up: true, down: true, left: false, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: false, passed: false, ans: false },
		
		{ up: true, down: false, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: false, down: true, left: true, right: true, passed: false, ans: false },
		{ up: true, down: true, left: true, right: false, passed: false, ans: false },
		
		{ up: false, down: true, left: false, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: true, down: false, left: false, right: false, passed: false, ans: false },
		
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		{ up: true, down: false, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: false, down: true, left: true, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: true, down: false, left: false, right: true, passed: false, ans: false },
		{ up: false, down: true, left: true, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: false, down: true, left: true, right: false, passed: false, ans: false },
		
		{ up: true, down: true, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: false, down: true, left: true, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: true, passed: false, ans: false },
		{ up: false, down: true, left: true, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: false, passed: false, ans: false },
		{ up: true, down: false, left: false, right: false, passed: false, ans: false },
		{ up: false, down: true, left: false, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		
		{ up: true, down: false, left: false, right: true, passed: false, ans: false },
		{ up: false, down: true, left: true, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: true, down: true, left: false, right: false, passed: false, ans: false },
		
		{ up: false, down: false, left: false, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: true, down: false, left: false, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: true, down: false, left: false, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false },
		{ up: false, down: false, left: false, right: true, passed: false, ans: false },
		{ up: false, down: false, left: true, right: true, passed: false, ans: false },
		{ up: true, down: false, left: true, right: false, passed: false, ans: false }
	};
	
	while((x != endX) || (y != endY)) {  // ���� ��ġ�� ��ǥ ��ġ�� ��ġ���� �ʴ� ���� ��ȸ 
		nextDir.clear();
		pos = maze[x + y * 9];  // ���� ��ġ�ϰ� �ִ� ĭ 
		
		// ���� ĭ���κ��� ���� ��, �Ʒ�, ����, ������ ĭ�� ���� ������ ��´�.
		// �̷��� �ܺ��� �����ϴ� ĭ�� ��� �ܺ��� �Ѿ�� ĭ(�迭�� �ε��� ������ �Ѿ��)�� ��ȸ���� �ʵ��� ������ �̿� �Ұ����� ĭ(unavail)�� �Ҵ��Ѵ�. 
		upSqr = (y != 0) ? maze[x + (y-1) * 9] : unavail;
		downSqr = (y != 11) ? maze[x + (y+1) * 9] : unavail;
		leftSqr = (x != 0) ? maze[(x-1) + y * 9] : unavail;
		rightSqr = (x != 8) ? maze[(x+1) + y * 9] : unavail;
		
		xNow = x; yNow = y;
		
		// ���� ��ġ�� passed ǥ��
		maze[x + y*9].passed = true;
		
		// ���� ������ ���� �ִ��� Ȯ���Ѵ�. 
		if (pos.up && !upSqr.passed) {
			nextDir.push_back('u');
		}
		if (pos.down && !downSqr.passed) {
			nextDir.push_back('d');
		}
		if (pos.left && !leftSqr.passed) {
			nextDir.push_back('l');
		}
		if (pos.right && !rightSqr.passed) {
			nextDir.push_back('r');
		}
		
		// ���ٸ� ���� �ƴ϶��(�� ���� �ִٸ� ��� �ĺ��� ���� �ִ´�)
		if (!nextDir.empty()) {
			f = {x: xNow, y: yNow};  // ���� ��ġ ���� 
			ansStk.push(f);  // ���� �ִ� ��ġ�� ���������� ����� ���ÿ� PUSH 
			switch(nextDir.at(0)) {  // ù ��° ���� ������ ��� �����Ѵ�. 
				case 'u': y--; nextDir.replace(0, 1, "-"); break;
				case 'd': y++; nextDir.replace(0, 1, "-"); break;
				case 'l': x--; nextDir.replace(0, 1, "-"); break;
				case 'r': x++; nextDir.replace(0, 1, "-"); break;
				default: ;
			}
			
			// ������ ���ÿ� PUSH 
			if (nextDir.find("u") != string::npos)
				forkStk.push(f);
			if (nextDir.find("d") != string::npos)
				forkStk.push(f);
			if (nextDir.find("l") != string::npos)
				forkStk.push(f);
			if (nextDir.find("r") != string::npos)
				forkStk.push(f);
		}
		
		// ���ٸ� ���̶�� ������ ������� �̵� 
		else {
			x = forkStk.top().x;
			y = forkStk.top().y;
			while((ansStk.top().x != x) || (ansStk.top().y != y)) {
				ansStk.pop();
			}  // top�� ���ư��� (�������� �ִ�) ��ġ�� �� ������ pop 
			ansStk.pop();  // �׸��� �� �� �� pop(�ش� ��ġ�� ���� �ش� ���� ��ġ push�ϹǷ�)
			forkStk.pop();
		}
	}

	// ���� �� ǥ��
	while(!ansStk.empty()) {
		maze[ansStk.top().x + ansStk.top().y * 9].ans = true;
		ansStk.pop();
	}
	maze[107].ans = true;
	
	for(int i = 0; i < 12; i++) {
		for(int j = 0; j < 9; j++) {
			if (!maze[9 * i + j].up) cout << "+ + + ";
			else cout << "+   + ";
		}
		cout << "\n";
		for(int j = 0; j < 9; j++) {
			if (!maze[9 * i + j].left) cout << "+ ";
			else cout << "  ";
			if (maze[9 * i + j].ans) cout << "@ ";
			else cout << "  ";
			if (!maze[9 * i + j].right) cout << "+ ";
			else cout << "  ";
		}
		cout << "\n";
		for(int j = 0; j < 9; j++) {
			if (!maze[9 * i + j].left) cout << "+   ";
			else cout << "    ";
			if (!maze[9 * i + j].right) cout << "+ ";
			else cout << "  ";
		}
		cout << "\n";
		for(int j = 0; j < 9; j++) {
			if (!maze[9 * i + j].down) cout << "+ + + ";
			else cout << "+   + ";
		}
		cout << "\n";
	} 
	
	return 0;
}
