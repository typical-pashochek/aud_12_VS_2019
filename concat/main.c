#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

//Вариант функции с заранее выделяемой памятью
/*char* concat(char* first, ...) {
	int Size = 1024;
	va_list arglist;
	va_start(arglist, first);
	int len = 0;
	if (strlen(first) > 1023) {
		printf("Very big string\n");
		return;
	}
	char* _result = (char*)malloc(Size * sizeof(char));
	for (int j = 0; j < strlen(first); j++) {
		_result[len] = first[j];
		len++;
	}

	char* i;
	do {
		i = va_arg(arglist, char*);
		if (len + strlen(i) > 1023) {
			printf("Very big string\n");
			return;
		}
		for (int j = 0; j < strlen(i); j++) {
			_result[len] = i[j];
			len++;
		}
	} while (i[0] != 0);
	va_end(arglist);
	char* result = (char*)malloc((len+1) * sizeof(char));
	for (int j = 0; j < len; j++) {
		result[j] = _result[j];
	}
	result[len] = 0;
	free(_result);
	return result;
}*/

//Вариант функции с использованием realloc()
char* concat(char* first, ...) {
	int Size = strlen(first);
	va_list arglist;
	va_start(arglist, first);
	int len = 0;
	char* result = (char*)malloc(Size * sizeof(char));
	for (int j = 0; j < strlen(first); j++) {
		result[len] = first[j];
		len++;
	}

	char* i;
	do {
		i = va_arg(arglist, char*);
		result = (char*)realloc(result, len + strlen(i));
		for (int j = 0; j < strlen(i); j++) {
			result[len] = i[j];
			len++;
		}
		if (i[0] == 0) {
			result = (char*)realloc(result, len + 1);
			result[len] = i[0];
			len++;
		}
	} while (i[0] != 0);
	va_end(arglist);
	return result;
}

int main() {
	char* str1 = concat("one ", "two ", "three ", "four", "\0");
	printf("%s\n", str1);
	free(str1);
	str1 = concat("Happy ", "new ", "year!", "\0");
	printf("%s\n", str1);
	free(str1);
	str1 = concat("Hello ", "world!", "\0");
	printf("%s\n", str1);
	free(str1);
	return 0;
}