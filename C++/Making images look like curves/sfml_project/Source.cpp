#include <iostream>
#include <complex>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <time.h>

using namespace std;
using namespace sf;


int main() {

	srand(time(0));


	Image img;
	img.loadFromFile("image.bmp");

	int imgx = img.getSize().x;
	int imgy = img.getSize().y;

	RenderWindow wnd(VideoMode(imgx, imgy), "Curve image");



	
	Image output;
	output.create(imgx * 1.5, imgy * 1.5);

	double cof = 10;
	double ampl = 10.0;
	for (int y = 0; y < imgy; y++) {
		for (int x = 0; x < imgx; x++) {
			
			int xnew = x;
			int ynew = y + ampl * cos(x / cof);

			ynew += 100;

			output.setPixel(xnew, ynew, Color(img.getPixel(x, y)));

		}
	}

	Texture t;
	t.loadFromImage(output);
	Sprite s(t);

	output.saveToFile("results/result" + to_string(rand() % 32000) + ".png");


	while (wnd.isOpen())
	{
		sf::Event event;
		while (wnd.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				wnd.close();
		}

		wnd.clear();
		wnd.draw(s);
		wnd.display();
	}


	cin.get();

	return 0;
}
