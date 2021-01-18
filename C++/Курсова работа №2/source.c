/*

	Курсова работа по программированию №2
	Цель программы - анализ текстового файла.
	Функции:
	1) Подсчет количества символов.
	2) Подсчет количества слов.
	3) Подсчет частоты слов.
	4) Вывод самых частых и самых редких слов.
	5) Вывод статистики по каждому слову в файл.

*/

#include <stdio.h>
#include <stdlib.h>
#include "textAnalysis.h"

int main(){

	printf("TEXT ANALYZER v0.1 by Intriger\n\n\n");

	printf("Enter the name of file for analysis: ");

	char fileName[100];

	scanf("%s", fileName);

	FILE* file;
	unsigned char symbol;

	if (fopen(fileName, "r") == NULL){
		printf("Error opening file!\n");
		exit(-1);
	}
	else{
		printf("File %s opened successfully!\n", fileName);
	}

	printf("Starting analysis...\n");

	struct strIntDictionaryVector vec;
	struct strIntDictionaryVector* vecHead = &vec;
	struct strIntDictionaryVector* vecC = &vec;

	vecC->element.key = "hello";
	vecC->element.value = 1;
	vecC->next = (int*) calloc(1, sizeof(struct strIntDictionaryVector));
	vecC = vecC->next;



	vecC->element.key = "hello1";
	vecC->element.value = 1;
	vecC->next = (int*) calloc(1, sizeof(struct strIntDictionaryVector));
	vecC = vecC->next;



	vecC->element.key = "hello2";
	vecC->element.value = 1;
	vecC->next = (int*) calloc(1, sizeof(struct strIntDictionaryVector));
	vecC = vecC->next;

	char* str1 = "hello3";
	char* str2 = "hello3";

	printf("%d", strEquals(str1, str2));


}