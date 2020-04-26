#include <stdio.h>
#include <math.h>

#define MAX_DEGREE 11
#define MAX_TEMP_DEGREE 37

typedef struct {
	int coef;
	int expon;
} polynomial;

/* ���׽��� ���� */
void add(polynomial *exp_1, polynomial *exp_2, polynomial *exp_3) {
	int arr_pos = 0;
	int highest_expon = (exp_1[0].expon > exp_2[0].expon) ? exp_1[0].expon : exp_2[0].expon;
	/* �� ���׽��� �ְ� �������� 0���� ��ȸ�Ѵ�. */
	for(int i = highest_expon; i >= 0; i--) {
		int temp_coef = 0;
		/* ù ��° ���׽��� ù ��° ���Һ��� ����� 0�� �ƴ� ���ұ��� ��ȸ�Ѵ�. */
		for(int j = 0; exp_1[j].coef != 0; j++) {
			if (j == MAX_DEGREE) break;
			/* Ư�� ������ ����� �߰��ϸ� �ӽ� ������ ���Ѵ�. */
			if (exp_1[j].expon == i) temp_coef += exp_1[j].coef;
		}
		/* �� ��° ���׽��� ù ��° ���Һ��� ����� 0�� �ƴ� ���ұ��� ��ȸ�Ѵ�. */
		for(int k = 0; exp_2[k].coef != 0; k++) {
			if (k == MAX_DEGREE) break;
			/* Ư�� ������ ����� �߰��ϸ� �ӽ� ������ ���Ѵ�. */
			if (exp_2[k].expon == i) temp_coef += exp_2[k].coef;
		}
		if (temp_coef) {  /* ����� 0�� �ƴ� ��� */
			exp_3[arr_pos].coef = temp_coef;
			exp_3[arr_pos].expon = i;
			arr_pos++;
		}
	}
}

/* ���׽��� ���� */
void multiply(polynomial *exp_1, polynomial *exp_2, polynomial *exp_3) {
	/* �������� ���� ���� ����� ��� �ӽ� �迭. �ִ� 36��(6��*6��)�� ���� �� �ֵ��� �Ҵ��Ѵ�. */
	polynomial temp_arr[MAX_TEMP_DEGREE] = {{0, 0}, };
	int arr_pos = 0;  /* �ӽ� �迭�� ÷�ڿ� ���� ���� ���� */
	
	/* ���׽� 1�� ����� 0�� �ƴ� ������ ��ȸ�Ѵ�. */
	for(int i = 0; exp_1[i].coef != 0; i++) {
		/* ���׽� 2�� ����� 0�� �ƴ� ������ ��ȸ�Ѵ�. */
		for (int j = 0; exp_2[j].coef != 0; j++) {
			/* �� ���׽��� ����� ���Ѵ�. */
			temp_arr[arr_pos].coef = exp_1[i].coef * exp_2[j].coef;
			/* �� ���׽��� ������ ���Ѵ�. */
			temp_arr[arr_pos].expon = exp_1[i].expon + exp_2[j].expon;
			arr_pos++;
		}
	}
	
	/* ���� ������ ���� ���� ���� ���� ���� �� ���� ���� ������������ �����Ѵ�. */
	arr_pos = 0;  /* ��� ���׽� �迭�� ÷�ڿ� ����ϱ� ���� 0���� �ʱ�ȭ�Ѵ�. */
	
	/* �ӽ� �迭�� �ְ� ���׺��� �����Ͽ� 0���� ��ȸ�Ѵ�. */
	for(int e = temp_arr[0].expon; e >= 0; e--) {
		int temp_coef = 0;  /* ����� ������ ���� */
		/* �ӽù迭�� ù ��° ���Һ��� ����� 0�� ���� ���� ������ ��ȸ�Ѵ�. */
		for(int j = 0; temp_arr[j].coef != 0; j++) {
			/* ����� 0�� ���� ������ �ʰ� �迭�� ũ�⸦ �Ѿ ��� Ż�����ش�. */
			if (j == MAX_TEMP_DEGREE) break;
			/* ���� ������ ���� ���� ��� �ش� ���� ����� ��� �����ش�. */
			if (temp_arr[j].expon == e) temp_coef += temp_arr[j].coef;
		}
		if (temp_coef) {  /* ����� 0�� �ƴ� ��� */
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
		/* ����� 0�� ���� ������ �ʰ� �迭�� ũ�⸦ �Ѿ ��� Ż�����ش�. */
		if (i == MAX_DEGREE) break;
		result += exp[i].coef * pow(x, exp[i].expon);
		i++;
	}
	return result;
}

int main(void) {
	int term_cnt;  /* ����ڰ� �Է��� ���׽��� �� ����  */
	
	polynomial exp_1[MAX_DEGREE] = {{0, 0}, };  /* ���׽� 1 */
	polynomial exp_2[MAX_DEGREE] = {{0, 0}, };  /* ���׽� 2 */
	polynomial exp_3[MAX_DEGREE] = {{0, 0}, };  /* ���� ��� ���׽� */
	polynomial exp_4[MAX_DEGREE] = {{0, 0}, };  /* ���� ��� ���׽� */
	
	printf("** ���׽��� ������2 **\n���� 1�� �� ���� ������ �����Ǿ� �ֳ���? : ");
	scanf("%d", &term_cnt);
	printf("���� 1�� �Է��ϼ���. : ");
	for(int i = 0; i < term_cnt; i++) {
		scanf("%d %d", &exp_1[i].coef, &exp_1[i].expon);
	}

	printf("���� 2�� �� ���� ������ �����Ǿ� �ֳ���? : ");
	scanf("%d", &term_cnt);
	printf("���� 2�� �Է��ϼ���. : ");
	for(int i = 0; i < term_cnt; i++) {
		scanf("%d %d", &exp_2[i].coef, &exp_2[i].expon);
	}
	
	add(exp_1, exp_2, exp_3);
	printf("���� 1 + 2�� ");
	for(int i = 0; exp_3[i].coef != 0; i++) {
		if (i == MAX_DEGREE) break; 
		printf("%d %d ", exp_3[i].coef, exp_3[i].expon);
	}
	printf("\n");
	
	multiply(exp_1, exp_2, exp_4);
	printf("���� 1 * 2�� ");
	for(int i = 0; exp_4[i].coef != 0; i++) {
		if (i == MAX_DEGREE) break;
		printf("%d %d ", exp_4[i].coef, exp_4[i].expon);
	}
	printf("\n");
	
	while(1) {
		int exp_num, x;
		polynomial *exp_arr[4] = {exp_1, exp_2, exp_3, exp_4};
		printf("���Ŀ� ���� �������� : ");
		scanf("%d %d", &exp_num, &x);
		printf("������� %d\n", calc(exp_arr[exp_num - 1], x));
	}
	
	return 0;
}
