#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <utility>

#define STUDENTS_NUM 10000  // 데이터(Student) 수
#define STD_NUM_LEN 8  // 학번 길이 
#define MAX_NAME_LEN 10  // 이름의 최대 길이 
#define PHONE_NUM_LEN 11  // 전화번호의 길이 

// C++ 11
using namespace std;

typedef struct {
	string stdNum;  // 학번 
	string name;  // 이름 
	string phoneNum;  // 전화번호 
} Student;

// 두 Student 변수의 내용을 바꾸는 함수 
void swap(Student *x, Student *y) {
	Student temp=*x;
	*x=*y;
	*y=temp;
}

// 100개 당 한 개의 Student 데이터만 출력하는 함수 
void printBook(Student book[]) {
	for(int i = 0; i < 100; i++)
		cout << "stdNum: " << book[i*100].stdNum << " name: " << book[i*100].name << " phoneNum: " << book[i*100].phoneNum << "\n";
}

// 정렬용 복사 데이터를 생성하는 함수 
void bookCopy(Student from[], Student to[]) {
	for(int i = 0; i < STUDENTS_NUM; i++) 
		to[i] = from[i];
}

// 선택 정렬(학번순) 
void stdNumSelectionSort(Student copy[], int left, int right) {
	int max;
	for(int i = left; i < right; i++) {
		max = i;
		for(int j = i+1; j <= right; j++) {
			if(copy[j].stdNum > copy[max].stdNum) max = j;
		}
		swap(copy+i, copy+max);
	}
}

// 선택 정렬(이름순) 
void nameSelectionSort(Student copy[], int left, int right) {
	int max;
	for(int i = left; i < right; i++) {
		max = i;
		for(int j = i+1; j <= right; j++) {
			if(copy[j].name > copy[max].name) max = j;
		}
		swap(copy+i, copy+max);
	}
}

// 퀵 정렬용 파티션(학번순) 
int stdNumPartition(Student copy[], int left, int right) {
	string pivot;
	int high, low;
	
	high = left;
	low = right+1;
	pivot = copy[left].stdNum;
	do {
		do high++;
		while (high <= right && copy[high].stdNum > pivot);
		do low--;
		while (low >= left && copy[low].stdNum < pivot);
		
		if (high < low) swap(copy+high, copy+low);
	} while(high < low);
	
	swap(copy+left, copy+low);
	return low;
}

// 퀵 정렬(학번순) 
void stdNumQuickSort(Student copy[], int left, int right) {
	if(left < right) {
		int pivot = stdNumPartition(copy, left, right);
		stdNumQuickSort(copy, left, pivot-1);
		stdNumQuickSort(copy, pivot+1, right);
	}
}

// 퀵 정렬용 파티션(이름순) 
int namePartition(Student copy[], int left, int right) {
	string pivot;
	int high, low;
	
	high = left;
	low = right+1;
	pivot = copy[left].name;
	do {
		do high++;
		while (high <= right && copy[high].name > pivot);
		do low--;
		while (low >= left && copy[low].name < pivot);
		
		if (high < low) swap(copy+high, copy+low);
	} while(high < low);
	
	swap(copy+left, copy+low);
	return low;
}

// 퀵 정렬용(이름순) 
void nameQuickSort(Student copy[], int left, int right) {
	if(left < right) {
		int pivot = namePartition(copy, left, right);
		nameQuickSort(copy, left, pivot-1);
		nameQuickSort(copy, pivot+1, right);
	}
}

// 비재귀 퀵 정렬(학번순) 
void stdNumNonRucurQuickSort(Student copy[], int left, int right) {
	stack<pair<int, int> > s;
	pair<int, int> p;
	p = make_pair(left, right);
	s.push(p);
	while(!s.empty()) {
		p = s.top();
		int pivot = stdNumPartition(copy, p.first, p.second);
		s.pop();
		
		if (pivot - p.first < 10) {
			// 선택 정렬 
			stdNumSelectionSort(copy, p.first, pivot-1);
		} else {
			s.push(make_pair(p.first, pivot-1));
		}
		
		if (p.second - pivot < 10) {
			// 선택 정렬 
			stdNumSelectionSort(copy, pivot+1, p.second);
		} else {
			s.push(make_pair(pivot+1, p.second));
		}
	}
	
}

