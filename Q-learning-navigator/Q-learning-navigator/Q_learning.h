#pragma once
#include "headers.h"
using namespace std;
using namespace Tag_Types;

namespace QL
{
	class Q_learning
	{
	private:
		bool inputs[6];
		double hidN[10];
		double output = 0;

		double weight_1[6][10];
		double weight_2[10];

		double matrix[64][17];


		float gamma = 0.75;
		float alpha = 0.1;
		double explorationConst = 300;
		double r = 0.0;
		double lookAheadValue = 0.0;
		double sample = 0.0;
		double theta2Min = 90.0;

	public:
		Q_learning();
		void initializeQ();
		void Random_weight();
		double sigmoid(double x);
		double predict();
		int* imitation(int* b, float* distance, int time);
		
		~Q_learning();
	};
}