#include<iostream>
#include<conio.h>
#include<time.h>
#include<fstream>
#include<time.h>
#include<Windows.h>
#include<cmath>
#include<random>
using namespace std;
double sigm_pro(double x) {
	if ((fabs(x - 1) < 1e-9) || (fabs(x) < 1e-9)) return 0.0;
	double res = x * (1.0 - x);
	return res;
}

struct neuron {
	double value;
	double error;
	void act() {
		value = (1 / (1 + pow(2.71828, -value)));
	}
};

struct data_one {
	double info[4096];
	char rresult;
};

class network {
public:
	int layers;
	neuron **neurons;
	double ***weights;
	int* size;
	double predict(double x) {
		if (x >= 0.8) {
			return 1;
		}
		else {
			return 0;
		}
	}
	void set_layers_no_study(int n, int *p) {
		ifstream fin;
		fin.open("perfect_weights.txt");
		srand(time(0));
		layers = n;
		neurons = new neuron * [n];
		weights = new double** [n - 1];
		size = new int[n];
		for (int i = 0; i < n; i++) {
			size[i] = p[i];
			neurons[i] = new neuron[p[i]];
			if (i < n - 1) {
				weights[i] = new double* [p[i]];
				for (int j = 0; j < p[i]; j++) {
					weights[i][j] = new double[p[i + 1]];
					for (int k = 0; k < p[i + 1]; k++) {
						fin >> weights[i][j][k];
					}
				}
			}
		}
	}
	void set_layers(int n, int *p) {
		srand(time(0));
		layers = n;
		neurons = new neuron * [n];
		weights = new double ** [n - 1];
		size = new int[n];
		for (int i = 0; i < n; i++) {
			size[i] = p[i];
			neurons[i] = new neuron[p[i]];
			if (i < n - 1) {
				weights[i] = new double *[p[i]];
				for (int j = 0; j < p[i]; j++) {
					weights[i][j] = new double[p[i + 1]];
					for (int k = 0; k < p[i + 1]; k++) {
						weights[i][j][k] =  ((rand() % 100)) * 0.01 / size[i];
					}
				}
			}
		}
	}
	void set_random_input() {
		for (int j = 0; j < layers; j++) {
			for (int k = 0; k < size[j]; k++) {
				neurons[j][k].value = rand() % 2;
			}
		}
	}
	void set_input(double *p) {
		for (int i = 0; i < size[0]; i++) {
			neurons[0][i].value = p[i];	
		}
	}
	void show() {
		cout << "Нейронная сеть имеет архитектуру: ";
		for (int i = 0; i < layers; i++) {
			cout << size[i];
			if (i < layers - 1) {
				cout << " - ";
			}
		}cout << endl;
		for (int i = 0; i < layers; i++) {
			cout << "\n#Слой " << i + 1 << "\n\n";
			for (int j = 0; j < size[i]; j++) {
				cout << "Нейрон #" << j + 1 << ": \n";
				cout << "Значение: " << neurons[i][j].value << endl;
				if (i < layers - 1) {
					cout << "Веса: \n";
					for (int k = 0; k < size[i + 1]; k++) {
						cout << "#" << k + 1 << ": ";
						cout << weights[i][j][k] << endl;
					}
				}
			}
		}
	}
	double forward_feed() {
		for (int i = 1; i < layers; i++) {
			for (int j = 0; j < size[i]; j++) {
				neurons[i][j].value = 0;
			}
			for (int j = 0; j < size[i]; j++) {
				for (int k = 0; k < size[i - 1]; k++) {
					neurons[i][j].value += neurons[i - 1][k].value * weights[i - 1][k][j];
				}
				//cout << "До активации: " << neurons[i][j].value << endl;
				neurons[i][j].act();
			}
		}
		double max = 0;
		double prediction = 0;
		for (int i = 0; i < size[layers - 1]; i++) {
			if (neurons[layers - 1][i].value > max) {
				max = neurons[layers - 1][i].value;
				prediction = i;
			}
		}
		return prediction;
	}
	double back_propogation(double prediction, double rresult, double lr /*lr = learning rate, rresult = right result*/ ) {
		//cout << "\t\tRRESULT:\t\t" << rresult << endl;
		for (int i = layers - 1; i > 0; i--) {
			if (i == layers - 1) {
				for (int j = 0; j < size[i]; j++) {
					if (j != int(rresult)) {
						neurons[i][j].error = -(neurons[i][j].value);
						//cout << "Neurons[" << i << "][" << j << "].value:\t" << neurons[i][j].value << endl;
						//cout << "Error for neuron #" << j << " = " << -(neurons[i][j].value) << endl;
					}
					else {
						neurons[i][j].error = 1.0 - neurons[i][j].value;
						//cout << "Neurons[" << i << "][" << j << "].value:\t" << neurons[i][j].value << endl;
						//cout << "Error for neuron #" << j << " = \t" << neurons[i][j].error << endl;
					}
					
				}
			}
			else {
				for (int j = 0; j < size[i]; j++) {
					double error = 0.0;
					for (int k = 0; k < size[i + 1]; k++) {
						error += neurons[i + 1][k].error * weights[i][j][k];
						//cout << "Error: " << neurons[i + 1][k].error << "\tweight: " << weights[i][j][k] << endl;
					}
					neurons[i][j].error = error;
					//cout << "Ошибка нейрона [ " << i << " ] [ " << j << " ]: " << neurons[i][j].error << endl;
				}
			}
			
		}
		//cout << "Ошибки для всех нейронов посчитаны!" << endl;
		double layer_weights_dif = 0;
		for (int i = 0; i < layers - 1; i++) {
			 layer_weights_dif = 0;
			for (int j = 0; j < size[i]; j++) {
				//cout << "Значение нейрона [ " << i << " ] [ " << j << " ]: " << neurons[i][j].value << endl;
				for (int k = 0; k < size[i + 1]; k++) {
					//cout << "Lr: " << lr << endl;
					//cout << "Neurons[" << i + 1 << "][" << k << "].error: " << neurons[i + 1][k].error << endl;
					//cout << "Sigm_pro: " << sigm_pro(neurons[i + 1][k].value) << endl;
					//cout << "Neurons[" << i << "][" << j <<"].value: " << neurons[i][j].value << endl;
					weights[i][j][k] += lr * neurons[i + 1][k].error * sigm_pro(neurons[i + 1][k].value) * neurons[i][j].value;
					double delta = lr * neurons[i + 1][k].error * sigm_pro(neurons[i + 1][k].value) * neurons[i][j].value;
					layer_weights_dif += lr * neurons[i + 1][k].error * sigm_pro(neurons[i + 1][k].value) * neurons[i][j].value;
					/*if (neurons[0][j].value != 0) {
						//cout << "Delta : " << delta << endl;
						cout << "Lr: " << lr << endl;
						cout << "Neurons[" << i + 1 << "][" << k << "].error: " << neurons[i + 1][k].error << endl;
						cout << "Sigm_pro: " << sigm_pro(neurons[i + 1][k].value) << endl;
						cout << "Neurons[" << i + 1 << "][" << k << "].value:= " << neurons[i + 1][k].value << endl;
						cout << "Neurons[" << i << "][" << j << "].value: " << neurons[i][j].value << endl;
					}*/
					
				}
			}
			//cout << "Layer #" << i << " weights dif: " << layer_weights_dif << endl;
		}
		return 0;
	}
	bool save_weights() {
		ofstream fout;
		fout.open("perfect_weights.txt");
		for (int i = 0; i < layers; i++) {
			if (i < layers - 1) {
				for (int j = 0; j < size[i]; j++) {
					for (int k = 0; k < size[i + 1]; k++) {
						fout << weights[i][j][k] << " ";
					}
				}
			}
		}
		fout.close();
		return 1;
	}
};

