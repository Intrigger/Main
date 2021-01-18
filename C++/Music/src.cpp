#include <iostream>
#include <random>
#include <fstream>
#include <cmath>
using namespace std;

int main(){
	
	ofstream fout;
	fout.open("music", ios::binary);
	int amplitude = 32000;

	double fr = 261.63;
	double cof = 1.0594;

	int a;

	int secondsTime = 24;

	int temp = 2;


	int audioFrequency = 44000;

	for (int i = 0; i < secondsTime*audioFrequency; i++){
		
		
		int v1 = cos(double(i) * 2 * 3.1415 / audioFrequency * fr) * amplitude;
		
		if ((i % (audioFrequency / temp) == 0) && (i != 0)){
			if ((i / audioFrequency) <= (secondsTime / 2)){
				fr *= pow(cof, 1.0 / temp);
			}
			else fr /= pow(cof, 1.0 / temp);
		}


		fout.write((const char*) &v1, 2);
	}


	return 0;
}