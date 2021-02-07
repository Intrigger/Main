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

class nn {
public:
	int layersN;
	int* arch;
	string* activationFunctions;
	long long neuronsNum = 0;
	long long weightsNum = 0;
	double* values;	//values of neurons
	double* errors;
	double* weights; // weights of neurons
	nn(int lN, int* Arch, string* AF) {
		layersN = lN;
		arch = new int[lN];
		activationFunctions = new string[lN];
		for (int i = 0; i < lN; i++) {
			arch[i] = Arch[i];
			activationFunctions[i] = AF[i];
			neuronsNum += arch[i];
			if (i > 0) {
				weightsNum += arch[i] * arch[i - 1];
			}
		}
		weights = new double[weightsNum];
		values = new double[neuronsNum];
		errors = new double[neuronsNum];
	}

	void gemm(int M, int N, int K, const double* A, const double* B, double* C)
	{
		for (int i = 0; i < M; ++i)
		{
			double* c = C + i * N;
			for (int j = 0; j < N; ++j)
				c[j] = 0;
			for (int k = 0; k < K; ++k)
			{
				const double* b = B + k * N;
				float a = A[i * K + k];
				for (int j = 0; j < N; ++j)
					c[j] += a * b[j];
			}
		}
	}
	void gemmSum(int M, int N, int K, const double* A, const double* B, double* C)
	{
		for (int i = 0; i < M; ++i)
		{
			double* c = C + i * N;
			for (int k = 0; k < K; ++k)
			{
				const double* b = B + k * N;
				double a = A[i * K + k];
				for (int j = 0; j < N; ++j)
					c[j] += a * b[j];
			}
		}
	}

	void New() {
		long long counter = 0;
		for (int i = 0; i < layersN - 1; i++) {
			for (int j = 0; j < arch[i] * arch[i + 1]; j++) {
				weights[counter] = (double(rand() % 101) / 100.0) / arch[i + 1];
				counter++;
			}
		}
	}

	void act(int valuesC, int layer) {
		if (activationFunctions[layer] == "sigmoid") {
			for (int i = valuesC; i < valuesC + arch[layer]; i++) {
				values[i] = (1 / (1 + pow(2.71828, -values[i])));
			}

		}
		if (activationFunctions[layer] == "relu") {
			for (int i = valuesC; i < valuesC + arch[layer]; i++) {
				if (values[i] < 0) values[i] *= 0.01;
			}
		}
		if (activationFunctions[layer] == "softmax") {
			double zn = 0.0;
			for (int i = 0; i < arch[layer]; i++) {
				zn += pow((2.71), values[valuesC + i]);
			}
			for (int i = 0; i < arch[layer]; i++) {
				values[valuesC + i] = pow(2.71, values[valuesC + i]) / zn;
			}
		}
	}

	void pro(double* value, int ecounter, int layer) {
		if (activationFunctions[layer] == "sigmoid") {
			for (int i = 0; i < arch[layer]; i++) {
				values[ecounter + i] = values[ecounter + i] * (1.0 - values[ecounter + i]);
				value[i] *= values[ecounter + i];
			}
		}

		if (activationFunctions[layer] == "relu") {
			for (int i = 0; i < arch[layer]; i++) {
				if (values[i + ecounter] < 0) values[i] = 0.01;
				else values[i + ecounter] = 1.0;
				value[i] *= values[ecounter + i];
			}
		}

		if (activationFunctions[layer] == "softmax") {
			/*
			float** matrix = new float *[arch[layer]];
			for (int i = 0; i < arch[layer]; i++) {
				matrix[i] = new float[arch[layer]];
			}
			for (int i = 0; i < arch[layer]; i++) {
				for (int j = 0; j < arch[layer]; j++) {
					if (i == j) {
						matrix[i][j] = values[ecounter + i] * (1.0 - values[ecounter + i]);
					}
					else {
						matrix[i][j] = -(values[ecounter + i] * values[ecounter + j]);
					}
				}
			}
			float* pros = new float[arch[layer]];
			for (int i = 0; i < arch[layer]; i++) {
				pros[i] = 0.0;
				for (int j = 0; j < arch[layer]; j++) {
					pros[i] += matrix[j][i];
				}
				value[i] *= pros[i];

			}
			for (int i = 0; i < arch[layer]; i++) {
				delete[] matrix[i];
			}
			delete[] pros;*/
			for (int i = 0; i < arch[layer]; i++) {
				value[i] *= values[ecounter + i] * (1.0 - values[ecounter + i]);
			}
		}
	}

