#include <stdio.h>
#include <math.h>

#define MAX_DEGREE 11
#define MAX_TEMP_DEGREE 73

typedef struct {
	int expon;  /* 다항식의 최대 차수 */
	int coef[MAX_DEGREE];  /* 다항식의 계수 */
} polynomial;

/* 임시로 담은 사용자의 입력을 저장 방식에 맞게 변환하여 저장한다. */
void format(int *arr, polynomial *exp, int cnt) {
	int index;
	exp->expon = arr[1];
	for(int i = 0; i < cnt; i++) {
		/* 다항식의 차수에 맞는 배열의 인덱스를 계산하여 해당 위치에 계수를 저장한다. */
		index = (exp->expon) - arr[(i * 2) + 1];
		exp->coef[index] = arr[i * 2];
	}
}

/* 사용자의 입력 방식에 맞게 변환하여 출력한다. */
void print(polynomial *exp) {
	int expon_pos = exp->expon;
	for(int i = 0; i < exp->expon + 1; i++) {
		if (exp->coef[i] != 0) {  /* 계수가 0인 항을 제외하고 출력한다. */
			printf("%d ", exp->coef[i]);
			printf("%d ", expon_pos);
		}
		expon_pos--;
	}
	printf("%c", '\n');
}

/* 다항식의 덧셈 */
void add(polynomial *exp_1, polynomial *exp_2, polynomial *exp_3) {
	int dif = (exp_1->expon) - (exp_2->expon);  /* 두 다항식의 차수를 비교한다. */ 
	/* exp_1의 차수가 더 클 경우 */
	if (dif > 0) {
		exp_3->expon = exp_1->expon;
		/* 큰 차수를 별도의 계산 없이 모두 exp_3에 저장한다. */
		for(int i = 0; i < dif; i++) {
			exp_3->coef[i] = exp_1->coef[i];	
		}
		/* 차수에 맞게 계수를 더한다. */
		for(int i = 0; i < exp_3->expon + 1 - dif; i++) {
			exp_3->coef[dif + i] = exp_1->coef[dif + i] + exp_2->coef[i];
		}
	}
	/* exp_2의 차수가 더 클 경우 */
	else if (dif < 0) {
		exp_3->expon = exp_2->expon;
		/* 큰 차수를 별도의 계산 없이 모두 exp_3에 저장한다. */
		for(int i = 0; i < -dif; i++) {
			exp_3->coef[i] = exp_2->coef[i];
		}
		/* 차수에 맞게 계수를 더한다. */
		for(int i = 0; i < exp_3->expon + 1 + dif; i++) {
			exp_3->coef[-dif + i] = exp_1->coef[-dif + i] + exp_2->coef[i];
		}
	}
	/* 두 다항식의 차수가 같을 경우 */
	else {
		exp_3->expon = exp_1->expon;
		for(int i = 0; i < exp_3->expon + 1; i++) {
			exp_3->coef[dif + i] = exp_1->coef[dif + i] + exp_2->coef[i];
		}
	}
}

/* 다항식의 곱셈 */
void multiply(polynomial *exp_1, polynomial *exp_2, polynomial *exp_3) {
	int temp_arr[MAX_TEMP_DEGREE];  /* 곱셈 결과 다항식의 계수와 차수가 함께 담길 배열 */
	int arr_pos = 0;
	int expon_pos_1 = exp_1->expon;  /* 현재 순회 중인 다항식 1의 차수를 확인하기 위한 변수 */
	/* 다항식 1의 모든 항을 순회(0부터 최고차수까지) */
	for(int i = 0; i < exp_1->expon + 1; i++) {
		int expon_pos_2 = exp_2->expon;  /* 현재 순회 중인 다항식 2의 차수를 확인하기 위한 변수 */
		/* 다항식 2의 모든 항을 순회(0부터 최고차수까지) */
		for (int j = 0; j < exp_2->expon + 1; j++) {
			/* 두 다항식의 각각의 항의 계수를 곱한 후 임시 배열에 담는다. */
			temp_arr[arr_pos] = exp_1->coef[i] * exp_2->coef[j];
			arr_pos++;
			/* 두 다항식의 각각의 항의 차수를 더한 후 임시 배열에 담는다. */
			temp_arr[arr_pos] = expon_pos_1 + expon_pos_2;
			expon_pos_2--;
			arr_pos++;
		}
		expon_pos_1--;
	}
	/* 순회 후 arr_pos는 temp_arr(임시 배열)의 원소 개수를 담고 있다. */

	exp_3->expon = exp_1->expon + exp_2->expon;
	/* exp_3의 최고차수부터 0까지 순회 */
	for(int e = exp_3->expon; e >= 0; e--) {
		int temp_coef = 0;  /* 특정 차수에 해당하는 계수를 모두 더할 변수 */
		/* 임시배열을 한 pair(원소 2개 : 계수와 차수)씩 순회 */
		for(int p = 0; p < arr_pos; p += 2) {
			if (temp_arr[p + 1] == e) {  /* 특정 차수와 임시 배열이 담고 있는 차수가 같을 때 */
				temp_coef += temp_arr[p];  /* 임시 배열의 계수를 담는다. */
			}
		}
		exp_3->coef[exp_3->expon - e] = temp_coef;
	}
}

int calc(polynomial *exp, int x) {
	int result = 0;
	for(int i = 0; i < exp->expon + 1; i++) {
		result += exp->coef[i] * pow(x, exp->expon - i);
	}
	return result;
}

int main(void) {
	int term_cnt;  /* 사용자가 입력할 다항식의 항 개수  */
	int temp_arr[13];  /* 사용자가 입력한 다항식을 임시로 보관하는 배열 */

	polynomial exp_1 = {0, {0, }};  /* 다항식 1 */
	polynomial exp_2 = {0, {0, }};  /* 다항식 2 */
	polynomial exp_3 = {0, {0, }};  /* 덧셈 결과 다항식 */
	polynomial exp_4 = {0, {0, }};  /* 곱셈 결과 다항식 */
	
	printf("** 다항식의 저장방식1 **\n수식 1은 몇 개의 항으로 구성되어 있나요? : ");
	scanf("%d", &term_cnt);
	printf("수식 1을 입력하세요 : ");
	for(int i = 0; i < term_cnt * 2; i++) {  /* 계수와 차수를 저장하기 위해 (항 개수 * 2)만큼 반복한다. */
		scanf("%d", temp_arr + i);
	}
	format(temp_arr, &exp_1, term_cnt);
	
	printf("수식 2는 몇 개의 항으로 구성되어 있나요? : ");
	scanf("%d", &term_cnt);
	printf("수식 2를 입력하세요 : ");
	for(int i = 0; i < term_cnt * 2; i++) {
		scanf("%d", temp_arr + i);
	}
	format(temp_arr, &exp_2, term_cnt);
	
	add(&exp_1, &exp_2, &exp_3);
	printf("수식 1 + 2는 : ");
	print(&exp_3);
	
	multiply(&exp_1, &exp_2, &exp_4);
	printf("수식 1 * 2는 : ");
	print(&exp_4);
	
	while(1) {
		int exp_num, x;
		polynomial *exp_arr[4] = {&exp_1, &exp_2, &exp_3, &exp_4};
		printf("수식에 값을 넣으세요 : ");
		scanf("%d %d", &exp_num, &x);
		printf("결과값은 %d\n", calc(exp_arr[exp_num - 1], x));
	}

	return 0;
}
