#include <stdio.h>
#include <string.h>

int compare(char* a, char* b) {
	int a_len = strlen(a);
	int b_len = strlen(b);

	if (a_len != b_len)
		return a_len > b_len;
	for (int i = 0; i < a_len; i++) {
		if (a[i] != b[i]) 
			return a[i] > b[i];
	}
	return 1;
}

void encode(char* a, int* a_int) {
	for (int i = strlen(a) - 1, j = 200; i >= 0; i--, j--) {
		a_int[j] = a[i] - 48;
	}
}

void print_res(int* A) {
	int i;
	for (i = 0; i < 200; i++) {
		if (A[i])
			break;
	}
	for (; i <= 200; i++) {
		printf("%d", A[i]);
	}
	printf("\n");
}

void add(char* a, char* b) {
	int A[201] = { 0 }, B[201] = { 0 };
	int sum[202] = { 0 };

	encode(a, A); encode(b, B);

	for (int i = 200; i > 0; i--) {
		sum[i] += A[i] + B[i];
		if (sum[i] >= 10) {
			sum[i - 1]++;
			sum[i] -= 10;
		}
	}

	print_res(sum);;
}

void sub(char* a, char* b) {
	int A[201] = { 0 }, B[201] = { 0 };
	int sub_res[201] = { 0 };

	encode(a, A); encode(b, B);

	for (int i = 200; i > 0; i--) {
		sub_res[i] += A[i] - B[i];

		if (sub_res[i] < 0) {
			sub_res[i - 1]--;
			sub_res[i] += 10;
		}
	}
	 print_res(sub_res);
}

void mul(char* a, char* b) {
	int A[201] = { 0 }, B[201] = { 0 };
	int mul[402] = { 0 };
	int k;

	encode(a, A); encode(b, B);

	for (int j = 200; j >= 0; j--) {
		for (int i = 200; i >= 0; i--) {
			mul[i + j] += A[i] * B[j] / 10;
			mul[i + j + 1] += A[i] * B[j] % 10;
		}
	}

	for (int i = 401; i > 0; i--) {
		if (mul[i] > 9) {
			int temp = mul[i];
			mul[i] = temp % 10;
			mul[i - 1] += temp / 10;
		}
	}

	for (k = 0; k < 402; k++) {
		if (mul[k])
			break;
	}
	for (; k < 402; k++) {
		printf("%d", mul[k]);
	}
	printf("\n");
}

void div(char* a, char* b) {
	//not working yet
	int A[201] = { 0 }, B[201] = { 0 };
	int sub_res[201] = { 0 };
	int k;

	encode(a, A); encode(b, B);

	while (1)
	{
		for (int i = 200; i > 0; i--) {
			sub_res[i] += A[i] - B[i];

			if (sub_res[i] < 0) {
				sub_res[i - 1]--;
				sub_res[i] += 10;
			}
		}

		for (int i = 0; i < 201; i++) {
			A[i] = sub_res[i];
		}

		if (compare(sub_res, b)) {
			break;
		}
	}

	for (k = 0; k < 200; k++) {
		if (A[k])
			break;
	}
	for (; k <= 200; k++) {
		printf("%d", A[k]);
	}
	printf("\n");
	
}

int main() {
	char A[201], B[201];
	scanf("%s %s", A, B);
	printf("순서대로 덧셈, 뺄셈, 곱셈, 나눗셈\n");

	add(A, B);

	if (compare(A, B)) {
		sub(A, B);
	}
	else {
		printf("-");
		sub(B, A);
	}

	mul(A, B);
	

	div(A, B);
}
