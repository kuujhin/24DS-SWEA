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
	// 뒤집기 (reverse)
	for (int i = 0; i < half; ++i) {
		int tmp = buf[i];
		buf[i] = buf[idx - 1 - i];
		buf[idx - 1 - i] = tmp;
	}

	return buf;
}

int main() {
	char src[] = "abcdefghjiklmnopqrstuvwxyz";

	// 문자열 길이
	printf("문자열의 길이 : %d\n", strLen2(src));

	// 문자배열 선언과 할당
	char str2[100] = { 0, };		// 0 == '\0' == nullptr == NULL

	// 문자열 복사
	// strCpy(str2, src);
	printf("복사한 문자열 : %s\n", strCpy(str2, src));


	// 문자열 비교
	str2[26] = '#';		// len 위치에 항상 '\0'가 있다.  '\0' -> '#'
	if (strCmp(src, str2) == 0) {
		printf("같은 문자열\n");
	}
	else {
		printf("다른 문자열\n");
	}

	// 문자열 연결
	// strCat(str2, "!@#$%");
	printf("연결한 문자열 : %s\n", strCat(str2, "!@#$%"));


	// 문자열 뒤집기
	printf("뒤집은 문자열 : %s\n", strReverse(str2));

	// atoi() : "1234" --> 1234
	printf("%d\n", strToInt("-1234abcd") + 100);

	// itoa() : 1234 --> "1234"
	char str3[10] = { 0, };
	printf("%s\n", strCat(str2, IntToStr(-1234, str3)));

	return 0;
}