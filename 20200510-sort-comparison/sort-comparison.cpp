#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#include <utility>

#define STUDENTS_NUM 10000  // ������(Student) ��
#define STD_NUM_LEN 8  // �й� ���� 
#define MAX_NAME_LEN 10  // �̸��� �ִ� ���� 
#define PHONE_NUM_LEN 11  // ��ȭ��ȣ�� ���� 

// C++ 11
using namespace std;

typedef struct {
	string stdNum;  // �й� 
	string name;  // �̸� 
	string phoneNum;  // ��ȭ��ȣ 
} Student;

// �� Student ������ ������ �ٲٴ� �Լ� 
void swap(Student *x, Student *y) {
	Student temp=*x;
	*x=*y;
	*y=temp;
}

// 100�� �� �� ���� Student �����͸� ����ϴ� �Լ� 
void printBook(Student book[]) {
	for(int i = 0; i < 100; i++)
		cout << "stdNum: " << book[i*100].stdNum << " name: " << book[i*100].name << " phoneNum: " << book[i*100].phoneNum << "\n";
}

// ���Ŀ� ���� �����͸� �����ϴ� �Լ� 
void bookCopy(Student from[], Student to[]) {
	for(int i = 0; i < STUDENTS_NUM; i++) 
		to[i] = from[i];
}

// ���� ����(�й���) 
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

// ���� ����(�̸���) 
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

// �� ���Ŀ� ��Ƽ��(�й���) 
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

// �� ����(�й���) 
void stdNumQuickSort(Student copy[], int left, int right) {
	if(left < right) {
		int pivot = stdNumPartition(copy, left, right);
		stdNumQuickSort(copy, left, pivot-1);
		stdNumQuickSort(copy, pivot+1, right);
	}
}

// �� ���Ŀ� ��Ƽ��(�̸���) 
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

// �� ���Ŀ�(�̸���) 
void nameQuickSort(Student copy[], int left, int right) {
	if(left < right) {
		int pivot = namePartition(copy, left, right);
		nameQuickSort(copy, left, pivot-1);
		nameQuickSort(copy, pivot+1, right);
	}
}

// ����� �� ����(�й���) 
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
			// ���� ���� 
			stdNumSelectionSort(copy, p.first, pivot-1);
		} else {
			s.push(make_pair(p.first, pivot-1));
		}
		
		if (p.second - pivot < 10) {
			// ���� ���� 
			stdNumSelectionSort(copy, pivot+1, p.second);
		} else {
			s.push(make_pair(pivot+1, p.second));
		}
	}
	
}

// ����� �� ����(�̸���) 
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
			// ���� ���� 
			nameSelectionSort(copy, p.first, pivot-1);
		} else {
			s.push(make_pair(p.first, pivot-1));
		}
		
		if (p.second - pivot < 10) {
			// ���� ���� 
			nameSelectionSort(copy, pivot+1, p.second);
		} else {
			s.push(make_pair(pivot+1, p.second));
		}
	}
	
}

// �� ���Ŀ� heapify(�й���)
void stdNumAdjust(Student copy[], int root, int n) {
	Student rootkey;
	int child;
	rootkey = copy[root];
	child = 2 * root + 1;  // ���� child�� �������� 
	while(child <= n-2) {  // �ε����� ���� ����-1(: �ε���) -1(�ڿ� �� ���� �� �־����)
		if ((child < n) && (copy[child].stdNum > copy[child+1].stdNum))
			child++;  // ������ child�� �Űܰ��� 
		if (rootkey.stdNum < copy[child].stdNum)
			break;
		else {
			if (child%2 == 0)  // ¦��: ������ child���� parent�� �ö󰡱� 
				copy[(child /2)-1] = copy[child];
			else   // Ȧ��: ����child���� parent�� �ö󰡱� 
				copy[child /2] = copy[child];
			child = child * 2 + 1;   // ���� child�� �������� 
		}
	}
	if (child%2 == 0)  // ¦��: ������ child���� parent�� �ö󰡱� 
		copy[(child /2)-1] = rootkey;
	else    // Ȧ��: ����child���� parent�� �ö󰡱� 
		copy[child /2] = rootkey;
}

// �� ����(�й���) 
void stdNumHeapSort(Student copy[]) {
	for(int i = (STUDENTS_NUM/2)-1; i >= 0; i--) {
		stdNumAdjust(copy, i, STUDENTS_NUM);
	}
	for(int i = STUDENTS_NUM-1; i > 0; i--) {
		swap(copy[0], copy[i]);
		stdNumAdjust(copy, 0, i);
	}
}

// �� ���Ŀ� heapify(�̸���)
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

// �� ����(�̸���) 
void nameHeapSort(Student copy[]) {
	for(int i = (STUDENTS_NUM/2)-1; i >= 0; i--) {
		stdNumAdjust(copy, i, STUDENTS_NUM);
	}
	for(int i = STUDENTS_NUM-1; i > 0; i--) {
		swap(copy[0], copy[i]);
		stdNumAdjust(copy, 0, i);
	}
}

