#include <iostream>
#include <stack>
#include <string>

using namespace std;

// 미로를 구성하는 칸에 대한 정보를 담는 타입 
typedef struct {
	bool up;
	bool down;
	bool left; 
	bool right;
	bool passed;  // 이미 지나온 길인지에 대한 여부 
	bool ans;  // 정답 길 루트인지에 대한 여부 
} square;

// 갈림길 스택과 정답길 스택에 저장할 칸의 정보를 위한 타입 
typedef struct {
	int x;
	int y;
} fork;
		
int main() {
	int x = 0, y = 0;  // 현재 위치 
	const int endX = 8, endY = 11;  // 목표 지점 
	square pos;  // 현재 위치에 대한 정보를 담고 있는 칸
	stack<fork> forkStk;  // 갈림길을 담는 스택 
	stack<fork> ansStk;  // 정답길을 담는 스택 
	string nextDir;  // 입장 가능한 길에 대한 정보 
	int xNow, yNow;  // 현재 위치를 담기 위한 변수 
	square upSqr, downSqr, leftSqr, rightSqr;
	square unavail = { up: false, down: false, left: false, right: false, passed: false, ans: false };  // 입장 불가능한 칸 
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
	
	while((x != endX) || (y != endY)) {  // 현재 위치가 목표 위치와 일치하지 않는 동안 순회 
		nextDir.clear();
		pos = maze[x + y * 9];  // 현재 위치하고 있는 칸 
		
		// 현재 칸으로부터 각각 위, 아래, 왼쪽, 오른쪽 칸에 대한 정보를 담는다.
		// 미로의 외벽을 구성하는 칸의 경우 외벽을 넘어서는 칸(배열의 인덱스 범위를 넘어선다)을 조회하지 않도록 별도의 이용 불가능한 칸(unavail)을 할당한다. 
		upSqr = (y != 0) ? maze[x + (y-1) * 9] : unavail;
		downSqr = (y != 11) ? maze[x + (y+1) * 9] : unavail;
		leftSqr = (x != 0) ? maze[(x-1) + y * 9] : unavail;
		rightSqr = (x != 8) ? maze[(x+1) + y * 9] : unavail;
		
		xNow = x; yNow = y;
		
		// 현재 위치는 passed 표시
		maze[x + y*9].passed = true;
		
		// 입장 가능한 길이 있는지 확인한다. 
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
		
		// 막다른 길이 아니라면(갈 길이 있다면 모두 후보에 집어 넣는다)
		if (!nextDir.empty()) {
			f = {x: xNow, y: yNow};  // 현재 위치 정보 
			ansStk.push(f);  // 내가 있는 위치를 지속적으로 정답길 스택에 PUSH 
			switch(nextDir.at(0)) {  // 첫 번째 입장 가능한 길로 입장한다. 
				case 'u': y--; nextDir.replace(0, 1, "-"); break;
				case 'd': y++; nextDir.replace(0, 1, "-"); break;
				case 'l': x--; nextDir.replace(0, 1, "-"); break;
				case 'r': x++; nextDir.replace(0, 1, "-"); break;
				default: ;
			}
			
			// 갈림길 스택에 PUSH 
			if (nextDir.find("u") != string::npos)
				forkStk.push(f);
			if (nextDir.find("d") != string::npos)
				forkStk.push(f);
			if (nextDir.find("l") != string::npos)
				forkStk.push(f);
			if (nextDir.find("r") != string::npos)
				forkStk.push(f);
		}
		
		// 막다른 길이라면 직전의 갈림길로 이동 
		else {
			x = forkStk.top().x;
			y = forkStk.top().y;
			while((ansStk.top().x != x) || (ansStk.top().y != y)) {
				ansStk.pop();
			}  // top이 돌아가는 (갈림길이 있는) 위치가 될 때까지 pop 
			ansStk.pop();  // 그리고 한 번 더 pop(해당 위치에 가서 해당 현재 위치 push하므로)
			forkStk.pop();
		}
	}

	// 정답 길 표시
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
