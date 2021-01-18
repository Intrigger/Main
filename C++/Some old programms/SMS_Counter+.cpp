#include<iostream>
#include<conio.h>
#include<string.h>
#include<fstream>
#include<time.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include<ctime>

using namespace std;



int main()
{
	double start_time = clock();
	setlocale(LC_ALL, "Russian");

	ofstream fout;
	ifstream fin;
	fstream in("C:/Users/Intrigger/Desktop/text.txt");
	fin.open("C:/Users/Intrigger/Desktop/text.txt");
	fout.open("C:/Users/Intrigger/Desktop/dates.txt");
	char s;
	int counter = 0;
	while (in.get(s))
	{
		fin >> s;
		if (s == '(')
		{
			char stack[20];
			stack[0] = s;
			for (int i = 1; i < 20; i++)
			{
				fin >> s;
				stack[i] = s;
			}
			if ((stack[3] == ':') && (stack[6] == ':'))
			{
				for (int i = 0; i < 20; i++)
				{
					fout << stack[i];
				}
				counter++;
				fout << endl;
			}
		}
	}
	double end_time = clock();
	double time = end_time - start_time;
	cout << "Well done!" << endl;
	cout << "Всего сообщений: " << counter << endl;
	cout << "Время выполнения программы : " << time/1000 << endl;
	_getch();
	return 0;
}
