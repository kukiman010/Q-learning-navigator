#include "Q_learning.h"

namespace QL
{
	Q_learning::Q_learning()
	{
		Random_weight();
		for (int i = 0; i < 10; i++)
			hidN[i] = 0;
		for (int i = 0; i < 6; i++)
			inputs[i] = 0;
	}

	void Q_learning::initializeQ()
	{
		int b[64][6];
		for (int i = 0; i < 64; i++)
			for (int j = 0; j<6; j++)
				b[i][j] = 0;

		int predict[6] = { 1,2,4,8,16,32 };
		int cache[6];
		for (int i = 0; i < 6; i++)
			cache[i] = predict[i];

		for (int i = 1; i < 64; i++)
		{
			if (i >= predict[5])
				b[i][0] = 1;
			if (cache[4] == i)
			{
				if (predict[4] + 16 == i)
				{
					cache[4] += 16;
					predict[4] += 32;
				}
				else
				{
					b[i][1] = 1;
					cache[4] += 1;
				}
			}
			if (cache[3] == i)
			{
				if (predict[3] + 8 == i)
				{
					cache[3] += 8;
					predict[3] += 16;
				}
				else
				{
					b[i][2] = 1;
					cache[3] += 1;
				}
			}
			if (cache[2] == i)
			{
				if (predict[2] + 4 == i)
				{
					cache[2] += 4;
					predict[2] += 8;
				}
				else
				{
					b[i][3] = 1;
					cache[2] += 1;
				}
			}
			if (cache[1] == i)
			{

				if (predict[1] + 2 == i)
				{
					cache[1] += 2;
					predict[1] += 4;
				}
				else
				{
					b[i][4] = 1;
					cache[1] += 1;
				}
			}
			if (i >= predict[0] && cache[0] <= i)
			{
				b[i][5] = 1;
				if (cache[0] == i)
					cache[0] += 2;
			}
		}

		/*for (int i = 0; i < 64; i++)
		{
		cout << i << ":  ";
		for (int j = 0; j < 6; j++)
		cout << b[i][j] << " ";
		cout << endl;
		}*/

		for (int i = 0, j = 1; i < 64; j++, i++)
		{
			matrix[i][6] = j;
			for (int h = 0; h < 6; h++)
				matrix[i][h] = b[i][h];
			for (int h = 7; h < 17; h++)
				matrix[i][h] = 10;
		}
		
		
		for (int i = 0; i < 64; i++)
		{
			for (int j = 0; j < 17; j++)
			{
				cout << matrix[i][j];
				if (j == 5 || j == 6)
					cout << "   ";
				else
					cout << " ";
			}
			cout << endl;
		}

	}

	void Q_learning::Random_weight()
	{

		weight_1[6][10];
		weight_2[10];

		srand(time(nullptr));

		for (int i = 0; i <6; i++)
			for (int j = 0; j < 10; j++)
			{
				weight_1[i][j] = (rand() % 10) / 10.08;
				weight_1[i][j] = sigmoid(weight_1[i][j]);
			}

		for (int i = 0; i < 10; i++)
		{
			weight_2[i] = (rand() % 10) / 10.08;
			weight_2[i] = sigmoid(weight_2[i]);
		}
	}

	double Q_learning::sigmoid(double x)
	{
		return 1 / (1 + exp(-x));
	}

	double Q_learning::predict()
	{
		for (int i = 0; i < 6; i++)
		{
			for (int j = 0; j < 10; j++)
				hidN[i] += inputs[j] * weight_1[j][i];
			hidN[i] = sigmoid(hidN[i]);
		}

		for (int i = 0; i<10; i++)
			output += (hidN[i] * weight_2[i]);
		return output = sigmoid(output);
	}

	int * Q_learning::fake(int b[6])
	{
		

		
		return b;
	}

	Q_learning::~Q_learning()
	{
	}
}