#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int strLen1(const char* str) {
	int len = 0;
	while (*str != '\0') {
		len++;
		str++;
	}
	return len;
}

int strLen2(const char* str) {
	int len = 0;
	for (; str[len]; len++);
	return len;
}

char * strCpy(char * dest, const char * src) {
	char * org = dest;

	while (*src) {
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';

	return org;
}

int strCmp(const char* str1, const char* str2) {
	int idx = 0;
	while (str1[idx] && str1[idx] == str2[idx]) {
		idx++;
	}

	return str1[idx] - str2[idx];

}

char * strCat(char *dest, const char *src) {
	char *org = dest;
	while (*dest) dest++;

	while (*src) {
		*dest = *src;
		src++;
		dest++;
	}
	*dest = '\0';

	return org;
}

char * strReverse(char * str) {
	int len = 0;
	for (; str[len]; len++);

	int half = len / 2;
	for (int i = 0; i < half; ++i) {
		char ch = str[i];
		str[i] = str[len - 1 - i];
		str[len - 1 - i] = ch;
	}

	return str;
}

int strToInt(const char* str) {
	int num = 0;
	int isNegative = 0;

	if (*str == '-') {
		isNegative = 1;
		str++;
	}

	while (*str) {
		char ch = *str++;
		if (ch < '0' || '9' < ch) break;
		num = num * 10 + ch - '0';
	}

	if (isNegative == 1) num *= -1;
	return num;
}

char * IntToStr(int value, char *buf) {
	int idx = 0;
	int isNegative = 0;

	if (value < 0) {
		isNegative = 1;
		value *= -1;
	}

	while (value > 0) {
		buf[idx++] = value % 10 + '0';
		value /= 10;
	}

	if (isNegative) {
		buf[idx++] = '-';
	}
	buf[idx] = '\0';

	int half = idx >> 1; //idx / 2;
	// ������ (reverse)
	for (int i = 0; i < half; ++i) {
		int tmp = buf[i];
		buf[i] = buf[idx - 1 - i];
		buf[idx - 1 - i] = tmp;
	}

	return buf;
}

int main() {
	char src[] = "abcdefghjiklmnopqrstuvwxyz";

	// ���ڿ� ����
	printf("���ڿ��� ���� : %d\n", strLen2(src));

	// ���ڹ迭 ����� �Ҵ�
	char str2[100] = { 0, };		// 0 == '\0' == nullptr == NULL

	// ���ڿ� ����
	// strCpy(str2, src);
	printf("������ ���ڿ� : %s\n", strCpy(str2, src));


	// ���ڿ� ��
	str2[26] = '#';		// len ��ġ�� �׻� '\0'�� �ִ�.  '\0' -> '#'
	if (strCmp(src, str2) == 0) {
		printf("���� ���ڿ�\n");
	}
	else {
		printf("�ٸ� ���ڿ�\n");
	}

	// ���ڿ� ����
	// strCat(str2, "!@#$%");
	printf("������ ���ڿ� : %s\n", strCat(str2, "!@#$%"));


	// ���ڿ� ������
	printf("������ ���ڿ� : %s\n", strReverse(str2));

	// atoi() : "1234" --> 1234
	printf("%d\n", strToInt("-1234abcd") + 100);

	// itoa() : 1234 --> "1234"
	char str3[10] = { 0, };
	printf("%s\n", strCat(str2, IntToStr(-1234, str3)));

	return 0;
}