	void ForwardFeed(float* input_data) {
		for (int i = 0; i < arch[0]; i++) {
			values[i] = input_data[i];
		}

		long long valuesC = 0;
		long long weightsC = 0;
		for (int i = 0; i < layersN - 1; i++) {
			double* a = values + valuesC;
			double* b = weights + weightsC;
			double* c = values + valuesC + arch[i];
			gemm(1, arch[i + 1], arch[i], a, b, c);


			//for (int j = valuesC; j < valuesC + arch[i + 1]; j++) {
			valuesC += arch[i];
			act(valuesC, i + 1);



			weightsC += arch[i] * arch[i + 1];

		}

	}

	void GetPrediction(float* result) {
		long long h = neuronsNum - arch[layersN - 1];
		float sum = 0;
		for (int i = 0; i < arch[layersN - 1]; i++) {
			result[i] = values[h + i];
			sum += result[i];
		}
	}

	void BackPropogation(float* rightResults, float lr) {
		//Сначала вычисление ошибок
		int h = neuronsNum - arch[layersN - 1];
		for (int i = 0; i < arch[layersN - 1]; i++) {
			errors[i + h] = rightResults[i] - values[i + h];
		}
		long long wcounter = weightsNum;
		long long ecounter = neuronsNum;
		long long counter = neuronsNum - arch[layersN - 1];
		for (int i = layersN - 1; i > 0; i--) {
			ecounter -= arch[i];
			wcounter -= arch[i] * arch[i - 1];
			counter -= arch[i - 1];
			double* a = errors + ecounter;
			double* b = weights + wcounter;
			double* c = errors + counter;
			gemm(1, arch[i - 1], arch[i], a, b, c);

		}

		//Потом обновление весов:
		long long vcounter = neuronsNum - arch[layersN - 1];
		wcounter = weightsNum;
		ecounter = neuronsNum;
		for (int i = layersN - 1; i > 0; i--) {
			ecounter -= arch[i];
			vcounter -= arch[i - 1];
			wcounter -= arch[i] * arch[i - 1];
			double* b = new double[arch[i]];
			for (int j = 0; j < arch[i]; j++) {
				b[j] = errors[ecounter + j] /*pro(values[ecounter + j], i)*/ * lr;
			}
			pro(b, ecounter, i);
			double* a = values + vcounter;
			double* c = weights + wcounter;

			gemmSum(arch[i - 1], arch[i], 1, a, b, c);

			delete[] b;
		}

	}

	void SaveWeights(string filename) {
		ofstream fout;
		fout.close();
		fout.open(filename);
		for (int i = 0; i < weightsNum; i++) {
			fout << weights[i] * 10000.0 << " ";
		}
		fout.close();
	}
};
int checkWinner(int** field, int playerId) {
	for (int i = 0; i < 3; i++) {
		if ((field[i][0] == field[i][1]) and (field[i][0] == field[i][2])) {
			if (playerId == field[i][0]) return playerId;
		}
		if ((field[0][i] == field[1][i]) and (field[0][i] == field[2][i])) {
			if (playerId == field[0][i]) return playerId;
		}
	}
	if ((field[0][0] == field[1][1]) and (field[0][0] == field[2][2])) {
		if (playerId == field[0][0]) return playerId;
	}
	if ((field[0][2] == field[1][1]) and (field[0][2] == field[2][0])) {
		if (playerId == field[0][2]) return playerId;
	}
	return 0;
}

struct go {
	float field[9];
	int cell;
};

