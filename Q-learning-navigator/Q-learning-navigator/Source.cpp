#include "window.h"
#include "Q_learning.h"

//using namespace Win;
using namespace QL;

int main()
{
	//Win::win wi;

	/*list<int> arr = { 15,11,13,99,03 };/// for each
	for (auto gg : arr)
	cout << gg << endl;*/

	int y[6] = { 0,0,0,1,1,1 };

	int* g = new int[6];
	for (int i = 0; i < 6; i++)
		g[i] = y[i];

	Q_learning ql;
	//ql.initializeQ();
	g = ql.fake(y);

	

	//cout << ql.predict() << endl;




	system("pause");
	return 0;
}