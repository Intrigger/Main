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
#include <math.h>
#include <ctype.h>
#include <locale.h>
#include "textAnalysis.h"

unsigned char *blackList = " ,.!?()-:;«»\"\n–'%^&*@#$[]<>|~";



int inBlackList(unsigned char c){
	for (int i = 0; i < strlen(blackList); i++){
		if (blackList[i] == c) return 1;
	}
	return 0;
}

int main(){


	printf("TEXT ANALYZER v0.1 by Intriger\n\n\n");

	printf("Enter the name of file for analysis: ");

	char fileName[100];

	scanf("%s", fileName);

	FILE* file;
	unsigned char symbol;

	if ((file = fopen(fileName, "r")) == NULL){
		printf("Error opening file!\n");
		exit(-1);
	}
	else{
		printf("File %s opened successfully!\n", fileName);
	}


	int sortBy;	// 0 - key, 1 - value
	int sortType;	//0 - ascending, 1 - descending 

	printf("Sorting by key(0) or by value(1): ");
	scanf("%d", &sortBy);

	printf("Sorting ascending(0) or descending(1): ");
	scanf("%d", &sortType);


	printf("Starting analysis...\n");

	struct strIntDictionaryVector vec;
	struct strIntDictionaryVector* vecHead = &vec;
	struct strIntDictionaryVector* vecC = &vec;

	struct buf data;
	struct buf* dataP = &data;


	int length = 0;

	while (!feof(file)){
		length++;
		dataP->value = tolower(getc(file));
		dataP->next = (struct buf*) calloc(1, sizeof(struct buf));
		dataP = dataP->next;
	}



	dataP = &data;

	int current = 0;

	int vecSize = 0;


	while (current < length - 1){
		while (inBlackList(dataP->value) && (current < length - 1)){
			current++;
			dataP = dataP->next;
		}

		if (!(current < length - 1)) break;


		unsigned char word[50];
		for (int i  = 0; i < 50; i++) word[i] = 0;
		int iter = 0;

		while ((!inBlackList(dataP->value)) && (current < length - 1)){
			word[iter] = dataP->value;
			dataP = dataP->next;
			iter++;
			current++;
		}


		if (!inVector(vecHead, word, vecSize)){

			vecSize++;
			for (int i = 0; i < 50; i++){
				vecC->element.key[i] = word[i];
			}
			vecC->element.value = 1;
			vecC->next = (struct strIntDictionaryVector*) calloc(1, sizeof(struct strIntDictionaryVector));
			vecC = vecC->next;
		}
		else{
			struct strIntDictionaryVector* vecCCopy = vecC;

			vecC = vecHead;

			int cur = 0;

			while (cur < vecSize){
				if (strEquals(vecC->element.key, word)){
					vecC->element.value += 1;
					break;
				}
				vecC = vecC->next;
				cur++;
			}



			vecC = vecCCopy;

		}


	}




	printf("vecSize: %d\n", vecSize);

	printf("\nStatystics about %d words: \n\n", vecSize);

	vecC = &vec;

	if (sortBy == 0){
		sortVectorByKey(vecC, vecSize, sortType);
	}
	else{
		sortVectorByValue(vecC, vecSize, sortType);
	}
	

	for (int i = 0; i < vecSize; i++){
		printf("%s : %d\n", vecC->element.key, vecC->element.value);
		if (i + 1 < vecSize) vecC = vecC->next;
	}

	fclose(file);

	FILE* stats = fopen("stats.txt", "w");

	vecC = &vec;

	fprintf(stats, "Statystics (%d different words): \n", vecSize);


	for (int i = 0; i < vecSize; i++){

		fprintf(stats, "%s : %d\n", (vecC->element.key), vecC->element.value);
		if (i + 1 < vecSize) vecC = vecC->next;
	}

	fclose(file);

}