int main() {
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	ifstream fin;
	ofstream fout;
	fout.open("log.txt");
	const int l = 4;
	const int input_l = 4096;
	int size[l] = { input_l, 64,  32 ,   26 };
	network nn;
	
	double input[input_l];
	//double rresult;
	char rresult;
	double result;
	double ra = 0;
	int maxra = 0;
	int maxraepoch = 0;
	const int n = 52;
	bool to_study = 0;
	cout << "Производить обучение?";
	cin >> to_study;
	if (to_study) {

		
		nn.set_layers(l, size);
		for (int e = 0; ra / n * 100 < 100; e++) {
			//cout << "Epoch #" << e << endl;
			fout << "Epoch # " << e << endl;
			ra = 0;
			double w_delta = 0;
			fin.open("lib.txt");

			for (int i = 0; i < n; i++) {
				for (int j = 0; j < input_l; j++) {
					fin >> input[j];
				}
				fin >> rresult;
				rresult -= 65;
				//cout << int(rresult) << endl;
				//cout << "Цифра " << rresult << endl;
				nn.set_input(input);

				result = nn.forward_feed();
				//nn.show();
				if (result == rresult) {
					//cout << "Результат верный!\n";
					//cout << "Угадал цифру " << result << "\t\t\t****" <<  endl;
					ra++;
				}
				else {
					//cout << "Результат " << result << " неверный!\n";
					//cout << "Не угадал цифру " << rresult << "\n";
					w_delta += nn.back_propogation(result, rresult, 0.25);
				}
			}
			fin.close();
			cout << "Right answers: " << ra / n * 100 << "% \t Max RA: " << double(maxra) / n * 100 << "(epoch " << maxraepoch << " )" << endl;
			fout << "Right answers: " << ra / n * 100 << "% \t Max RA: " << double(maxra) / n * 100 << "(epoch " << maxraepoch << " )" << endl;

			//cout << "W_Delta: " << w_delta << endl;
			if (ra > maxra) {
				maxra = ra;
				maxraepoch = e;
			}
			if (maxraepoch < e - 250) {
				maxra = 0;
			}
		}
		fout.close();
		if (nn.save_weights()) {
			cout << "Веса сохранены!";
		}
	}
	else {
		nn.set_layers_no_study(l, size);
	}
	fin.close();

	cout << "Начать тест:(1/0) ";
	bool to_start_test = 0;
	cin >> to_start_test;
	if (to_start_test) {
		fin.open("test.txt");
		for (int i = 0; i < input_l; i++) {
			fin >> input[i];
		}
		nn.set_input(input);
		result = nn.forward_feed();
		cout << "Я считаю, что это буква " << char(result+65) << "\n\n";
	}

	
	return 0;
}