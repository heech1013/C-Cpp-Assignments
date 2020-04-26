#include <stdio.h>
#include <math.h>

#define MAX_DEGREE 11
#define MAX_TEMP_DEGREE 37

typedef struct {
	int coef;
	int expon;
} polynomial;

/* 다항식의 덧셈 */
void add(polynomial *exp_1, polynomial *exp_2, polynomial *exp_3) {
	int arr_pos = 0;
	int highest_expon = (exp_1[0].expon > exp_2[0].expon) ? exp_1[0].expon : exp_2[0].expon;
	/* 두 다항식의 최고 차수부터 0까지 순회한다. */
	for(int i = highest_expon; i >= 0; i--) {
		int temp_coef = 0;
		/* 첫 번째 다항식의 첫 번째 원소부터 계수가 0이 아닌 원소까지 순회한다. */
		for(int j = 0; exp_1[j].coef != 0; j++) {
			if (j == MAX_DEGREE) break;
			/* 특정 차수의 계수를 발견하면 임시 변수에 더한다. */
			if (exp_1[j].expon == i) temp_coef += exp_1[j].coef;
		}
		/* 두 번째 다항식의 첫 번째 원소부터 계수가 0이 아닌 원소까지 순회한다. */
		for(int k = 0; exp_2[k].coef != 0; k++) {
			if (k == MAX_DEGREE) break;
			/* 특정 차수의 계수를 발견하면 임시 변수에 더한다. */
			if (exp_2[k].expon == i) temp_coef += exp_2[k].coef;
		}
		if (temp_coef) {  /* 계수가 0이 아닐 경우 */
			exp_3[arr_pos].coef = temp_coef;
			exp_3[arr_pos].expon = i;
			arr_pos++;
		}
	}
}

/* 다항식의 곱셈 */
void multiply(polynomial *exp_1, polynomial *exp_2, polynomial *exp_3) {
	/* 정돈되지 않은 곱셈 결과가 담길 임시 배열. 최대 36항(6항*6항)을 담을 수 있도록 할당한다. */
	polynomial temp_arr[MAX_TEMP_DEGREE] = {{0, 0}, };
	int arr_pos = 0;  /* 임시 배열의 첨자에 쓰일 변수 선언 */
	
	/* 다항식 1의 계수가 0이 아닐 때까지 순회한다. */
	for(int i = 0; exp_1[i].coef != 0; i++) {
		/* 다항식 2의 계수가 0이 아닐 때까지 순회한다. */
		for (int j = 0; exp_2[j].coef != 0; j++) {
			/* 두 다항식의 계수를 곱한다. */
			temp_arr[arr_pos].coef = exp_1[i].coef * exp_2[j].coef;
			/* 두 다항식의 차수를 더한다. */
			temp_arr[arr_pos].expon = exp_1[i].expon + exp_2[j].expon;
			arr_pos++;
		}
	}
	
	/* 같은 차수를 가진 여러 개의 항을 더한 후 차수 기준 내림차순으로 정렬한다. */
	arr_pos = 0;  /* 결과 다항식 배열의 첨자에 사용하기 위해 0으로 초기화한다. */
	
	/* 임시 배열의 최고 차항부터 시작하여 0까지 순회한다. */
	for(int e = temp_arr[0].expon; e >= 0; e--) {
		int temp_coef = 0;  /* 계수를 저장할 변수 */
		/* 임시배열의 첫 번째 원소부터 계수가 0인 항을 만날 때까지 순회한다. */
		for(int j = 0; temp_arr[j].coef != 0; j++) {
			/* 계수가 0인 항을 만나지 않고 배열의 크기를 넘어갈 경우 탈출해준다. */
			if (j == MAX_TEMP_DEGREE) break;
			/* 같은 차수의 항을 만날 경우 해당 항의 계수를 모두 더해준다. */
			if (temp_arr[j].expon == e) temp_coef += temp_arr[j].coef;
		}
		if (temp_coef) {  /* 계수가 0이 아닐 경우 */
			exp_3[arr_pos].coef = temp_coef;
			exp_3[arr_pos].expon = e;
			arr_pos++;
		}
	}
}

int calc(polynomial *exp, int x) {
	int i = 0;
	int result = 0;
	while(exp[i].coef != 0) {
		/* 계수가 0인 항을 만나지 않고 배열의 크기를 넘어갈 경우 탈출해준다. */
		if (i == MAX_DEGREE) break;
		result += exp[i].coef * pow(x, exp[i].expon);
		i++;
	}
	return result;
}

int main(void) {
	int term_cnt;  /* 사용자가 입력할 다항식의 항 개수  */
	
	polynomial exp_1[MAX_DEGREE] = {{0, 0}, };  /* 다항식 1 */
	polynomial exp_2[MAX_DEGREE] = {{0, 0}, };  /* 다항식 2 */
	polynomial exp_3[MAX_DEGREE] = {{0, 0}, };  /* 덧셈 결과 다항식 */
	polynomial exp_4[MAX_DEGREE] = {{0, 0}, };  /* 곱셈 결과 다항식 */
	
	printf("** 다항식의 저장방식2 **\n수식 1은 몇 개의 항으로 구성되어 있나요? : ");
	scanf("%d", &term_cnt);
	printf("수식 1을 입력하세요. : ");
	for(int i = 0; i < term_cnt; i++) {
		scanf("%d %d", &exp_1[i].coef, &exp_1[i].expon);
	}

	printf("수식 2은 몇 개의 항으로 구성되어 있나요? : ");
	scanf("%d", &term_cnt);
	printf("수식 2을 입력하세요. : ");
	for(int i = 0; i < term_cnt; i++) {
		scanf("%d %d", &exp_2[i].coef, &exp_2[i].expon);
	}
	
	add(exp_1, exp_2, exp_3);
	printf("수식 1 + 2는 ");
	for(int i = 0; exp_3[i].coef != 0; i++) {
		if (i == MAX_DEGREE) break; 
		printf("%d %d ", exp_3[i].coef, exp_3[i].expon);
	}
	printf("\n");
	
	multiply(exp_1, exp_2, exp_4);
	printf("수식 1 * 2는 ");
	for(int i = 0; exp_4[i].coef != 0; i++) {
		if (i == MAX_DEGREE) break;
		printf("%d %d ", exp_4[i].coef, exp_4[i].expon);
	}
	printf("\n");
	
	while(1) {
		int exp_num, x;
		polynomial *exp_arr[4] = {exp_1, exp_2, exp_3, exp_4};
		printf("수식에 값을 넣으세요 : ");
		scanf("%d %d", &exp_num, &x);
		printf("결과값은 %d\n", calc(exp_arr[exp_num - 1], x));
	}
	
	return 0;
}