// 비재귀 퀵 정렬(이름순) 
void nameNonRucurQuickSort(Student copy[], int left, int right) {
	stack<pair<int, int> > s;
	pair<int, int> p;
	p = make_pair(left, right);
	s.push(p);
	while(!s.empty()) {
		p = s.top();
		int pivot = namePartition(copy, p.first, p.second);
		s.pop();
		
		if (pivot - p.first < 10) {
			// 선택 정렬 
			nameSelectionSort(copy, p.first, pivot-1);
		} else {
			s.push(make_pair(p.first, pivot-1));
		}
		
		if (p.second - pivot < 10) {
			// 선택 정렬 
			nameSelectionSort(copy, pivot+1, p.second);
		} else {
			s.push(make_pair(pivot+1, p.second));
		}
	}
	
}

// 힙 정렬용 heapify(학번순)
void stdNumAdjust(Student copy[], int root, int n) {
	Student rootkey;
	int child;
	rootkey = copy[root];
	child = 2 * root + 1;  // 왼쪽 child로 내려가기 
	while(child <= n-2) {  // 인덱스가 원소 개수-1(: 인덱스) -1(뒤에 한 개는 더 있어야함)
		if ((child < n) && (copy[child].stdNum > copy[child+1].stdNum))
			child++;  // 오른쪽 child로 옮겨가기 
		if (rootkey.stdNum < copy[child].stdNum)
			break;
		else {
			if (child%2 == 0)  // 짝수: 오른쪽 child에서 parent로 올라가기 
				copy[(child /2)-1] = copy[child];
			else   // 홀수: 왼쪽child에서 parent로 올라가기 
				copy[child /2] = copy[child];
			child = child * 2 + 1;   // 왼쪽 child로 내려가기 
		}
	}
	if (child%2 == 0)  // 짝수: 오른쪽 child에서 parent로 올라가기 
		copy[(child /2)-1] = rootkey;
	else    // 홀수: 왼쪽child에서 parent로 올라가기 
		copy[child /2] = rootkey;
}

// 힙 정렬(학번순) 
void stdNumHeapSort(Student copy[]) {
	for(int i = (STUDENTS_NUM/2)-1; i >= 0; i--) {
		stdNumAdjust(copy, i, STUDENTS_NUM);
	}
	for(int i = STUDENTS_NUM-1; i > 0; i--) {
		swap(copy[0], copy[i]);
		stdNumAdjust(copy, 0, i);
	}
}

// 힙 정렬용 heapify(이름순)
void nameAdjust(Student copy[], int root, int n) {
	Student rootkey;
	int child;
	rootkey = copy[root];
	child = 2 * root + 1;
	while(child <= n-2) {
		if ((child < n) && (copy[child].name > copy[child+1].name))
			child++; 
		if (rootkey.name < copy[child].name)
			break;
		else {
			if (child%2 == 0)  
				copy[(child /2)-1] = copy[child];
			else  
				copy[child /2] = copy[child];
			child = child * 2 + 1;
		}
	}
	if (child%2 == 0)
		copy[(child /2)-1] = rootkey;
	else 
		copy[child /2] = rootkey;
}

// 힙 정렬(이름순) 
void nameHeapSort(Student copy[]) {
	for(int i = (STUDENTS_NUM/2)-1; i >= 0; i--) {
		stdNumAdjust(copy, i, STUDENTS_NUM);
	}
	for(int i = STUDENTS_NUM-1; i > 0; i--) {
		swap(copy[0], copy[i]);
		stdNumAdjust(copy, 0, i);
	}
}

// C++ 내부 정렬(학번순) 알고리즘용 비교함수 
bool stdNumCompare(Student a, Student b) {
	return a.stdNum > b.stdNum;
}

// C++ 내부 정렬(이름순) 알고리즘용 비교함수 
bool nameNumCompare(Student a, Student b) {
	return a.name > b.name;
}

