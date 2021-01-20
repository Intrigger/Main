#include <iostream>
#include <complex>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>


using namespace std;
using namespace sf;


int main() {

	double start = 2.0;
	while (start < 10) {
		Image img;

		cout << "Current: " << start << endl;

		double X, Y;
		X = 4000.0;
		Y = 4000.0;

		double cof = 2.0;

		img.create(X, Y, Color(255, 255, 255));

		double size = 2;

		for (int y = 0; y < Y; y++) {
			for (int x = 0; x < X; x++) {
				double rez = -2 + (double(x) / X * 4);
				double imz = -2 + (double(y) / Y * 4);
				complex<double> c(rez, imz);
				complex<double> z(0, 0);
				complex<double> newz;
				int counter = 0;
				double modz;
				double modnewz;
				for (int k = 0; k < 30; k++) {
					newz = pow(z, start) + c;
					modz = sqrt(pow(z.imag(), 2) + pow(z.real(), 2));
					modnewz = sqrt(pow(newz.imag(), 2) + pow(newz.real(), 2));
					z = newz;
				}

				modz = sqrt(pow(z.imag(), 2) + pow(z.real(), 2));

				if (modz < 50) {
					img.setPixel(x, y, Color(255, 0, 0));
				}

			}
		}

		img.saveToFile("mandelbrot/mandelbrot" + to_string(start) + ".png");
		start += 0.1;
	}

	
	return 0;
}
