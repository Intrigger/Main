#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<conio.h>
#include<iostream>
#include<string>
using namespace std;

int main()
{
	int n;
	cin >> n;
	bool to_swap = true;
	string *Names = new string[n];
	for (int i = 0; i < n; i++)
	{
		cin >> Names[i];
	}

	int MaxLength = 0;

	for (int i = 0; i < n; i++)
	{
		if (Names[i].length() > MaxLength) MaxLength = Names[i].length();
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = Names[i].length(); j < MaxLength; j++)
		{
			Names[i] += '*';
		}

		cout << Names[i] << endl;
	 }

	for (int i = 0; i < MaxLength; i++)
	{
		for (int j = 0; j < n; j++)
		{
			for (int k = 0; k < n - j - 1; k++)
			{
				if (i == 0)
				{
					if (Names[k][i] > Names[k + 1][i])
					{
						cout << "SWAP (" << Names[k] << ", " << Names[k + 1] << ")" << " as " << Names[k][i] << " > " << Names[k + 1][i] << endl;
						swap(Names[k], Names[k + 1]);
					}
				}

				if (i != 0)
				{
					to_swap = 1;
					if (Names[k][i] > Names[k + 1][i])
					{
						for (int l = i-1; l >= 0; l--)
						{
							if (Names[k][l] == Names[k + 1][l])
							{
								to_swap *= 1;
							}
							else
							{
								to_swap *= 0;
							}
						}
						if (to_swap)
						{
							cout << "SWAP (" << Names[k] << ", " << Names[k + 1] << ")" << " as " << Names[k][i] << " > " << Names[k + 1][i] << endl;
							swap(Names[k], Names[k + 1]);
						}
						
					}
				}
			}
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < MaxLength; j++)
		{
			if (Names[i][j] == '*') continue;
			else
			{
				cout << Names[i][j];
			}
		}
		cout << endl;
	}


	_getch();
	return 0;
}