#pragma once

//#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include <sstream>
//#include <conio.h>
//#include <string>
#include <vector>
//#include <time.h>
#include <ctime>
#include <cmath>
//#include <list>//I am a bad man :с

using namespace sf;
using namespace std;

namespace I_want_to_sleep
{
	struct Im_stupid
	{
		int one_two[3] = { 2,2,4 };// первый эл. это количество точек в массиве
		int one_three[4] = { 3,2,4,5 };
		int one_five[7] = { 6,2,1,3,6,10,12 };
		int one_four[7] = { 6,2,1,3,6,10,9 };
		int one_seven[6] = { 5,2,1,3,6,10 };

		int two_one[3] = { 2,4,2 };
		int two_three[3] = { 2,4,5 };
		int two_four[6] = { 5,4,7,6,10,9 };
		int two_five[6] = { 5,4,7,6,10, 12 };
		int two_seven[5] = { 4,4,7,6,10 };

		int three_one[4] = { 3,5,4,2 };
		int three_two[3] = { 2,5,4 };
		int three_four[6] = { 5,5,8,11,10,9 };
		int three_five[6] = { 5,5,8,11,10,12 };
		int three_seven[5] = { 4,5,8,11,10 };

		int four_one[7] = { 6,9,10,6,3,1,2 };
		int four_two[6] = { 5,9,10,6,7,4 };
		int four_three[7] = { 6,9,10,6,7,8,5 };
		int four_five[4] = { 3,9,10,12 };
		int four_seven[3] = { 2,9,10 };

		int five_one[8] = { 7,12,10,11,8,5,4,2 };
		int five_two[5] = { 4,12,10,6,7 };
		int five_three[7] = { 6,12,10,6,7,8,5 };
		int five_four[4] = { 3,12,10,9 };
		int five_seven[3] = { 2,12,10 };

		int seven_one[6] = { 5,10,6,7,4,2 };
		int seven_two[5] = { 4,10,6,7,4 };
		int seven_three[6] = { 5,10,6,7,8,5 };
		int seven_four[3] = { 2,10,9 };
		int seven_five[3] = { 2,10,12 };
	};

}

namespace Tag_Types
{
	struct tags
	{
		int museums_1[3] = { 2,2,8 };
		int monuments_2[7] = { 6,0,1,4,5,6,9 };
		int religion[3] = { 2,3,7 };
		int parks[5] = { 4,0,1,4,6 };
		int art[5] = { 4,2,3,7,8 };
		int exterior[5] = { 4,2,3,6,7 };
	};
}