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

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

struct vector{
	unsigned char v;
	vector* next;
};

struct dict{
	char *key;	//само слово
	int value = 0;  // количество слов равных ключу
};

struct dict_vector{
	dict element;
	dict_vector* next;
};

char *maxOfStrings(char* str1, char* str2){
	char* strings[2] = {str1, str2};
	int lengths[2] = {strlen(strings[0]), strlen(strings[1])};

	if (lengths[0] != lengths[1]){
		if (lengths[0] < lengths[1]){

		}
	}
}


int main(){

	char fileName[100];
	
	cout << "Введите имя текстового файла для анализа:";
	
	scanf("%s", fileName);

	FILE* file = fopen(fileName, "rb");
	ifstream fin;

	fin.open(fileName);

	if (!fin.is_open()){
		cout << "Ошибка! Не удалось открыть файл!\n";
		exit(-1);
	}
	else{
		cout << "Файл успешно открыт!\n";
	}

	cout << "Анализ текстового файла начат!\n";

	vector data;
	vector* dataStart = &data;
	vector* dataP = &data;

	unsigned char symbol;

	unsigned int symbolsN = 0;

	while (!feof(file)){
		dataP->v = getc(file);
		dataP->next = new vector;
		dataP = dataP->next;
		symbolsN++;
	}


	dict_vector vec;
	dict_vector* vecHead = &vec;
	dict_vector* vecP = &vec;

	vecP->element.key = "hello";
	vecP->element.value += 1;
	vecP->next = new dict_vector;
	vecP = vecP->next;

	vecP->element.key = "world";
	vecP->element.value += 1;
	vecP->next = new dict_vector;
	vecP = vecP->next;

	vecP->element.key = "name";
	vecP->element.value += 1;
	vecP->next = new dict_vector;
	vecP = vecP->next;

	vecP->element.key = "my";
	vecP->element.value += 1;
	vecP->next = new dict_vector;
	vecP = vecP->next;




	vecP = vecHead;

	for (int i = 0; i < 4; i++){
		cout << "dict_vector[" << i << "]: ";
		cout << "\tkey: " << vecP->element.key;
		cout << "\tvalue: " << vecP->element.value << endl;
		vecP = vecP->next;
	}
	

	return 0;
}