//#include "window.h"
#include "Q_learning.h"

//using namespace Win;
using namespace QL;

int main()
{
	//win wi;

	/*list<int> arr = { 15,11,13,99,03 };/// for each
	for (auto gg : arr)
	cout << gg << endl;*/



	Q_learning ql;
	ql.initializeQ();

	cout << ql.predict() << endl;




	system("pause");
	return 0;
}