int main() {
	const int layers = 3;
	int size[layers] = { 9, 36, 9 };
	string AF[layers - 1] = { "relu", "softmax" };
	nn net(layers, size, AF);
	net.New();

	srand(time(0));

	int** field = new int*[3];
	for (int i = 0; i < 3; i++) {
		field[i] = new int[3];
		for (int j = 0; j < 3; j++) {
			field[i][j] = 0;
		}
	}

	// 1 - AI
	// 2 - random
	const int batchN = 100;
	const int batchSize = 100000;
	int totalAIWins = 0;
	int totalRandomWins = 0;
	int stats[3] = { 0, 0, 0 };
	for (int b = 0; b < batchN; b++) {
		int wrongGoes = 0;
		stats[0] = stats[1] = stats[2] = 0;
		for (int g = 0; g < batchSize; g++) {
			vector<go> goes;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					field[i][j] = 0;
				}
			}
			int nowGoes = rand() % 2 + 1;
			int steps = 0;
			while (!(checkWinner(field, 1) or checkWinner(field, 2))) {
				//cout << "Now goes #" << nowGoes << "\n\n";

				if (nowGoes == 2) {
					int cell = 0;
					do {
						cell = rand() % 9;
					} while (field[cell / 3][cell % 3] != 0);
					
					float a_go[9];
					for (int i = 0; i < 9; i++) {
						if (field[i / 3][i % 3] == 0) a_go[i] = 0.0;
						if (field[i / 3][i % 3] == 1) a_go[i] = -1.0;
						if (field[i / 3][i % 3] == 2) a_go[i] = 1.0;
					}
					
					go v;
					v.cell = cell;
					for (int i = 0; i < 9; i++) {
						v.field[i] = a_go[i];
					}

					field[cell / 3][cell % 3] = nowGoes;
					/*
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							cout << field[i][j];
						}
						cout << "\n";
					}

					cout << "\n\n";
					*/
				}
				else {
					int cell = 0;
					float input[9];
					for (int i = 0; i < 9; i++) {
						if (field[i / 3][i % 3] != nowGoes) input[i] = -1.0;
						else {
							if (field[i / 3][i % 3] != 0) input[i] = 1.0;
							else input[i] = 0.0;
						}
					}
					net.ForwardFeed(input);
					float prediction[9];
					net.GetPrediction(prediction);
					cell = 0;
					float maxV = prediction[0];
					for (int i = 0; i < 8; i++) {
						if (maxV < prediction[i + 1]) {
							swap(prediction[i + 1], maxV);
							cell = i + 1;
						}
					}

					float rresult[9];
					int emptyCellCounter = 0;
					for (int i = 0; i < 9; i++) {
						rresult[i] = 0.0;
						if (field[i / 3][i % 3] == 0) emptyCellCounter++;
					}
					for (int i = 0; i < 9; i++) {
						if (field[i / 3][i % 3] == 0) rresult[i] = 1.0 / float(emptyCellCounter);
					}
					while (field[cell / 3][cell % 3] != 0) {
						wrongGoes++;
						net.BackPropogation(rresult, 0.1);
						net.ForwardFeed(input);
						net.GetPrediction(prediction);
						cell = 0;
						float maxV = prediction[0];
						for (int i = 0; i < 8; i++) {
							if (maxV < prediction[i + 1]) {
								swap(prediction[i + 1], maxV);
								cell = i + 1;
							}
						}
					}
					field[cell / 3][cell % 3] = nowGoes;

					/*
					for (int i = 0; i < 3; i++) {
						for (int j = 0; j < 3; j++) {
							cout << field[i][j];
						}
						cout << "\n";
					}

					cout << "\n\n";
					*/

				}


				steps++;
				if ((steps == 9) and (checkWinner(field, 1) == 0) and (checkWinner(field, 2) == 0)) {
					stats[0]++;
					break;
				}

				if (nowGoes == 1) nowGoes = 2;
				else nowGoes = 1;
			}

			if (checkWinner(field, 1) == 1) {
				stats[1]++;
			}
			else {
				if (checkWinner(field, 2) == 2) {
					stats[2]++;
					//Studying
					
					for (int i = 0; i < goes.size(); i++) {
						net.ForwardFeed(goes[i].field);
						float prediction[9];
						net.GetPrediction(prediction);
						int cell = 0;
						float maxV = prediction[0];
						for (int i = 0; i < 8; i++) {
							if (maxV < prediction[i + 1]) {
								swap(prediction[i + 1], maxV);
								cell = i + 1;
							}
						}
						float rresult[9];
						for (int i = 0; i < 9; i++) rresult[i] = 0.0;
						rresult[goes[i].cell] = 1.0;
						if (cell != goes[i].cell) {
							net.BackPropogation(rresult, 0.001);
						}
					}
				}
			}

		}
		
		cout << "Batch #" << b + 1 << endl;
		cout << "In a row: " << stats[0] << " == " << double(stats[0]) / double(batchSize) * 100 << " % " << endl;
		cout << "Player AI: " << stats[1] << " == " << double(stats[1]) / double(batchSize) * 100 << " % (wrong goes : " <<   double(wrongGoes)/double(batchSize) << ")" << endl;
		cout << (double(stats[1]) / double(batchSize)) / (double(stats[2]) / double(batchSize)) << endl;
		cout << "Random: " << stats[2] << " == " << double(stats[2]) / double(batchSize) * 100 << " % " << endl;
		cout << "\n\n";
		
		totalAIWins += stats[1];
		totalRandomWins += stats[2];
	}
	
	cout << "Total AI winrate: " << double(totalAIWins) / double(batchN * batchSize) << endl;
	cout << "Total random winrate: " << double(totalRandomWins) / double(batchN * batchSize) << endl;
	

}