// C++ ���� ����(�й���) �˰���� ���Լ� 
bool stdNumCompare(Student a, Student b) {
	return a.stdNum > b.stdNum;
}

// C++ ���� ����(�̸���) �˰���� ���Լ� 
bool nameNumCompare(Student a, Student b) {
	return a.name > b.name;
}

int main() {
	Student book[STUDENTS_NUM];  // ���� �����Ǵ� ���� ���� ������ �迭
	Student copy[STUDENTS_NUM];  // ���Ŀ����� ����� ������ �迭
	bool randDic[7][STUDENTS_NUM] = { false, };  // ���� �й��� �������� �ʵ��� �̹� ������ �й��� ����ϴ� ��ųʸ��� �迭 
	Student student;
	string stdNum, name, phoneNum;
	int randNameLen;  // �������� �����Ǵ� �̸��� ���̸� ��� ���� 
	char rc;  // �������� �����Ǵ� ���ڸ� ��� ���� 
	int rn;  // �������� �����Ǵ� ���ڸ� ��� ���� 
	bool flag; 
	clock_t start, end;  // ����ð� ������ ���� ���� 
		
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
		
		book[i] = { stdNum: stdNum, name: name, phoneNum: phoneNum };
	}
	
	cout << "\n[���ĵ��� ���� ���� �л� ������ 10000�� ����] (100�� �� 1���� ���)\n";
	printBook(book);
	
	cout << "\n����(1) ���� ����/�� ����/�� ����\n";
	
	bookCopy(book, copy);
	start = clock();
	stdNumSelectionSort(copy, 0, STUDENTS_NUM);
	end = clock();
	cout << "\n���� ����(�й���) ���� (�ɸ� �ð�: " << (float)(end - start)/CLOCKS_PER_SEC << "��)\n";
	printBook(copy);
	
	bookCopy(book, copy);
	start = clock();
	stdNumQuickSort(copy, 0, STUDENTS_NUM-1);
	end = clock();
	cout << "\n�� ����(�й���) ���� (�ɸ� �ð�: " << (float)(end - start)/CLOCKS_PER_SEC << "��)\n";
	printBook(copy);
	
	bookCopy(book, copy);
	start = clock();
	stdNumHeapSort(copy);
	end = clock();
	cout << "\n�� ����(�й���) ���� (�ɸ� �ð�: " << (float)(end - start)/CLOCKS_PER_SEC << "��)\n";
	printBook(copy);
	
	bookCopy(book, copy);
	start = clock();
	nameSelectionSort(copy, 0, STUDENTS_NUM);
	end = clock();
	cout << "\n���� ����(�̸���) ���� (�ɸ� �ð�: " << (float)(end - start)/CLOCKS_PER_SEC << "��)\n";
	printBook(copy);
	
	bookCopy(book, copy);
	start = clock();
	nameQuickSort(copy, 0, STUDENTS_NUM-1);
	end = clock();
	cout << "\n�� ����(�̸���) ���� (�ɸ� �ð�: " << (float)(end - start)/CLOCKS_PER_SEC << "��)\n";
	printBook(copy);
	
	bookCopy(book, copy);
	start = clock();
	nameHeapSort(copy);
	end = clock();
	cout << "\n�� ����(�̸���) ���� (�ɸ� �ð�: " << (float)(end - start)/CLOCKS_PER_SEC << "��)\n";
	printBook(copy);
	
	cout << "\n����(2) �� ������ ����� ȣ�� ����\n";
	
	bookCopy(book, copy);
	start = clock();
	stdNumNonRucurQuickSort(copy, 0, STUDENTS_NUM-1);
	end = clock();
	cout << "\n����� �� ����(�й���) ���� (�ɸ� �ð�: " << (float)(end - start)/CLOCKS_PER_SEC << "��)\n";
	printBook(copy);

	bookCopy(book, copy);
	start = clock();
	nameNonRucurQuickSort(copy, 0, STUDENTS_NUM-1);
	end = clock();
	cout << "\n����� �� ����(�̸���) ���� (�ɸ� �ð�: " << (float)(end - start)/CLOCKS_PER_SEC << "��)\n";
	printBook(copy);
	
	cout << "\n����(3) ����� ���� ����� ���ϱ�\n";
	
	bookCopy(book, copy);
	start = clock();
	sort(copy, copy+STUDENTS_NUM-1, stdNumCompare);  // C++ ���� ���� �Լ� 
	end = clock();
	cout << "\nC++ ���� ����(�й���) ���� (�ɸ� �ð�: " << (float)(end - start)/CLOCKS_PER_SEC << "��)\n";
	printBook(copy);
	
	bookCopy(book, copy);
	start = clock();
	sort(copy, copy+STUDENTS_NUM-1, nameNumCompare);  // C++ ���� ���� �Լ� 
	end = clock();
	cout << "\nC++ ���� ����(�̸���) ���� (�ɸ� �ð�: " << (float)(end - start)/CLOCKS_PER_SEC << "��)\n";
	printBook(copy);
	
	return 0;
}
