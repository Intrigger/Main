/*

	Programming course work #2
	Programm goal - text file analysis
	Functions:
	1) Counting symbols number
	2) Cunting words number
	3) Words frequency

*/

// Including nesessary libraries
#include <stdio.h>
#include <stdlib.h>	
#include <math.h>
#include <ctype.h>
#include <locale.h>
#include "textAnalysis.h"	//handwritten library 

// list of symbols which mustnt be inside words
unsigned char *blackList = " ,.!?()-:;«»\"\n–'%^&*@#$[]<>|~";


// checking if the symbol is in blackList
int inBlackList(unsigned char c){
	for (int i = 0; i < strlen(blackList); i++){
		if (blackList[i] == c) return 1;
	}
	return 0;
}


//the main function
int main(){


	printf("TEXT ANALYZER v0.1 by Intriger\n\n\n");

	printf("Enter the name of file for analysis: ");

	char fileName[100]; //filename

	scanf("%s", fileName);	//input the filename

	FILE* file;				//the input file	

	if ((file = fopen(fileName, "r")) == NULL){		//checking is file was opened
		printf("Error opening file!\n");
		exit(-1);
	}
	else{
		printf("File %s opened successfully!\n", fileName);
	}

	//sorting by value or by key
	int sortBy;	// 0 - key, 1 - value

	// ascending or descending sorting
	int sortType;	//0 - ascending, 1 - descending 

	printf("Sorting by key(0) or by value(1): ");
	scanf("%d", &sortBy);

	printf("Sorting ascending(0) or descending(1): ");
	scanf("%d", &sortType);


	printf("Starting analysis...\n");

	//the main vector with word and their frequency in the text
	struct strIntDictionaryVector vec;

	//the head pointer
	struct strIntDictionaryVector* vecHead = &vec;

	//the currentElementInVectorrentSymbol pointer
	struct strIntDictionaryVector* vecC = &vec;

	//buffer which contains all the symbols of the text
	struct buf data;

	//currentElementInVectorrentSymbol dataPointer
	struct buf* dataP = &data;

	//the characters in the file
	int symbolsN = 0;

	while (!feof(file)){	//while we dont reach the end of the file
		symbolsN++;	//increasing the characters number
		dataP->value = tolower(getc(file));	//reading one symbol
		dataP->next = (struct buf*) calloc(1, sizeof(struct buf));	//creating next buffer element
		dataP = dataP->next;	//going next
	}


	//returing to the head	
	dataP = &data;


	int currentElementInVectorrentSymbol = 0;

	//vector size --- the words number
	int vecSize = 0;

	//going through all the symbols
	while (currentElementInVectorrentSymbol < symbolsN - 1){
		//while the symbol is in black list -- going next symbol
		while (inBlackList(dataP->value) && (currentElementInVectorrentSymbol < symbolsN - 1)){
			currentElementInVectorrentSymbol++;
			dataP = dataP->next;
		}

		//if we reached the end - breaking the cycle
		if (!(currentElementInVectorrentSymbol < symbolsN - 1)) break;


		//the array of symbols for currentElementInVectorrent word
		unsigned char word[50];
		//zeroing it
		for (int i  = 0; i < 50; i++) word[i] = 0;

		//currentElementInVectorrent position in the word
		int wordIter = 0;

		//while its a good symbol -- saving it to the word[50] buffer
		while ((!inBlackList(dataP->value)) && (currentElementInVectorrentSymbol < symbolsN - 1)){
			word[wordIter] = dataP->value;
			dataP = dataP->next;
			wordIter++;
			currentElementInVectorrentSymbol++;
		}

		//checking if the word is already in the word`s vector
		if (!inVector(vecHead, word, vecSize)){
			vecSize++;	//increasing the vector`s size
			for (int i = 0; i < 50; i++){
				vecC->element.key[i] = word[i];	//copying the word to vector`s word
			}
			//we added the word - its frequency is 1
			vecC->element.value = 1; 
			//going next word
			vecC->next = (struct strIntDictionaryVector*) calloc(1, sizeof(struct strIntDictionaryVector));
			vecC = vecC->next;
		}
		//if the word is already in the vector
		else{

			//temporary pointer
			struct strIntDictionaryVector* vecCCopy = vecC;

			//starting from the head - and than going through all the vector
			vecC = vecHead;

			int currentElementInVector = 0;

			//going through the vector while we dont meet the nessesary word
			while (currentElementInVector < vecSize){
				if (strEquals(vecC->element.key, word)){
					vecC->element.value += 1;	//increasing its frequency by 1
					break;
				}
				vecC = vecC->next;
				currentElementInVector++;
			}


			//returning back to vecC value
			vecC = vecCCopy;

		}


	}




	printf("vecSize: %d\n", vecSize);

	printf("\nStatystics about %d words: \n\n", vecSize);

	//returning back to head
	vecC = &vec;

	//sorting different ways
	if (sortBy == 0){
		sortVectorByKey(vecC, vecSize, sortType);
	}
	else{
		sortVectorByValue(vecC, vecSize, sortType);
	}
	

	//printing statystics on the screen

	for (int i = 0; i < vecSize; i++){
		printf("%s : %d\n", vecC->element.key, vecC->element.value);
		if (i + 1 < vecSize) vecC = vecC->next;
	}

	//closing reading the input file
	fclose(file);

	//creating file for statystics
	FILE* stats = fopen("stats.txt", "w");

	//againg going to the head pointer
	vecC = &vec;


	//printing all the statystics to the file
	fprintf(stats, "Statystics (%d different words): \n", vecSize);


	for (int i = 0; i < vecSize; i++){

		fprintf(stats, "%s : %d\n", (vecC->element.key), vecC->element.value);
		if (i + 1 < vecSize) vecC = vecC->next;
	}

	//closing the file
	fclose(file);

}