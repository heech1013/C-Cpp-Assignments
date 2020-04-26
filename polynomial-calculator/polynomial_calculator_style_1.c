#include <stdio.h>
#include <math.h>

#define MAX_DEGREE 11
#define MAX_TEMP_DEGREE 73

typedef struct {
	int expon;  /* ���׽��� �ִ� ���� */
	int coef[MAX_DEGREE];  /* ���׽��� ��� */
} polynomial;

/* �ӽ÷� ���� ������� �Է��� ���� ��Ŀ� �°� ��ȯ�Ͽ� �����Ѵ�. */
void format(int *arr, polynomial *exp, int cnt) {
	int index;
	exp->expon = arr[1];
	for(int i = 0; i < cnt; i++) {
		/* ���׽��� ������ �´� �迭�� �ε����� ����Ͽ� �ش� ��ġ�� ����� �����Ѵ�. */
		index = (exp->expon) - arr[(i * 2) + 1];
		exp->coef[index] = arr[i * 2];
	}
}

/* ������� �Է� ��Ŀ� �°� ��ȯ�Ͽ� ����Ѵ�. */
void print(polynomial *exp) {
	int expon_pos = exp->expon;
	for(int i = 0; i < exp->expon + 1; i++) {
		if (exp->coef[i] != 0) {  /* ����� 0�� ���� �����ϰ� ����Ѵ�. */
			printf("%d ", exp->coef[i]);
			printf("%d ", expon_pos);
		}
		expon_pos--;
	}
	printf("%c", '\n');
}

/* ���׽��� ���� */
void add(polynomial *exp_1, polynomial *exp_2, polynomial *exp_3) {
	int dif = (exp_1->expon) - (exp_2->expon);  /* �� ���׽��� ������ ���Ѵ�. */ 
	/* exp_1�� ������ �� Ŭ ��� */
	if (dif > 0) {
		exp_3->expon = exp_1->expon;
		/* ū ������ ������ ��� ���� ��� exp_3�� �����Ѵ�. */
		for(int i = 0; i < dif; i++) {
			exp_3->coef[i] = exp_1->coef[i];	
		}
		/* ������ �°� ����� ���Ѵ�. */
		for(int i = 0; i < exp_3->expon + 1 - dif; i++) {
			exp_3->coef[dif + i] = exp_1->coef[dif + i] + exp_2->coef[i];
		}
	}
	/* exp_2�� ������ �� Ŭ ��� */
	else if (dif < 0) {
		exp_3->expon = exp_2->expon;
		/* ū ������ ������ ��� ���� ��� exp_3�� �����Ѵ�. */
		for(int i = 0; i < -dif; i++) {
			exp_3->coef[i] = exp_2->coef[i];
		}
		/* ������ �°� ����� ���Ѵ�. */
		for(int i = 0; i < exp_3->expon + 1 + dif; i++) {
			exp_3->coef[-dif + i] = exp_1->coef[-dif + i] + exp_2->coef[i];
		}
	}
	/* �� ���׽��� ������ ���� ��� */
	else {
		exp_3->expon = exp_1->expon;
		for(int i = 0; i < exp_3->expon + 1; i++) {
			exp_3->coef[dif + i] = exp_1->coef[dif + i] + exp_2->coef[i];
		}
	}
}

/* ���׽��� ���� */
void multiply(polynomial *exp_1, polynomial *exp_2, polynomial *exp_3) {
	int temp_arr[MAX_TEMP_DEGREE];  /* ���� ��� ���׽��� ����� ������ �Բ� ��� �迭 */
	int arr_pos = 0;
	int expon_pos_1 = exp_1->expon;  /* ���� ��ȸ ���� ���׽� 1�� ������ Ȯ���ϱ� ���� ���� */
	/* ���׽� 1�� ��� ���� ��ȸ(0���� �ְ���������) */
	for(int i = 0; i < exp_1->expon + 1; i++) {
		int expon_pos_2 = exp_2->expon;  /* ���� ��ȸ ���� ���׽� 2�� ������ Ȯ���ϱ� ���� ���� */
		/* ���׽� 2�� ��� ���� ��ȸ(0���� �ְ���������) */
		for (int j = 0; j < exp_2->expon + 1; j++) {
			/* �� ���׽��� ������ ���� ����� ���� �� �ӽ� �迭�� ��´�. */
			temp_arr[arr_pos] = exp_1->coef[i] * exp_2->coef[j];
			arr_pos++;
			/* �� ���׽��� ������ ���� ������ ���� �� �ӽ� �迭�� ��´�. */
			temp_arr[arr_pos] = expon_pos_1 + expon_pos_2;
			expon_pos_2--;
			arr_pos++;
		}
		expon_pos_1--;
	}
	/* ��ȸ �� arr_pos�� temp_arr(�ӽ� �迭)�� ���� ������ ��� �ִ�. */

	exp_3->expon = exp_1->expon + exp_2->expon;
	/* exp_3�� �ְ��������� 0���� ��ȸ */
	for(int e = exp_3->expon; e >= 0; e--) {
		int temp_coef = 0;  /* Ư�� ������ �ش��ϴ� ����� ��� ���� ���� */
		/* �ӽù迭�� �� pair(���� 2�� : ����� ����)�� ��ȸ */
		for(int p = 0; p < arr_pos; p += 2) {
			if (temp_arr[p + 1] == e) {  /* Ư�� ������ �ӽ� �迭�� ��� �ִ� ������ ���� �� */
				temp_coef += temp_arr[p];  /* �ӽ� �迭�� ����� ��´�. */
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
	int term_cnt;  /* ����ڰ� �Է��� ���׽��� �� ����  */
	int temp_arr[13];  /* ����ڰ� �Է��� ���׽��� �ӽ÷� �����ϴ� �迭 */

	polynomial exp_1 = {0, {0, }};  /* ���׽� 1 */
	polynomial exp_2 = {0, {0, }};  /* ���׽� 2 */
	polynomial exp_3 = {0, {0, }};  /* ���� ��� ���׽� */
	polynomial exp_4 = {0, {0, }};  /* ���� ��� ���׽� */
	
	printf("** ���׽��� ������1 **\n���� 1�� �� ���� ������ �����Ǿ� �ֳ���? : ");
	scanf("%d", &term_cnt);
	printf("���� 1�� �Է��ϼ��� : ");
	for(int i = 0; i < term_cnt * 2; i++) {  /* ����� ������ �����ϱ� ���� (�� ���� * 2)��ŭ �ݺ��Ѵ�. */
		scanf("%d", temp_arr + i);
	}
	format(temp_arr, &exp_1, term_cnt);
	
	printf("���� 2�� �� ���� ������ �����Ǿ� �ֳ���? : ");
	scanf("%d", &term_cnt);
	printf("���� 2�� �Է��ϼ��� : ");
	for(int i = 0; i < term_cnt * 2; i++) {
		scanf("%d", temp_arr + i);
	}
	format(temp_arr, &exp_2, term_cnt);
	
	add(&exp_1, &exp_2, &exp_3);
	printf("���� 1 + 2�� : ");
	print(&exp_3);
	
	multiply(&exp_1, &exp_2, &exp_4);
	printf("���� 1 * 2�� : ");
	print(&exp_4);
	
	while(1) {
		int exp_num, x;
		polynomial *exp_arr[4] = {&exp_1, &exp_2, &exp_3, &exp_4};
		printf("���Ŀ� ���� �������� : ");
		scanf("%d %d", &exp_num, &x);
		printf("������� %d\n", calc(exp_arr[exp_num - 1], x));
	}

	return 0;
}
