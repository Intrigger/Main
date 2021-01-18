#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
using namespace std;

int main(){
	
	ofstream fout;
	fout.open("music", ios::binary);
	int amplitude = 32000;

	double fr = 671;
	double frequency = 44100;
	int n = 50;

	int N;

	int notes[8];

	double cof = 1.059;

	notes[0] = 261.63;					// C		// D
	notes[1] = notes[0] * pow(cof, 2);// D#
	notes[2] = notes[0] * pow(cof, 2.5);	// F
	notes[3] = notes[0] * pow(cof, 4);	// G
	notes[4] = notes[0] * pow(cof, 5);// G#
	notes[5] = notes[0] * pow(cof, 5.5);
	notes[6] = notes[0] * pow(cof, 6.5);
	notes[7] = notes[0] * pow(cof, 8.5);
	for (int t = 0; t < 2000; t++){

		fr = notes[rand() % 8];

		N = ceil(frequency / fr * n);
	
		for (int i = 0; i < N; i++){
			int v = sin(double(i) * (6.28318) / frequency * fr) * amplitude;
			fout.write((const char*)&v, 2);
		}

		fr = notes[rand() % 8];

		N = ceil(frequency / fr * n);
		
		for (int i = 0; i < N; i++){
			int v = sin(double(i) * (6.28318) / frequency * fr) * amplitude;
			fout.write((const char*)&v, 2);
		}
	}
	


	fout.close();

	return 0;
}