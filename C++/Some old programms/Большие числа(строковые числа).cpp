#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<string>
#include<fstream>
#include<conio.h>
#include<Windows.h>
#include<random>

using namespace sf;
using namespace std;


string reverse(string x)
{
	for (int i = 0; i < int(x.length() / 2); i++)
	{
		swap(x[i], x[x.length() - 1 - i]);
	}
	return x;
}

string tobin(string dec)
{
	ofstream fout;
	fout.open("log.txt");
	string binary;
	string buf;
	bool to_up = 0;
	int counter = 0;
	while (dec.length() > 1)
	{
		for (int i = 0; i < dec.length(); i++)
		{
			char s = dec[i];

			int x = atoi(&s);

			
			if (to_up)
			{
				x += 10;
				to_up = false;
			}
			if (x % 2 == 1)
			{
				if(i != dec.length()-1) to_up = true;
			}

			
			if ((x == 1) && (i == 0))
			{
				to_up = true;
				continue;
			}
			buf.append(to_string(int(x / 2)));
		}
		dec.clear();
		dec = buf;
		/*if (dec.length() == 1)
		{
			cout << dec;
		}*/
		buf.clear();
		cout << dec << endl;
	}
	
	fout.close();
	return buf;
}


int main()
{
	system("color 2");
	Event event;
	Image img;
	ofstream fout;
	fout.open("text.txt");
	img.loadFromFile("image.png");
	Texture texture;
	texture.loadFromImage(img);
	Sprite s;
	s.setTexture(texture);
	/*
	for (int i = 0; i < img.getSize().y; i++)
	{
		for (int j = 0; j < img.getSize().x; j++)
		{
			fout << int(img.getPixel(j, i).r) << " ";
			fout << int(img.getPixel(j, i).g) << " ";
			fout << int(img.getPixel(j, i).b) << endl;
		}
	}
	
	cout << "Done!";*/
	cout << "Enter N(10): ";
	string n;
	cin >> n;
	cout << tobin(n);
	fout.close();
	cout << "Done!";
	_getch();
	return 0;
}
