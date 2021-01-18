#include<iostream>
#include<conio.h>
#include<string>
#include<cmath>
using namespace std;
//
typedef unsigned long long ull;
//

int CharToInt(char S)
{
	switch (S)
	{
	case('0'): return 0;
	case('1'): return 1;
	case('2'): return 2;
	case('3'): return 3;
	case('4'): return 4;
	case('5'): return 5;
	case('6'): return 6;
	case('7'): return 7;
	case('8'): return 8;
	case('9'): return 9;
	case('A'): return 10;
	case('B'): return 11;
	case('C'): return 12;
	case('D'): return 13;
	case('E'): return 14;
	case('F'): return 15;
	}
}
char IntToChar(int S)
{
	switch (S)
	{
	case(0): return '0';
	case(1): return '1';
	case(2): return '2';
	case(3): return '3';
	case(4): return '4';
	case(5): return '5';
	case(6): return '6';
	case(7): return '7';
	case(8): return '8';
	case(9): return '9';
	case(10): return 'A';
	case(11): return 'B';
	case(12): return 'C';
	case(13): return 'D';
	case(14): return 'E';
	case(15): return 'F';
	}

}
int Length(string Count)
{
	int Length = 0;
	for (int i = 0; Count[i] != '\0'; i++)
	{
		Length++;
	}
	return Length;
}
bool Checking(int CS, string Count)
{
	bool Check = 1;
	int L = Length(Count);
	for (int i = 0; i < L; i++)
	{
		if (CharToInt(Count[i]) >= CS)
		{
			cout << "Öèôðà " << Count[i] << " íå èñïîëüçóåòñÿ â " << CS << "-÷íîé ñèñòåìå ñ÷èñëåíèÿ!" << endl;
			Check = 0;
		}


	}
	return Check;
}
ull To10(int CS, string Count)
{
	ull  C10 = 0;
	for (int i = 0; i < Length(Count); i++)
	{
		C10 += CharToInt(Count[Length(Count) - 1 - i]) * (pow(CS, i));
	}
	return C10;
}
string ToOverWrong(int CS2, string Count, int CS)
{
	ull Int10 = To10(CS, Count);
	string OverW;
	while (Int10 != 0)
	{
		OverW += IntToChar(Int10%CS2);
		Int10 = Int10 / CS2;
	}
	return OverW;
}
void ToOverRight(string str)
{

	int L = Length(str);
	for (int i = 0; i < L; i++)
	{
		cout << str[L - 1 - i] ;
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int CS;
	int CS2;
	cout << "Ââåäèòå ñèñòåìó ñ÷èñëåíèÿ âàøåãî ÷èñëà: ";
	cin >> CS;
	string Count;
	cout << "Ââåäèòå âàøå ÷èñëî: ";
	cin >> Count;
	while (!(Checking(CS, Count)))
	{
		cout << "Ââåäèòå âàøå ÷èñëî: ";
		cin >> Count;
	}
	cout << "Â êàêóþ ñèñòåìó ñ÷èñëåíèÿ Âû õîòèòå ïåðåâåñòè âàøå ÷èñëî?: ";
	cin >> CS2;
	cout << "Âàøå ÷èñëî: ";
	ToOverRight(ToOverWrong(CS2, Count,CS));
	_getch();
	return 0;
}