int main() {
	Student book[STUDENTS_NUM];  // 최초 생성되는 랜덤 원본 데이터 배열
	Student copy[STUDENTS_NUM];  // 정렬용으로 복사될 데이터 배열
	bool randDic[7][STUDENTS_NUM] = { false, };  // 같은 학번이 존재하지 않도록 이미 생성된 학번을 기록하는 딕셔너리용 배열 
	Student student;
	string stdNum, name, phoneNum;
	int randNameLen;  // 랜덤으로 생성되는 이름의 길이를 담는 변수 
	char rc;  // 랜덤으로 생성되는 문자를 담는 변수 
	int rn;  // 랜덤으로 생성되는 숫자를 담는 변수 
	bool flag; 
	clock_t start, end;  // 실행시간 측정에 쓰일 변수 
		
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
		
		book[i] = { stdNum: stdNum, name: name, phoneNum: phoneNum };
	}
	
	cout << "\n[정렬되지 않은 랜덤 학생 데이터 10000개 생성] (100명 당 1개만 출력)\n";
	printBook(book);
	
	cout << "\n과제(1) 선택 정렬/퀵 정렬/힙 정렬\n";
	
	bookCopy(book, copy);
	start = clock();
	stdNumSelectionSort(copy, 0, STUDENTS_NUM);
	end = clock();
	cout << "\n선택 정렬(학번순) 수행 (걸린 시간: " << (float)(end - start)/CLOCKS_PER_SEC << "초)\n";
	printBook(copy);
	
	bookCopy(book, copy);
	start = clock();
	stdNumQuickSort(copy, 0, STUDENTS_NUM-1);
	end = clock();
	cout << "\n퀵 정렬(학번순) 수행 (걸린 시간: " << (float)(end - start)/CLOCKS_PER_SEC << "초)\n";
	printBook(copy);
	
	bookCopy(book, copy);
	start = clock();
	stdNumHeapSort(copy);
	end = clock();
	cout << "\n힙 정렬(학번순) 수행 (걸린 시간: " << (float)(end - start)/CLOCKS_PER_SEC << "초)\n";
	printBook(copy);
	
	bookCopy(book, copy);
	start = clock();
	nameSelectionSort(copy, 0, STUDENTS_NUM);
	end = clock();
	cout << "\n선택 정렬(이름순) 수행 (걸린 시간: " << (float)(end - start)/CLOCKS_PER_SEC << "초)\n";
	printBook(copy);
	
	bookCopy(book, copy);
	start = clock();
	nameQuickSort(copy, 0, STUDENTS_NUM-1);
	end = clock();
	cout << "\n퀵 정렬(이름순) 수행 (걸린 시간: " << (float)(end - start)/CLOCKS_PER_SEC << "초)\n";
	printBook(copy);
	
	bookCopy(book, copy);
	start = clock();
	nameHeapSort(copy);
	end = clock();
	cout << "\n힙 정렬(이름순) 수행 (걸린 시간: " << (float)(end - start)/CLOCKS_PER_SEC << "초)\n";
	printBook(copy);
	
	cout << "\n과제(2) 퀵 정렬의 비재귀 호출 버전\n";
	
	bookCopy(book, copy);
	start = clock();
	stdNumNonRucurQuickSort(copy, 0, STUDENTS_NUM-1);
	end = clock();
	cout << "\n비재귀 퀵 정렬(학번순) 수행 (걸린 시간: " << (float)(end - start)/CLOCKS_PER_SEC << "초)\n";
	printBook(copy);

	bookCopy(book, copy);
	start = clock();
	nameNonRucurQuickSort(copy, 0, STUDENTS_NUM-1);
	end = clock();
	cout << "\n비재귀 퀵 정렬(이름순) 수행 (걸린 시간: " << (float)(end - start)/CLOCKS_PER_SEC << "초)\n";
	printBook(copy);
	
	cout << "\n과제(3) 내장된 정렬 방법과 비교하기\n";
	
	bookCopy(book, copy);
	start = clock();
	sort(copy, copy+STUDENTS_NUM-1, stdNumCompare);  // C++ 내부 정렬 함수 
	end = clock();
	cout << "\nC++ 내부 정렬(학번순) 수행 (걸린 시간: " << (float)(end - start)/CLOCKS_PER_SEC << "초)\n";
	printBook(copy);
	
	bookCopy(book, copy);
	start = clock();
	sort(copy, copy+STUDENTS_NUM-1, nameNumCompare);  // C++ 내부 정렬 함수 
	end = clock();
	cout << "\nC++ 내부 정렬(이름순) 수행 (걸린 시간: " << (float)(end - start)/CLOCKS_PER_SEC << "초)\n";
	printBook(copy);
	
	return 0;
}
