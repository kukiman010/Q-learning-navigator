#include "window.h"
namespace Win
{
	win::win()
	{
		main();
	}

	void win::main()
	{
		thread dj(&win::menu, this);

		RenderWindow window(VideoMode(window_x, window_y), "Window");
		view.reset(FloatRect(0, 0, window_x, window_y));
		start_options();
		player snake_1("point.png", 1562, 957);
		cache_x = snake_1.x, cache_y = snake_1.y;

		image map("44.png");

		Font font;
		font.loadFromFile("ubuntu.ttf");
		Text text("", font, 16);
		text.setFillColor(Color::Black);//заливает текст в черный цвет 

		while (window.isOpen())
		{
			time_window = clock.getElapsedTime().asMicroseconds(); //дать прошедшее врем§ в микросекундах
			clock.restart(); //перезагружает врем§
			time_window = time_window / 500;//скорость игры


			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}

			if (Keyboard::isKeyPressed(Keyboard::A))
			{
				lave = "LEFT"; status = 99; status_2 = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::D))
			{
				lave = "RIGHT"; status = 99; status_2 = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::W))
			{
				lave = "UP"; status = 99; status_2 = 0;
				//snake_1.sprite.move(0, -0.1*time_window);
			}
			if (Keyboard::isKeyPressed(Keyboard::S))
			{
				lave = "DOWN";
				status = 99;
				status_2 = 0;
				//snake_1.sprite.move(0, 0.1*time_window);
			}
			if (Keyboard::isKeyPressed(Keyboard::P))
			{
				lave = "STOP";
				//status = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::T))
			{
				status_2 = 0;
				lave = "TELEPORT";
			}
			if (Keyboard::isKeyPressed(Keyboard::Num1))status = 1;
			if (Keyboard::isKeyPressed(Keyboard::Num2))status = 2;
			if (Keyboard::isKeyPressed(Keyboard::Num3))status = 3;
			if (Keyboard::isKeyPressed(Keyboard::Num4))status = 4;
			if (Keyboard::isKeyPressed(Keyboard::Num5))status = 5;
			if (Keyboard::isKeyPressed(Keyboard::Num6))status = 6;
			if (Keyboard::isKeyPressed(Keyboard::Num7))status = 7;
			if (Keyboard::isKeyPressed(Keyboard::Num8))status = 8;
			if (Keyboard::isKeyPressed(Keyboard::Num9))status = 9;
			if (Keyboard::isKeyPressed(Keyboard::Num1) && (Keyboard::isKeyPressed(Keyboard::Num0)))
				status = 10;
			//if (Keyboard::isKeyPressed(Keyboard::Num1) && (Keyboard::isKeyPressed(Keyboard::Num1)))
			//status = 11;
			if (Keyboard::isKeyPressed(Keyboard::Num0))
				status = 11;



			snake_1 = logic(snake_1);
			snake_1.color_player();

			//range_to_objects(snake_1.x, snake_1.y);////////////////////////////////////////////////////////////////////////////////////////
			test(snake_1.x, snake_1.y);
			//////////////////////////////////////////////////


			GetPlayerView(snake_1.x, snake_1.y);
			window.setView(view);
			window.clear();
			window.draw(map.sprite);
			window.draw(snake_1.sprite);
			ostringstream a, b, c, d, e, p, k, l;
			a << snake_1.x; c << lave;
			b << snake_1.y; d << status_2;
			e << point_2; p << status;
			k << point; l << min;
			text.setString("x: " + a.str() + " \ny: " + b.str() + "\n" + c.str() + "\nstatus_2: " + d.str() + "\npoint_2: "
				+ e.str() + "\nstatus: " + p.str() + "\npoint: " + k.str() + "\n\nmin: " + l.str());
			text.setPosition(view.getCenter().x - 420, view.getCenter().y - 255);
			window.draw(text);
			window.display();
		}
		dj.detach();
	}

	player win::logic(player p)// дыра в логике !!!!!
	{
		if (status == 0)
			lave = "STOP";
		else if (status == 99)
		{
			if (status_2 == 0)
			{
				p.motion(lave, cache_x, cache_y, time_window, status);
				lave = "STOP";
			}
		}
		else
		{
			if (status_2 == 0)
			{
				int y = swap_point(p.x, p.y);
				cache_x = Roads[y][0];
				cache_y = Roads[y][1];

				status_2 = 1;
			}
			else if (status_2 == 2)
			{
				if (point_2 == 0 && accurate_pointer(p.x, p.y) < 1)
				{
					point = route_search(status, swap_point(p.x, p.y));
					point_3 = 1;
				}
				else if (point_2 == 1 && accurate_pointer(p.x, p.y) < 1)
				{
					point = route_search(status, swap_point(p.x, p.y));
					point_3 = 1;
				}
				if (point == 0)
					status_2 = 3;
			}

			if (status_2 == 2)
			{
				if (point_3 == 1)
				{
					point--;
					cache_x = Roads[point][0];
					cache_y = Roads[point][1];
					point++;
				}
				else
				{
					cache_x = Roads[point][0];
					cache_y = Roads[point][1];
				}

			}
			else if (status_2 == 3)
			{
				status--;
				cache_x = Attraction[status][0];
				cache_y = Attraction[status][1];
				status++;
			}
			lave = p.network_player(lave, cache_x, cache_y);
			if (p.x == cache_x && p.y == cache_y)
			{
			}
			else
				p.motion(lave, cache_x, cache_y, time_window, status);

			if (p.x == cache_x)// отчет о выполнении 
				if (p.y == cache_y)// обрабатывает статусы 
				{
					int h = status;
					--h;
					if (p.x == Attraction[h][0] && p.y == Attraction[h][1])
					{
						if (status_2 == 3)
						{
							lave = "STOP";
							status_2 = 0;
							status = 0;
							point_2 = 0;
						}
					}
					if (status_2 == 1)
					{
						status_2 = 2;
					}
					else if (status_2 == 2)
					{
						if (point == 0)
							status_2 = 3;
					}
					else if (point_2 == 1)
					{
						point_2 = 0;
					}
					else if (point_2 == 0)
					{
						point_2 = 1;
					}

				}
		}

		//cout << point << endl;
		return p;
	}
	void win::start_options()
	{
		lave = "STOP";
		status = 0;
		status_2 = 0;
		point = 0;
		point_2 = 0;
		point_3 = 0;
		min = 15;

		int oto[13][2] = { { 1240,1289 },{ 1658,1297 },{ 1630,1572 },{ 2107,595 },{ 2765,474 },{ 2830,583 },{ 2189,1023 },{ 1292,1268 },{ 1724,1313 },{ 1166,1321 },{ 1585,1760 },{ 1466,1642 } };
		int tot[12][2] = { { 1194,1168 },{ 1188,1350 },{ 1562,1168 },{ 1562,1350 },{ 1562,1601 },{ 1932,1168 },{ 1932,1350 },{ 1932,1601 },{ 2267,658 },{ 2276,1168 },{ 2295,1601 },{ 2846,505 } };

		/*int oto[10][2] = { { 400,470 },{ 632,490 },{ 606,619 },{ 879,32 },{ 1166,59 },{ 1181,140 },{ 879,348 },{ 438,460 },{ 643,470 },{ 349,485 } };
		int tot[12][2] = { {375,416}, {375,507}, {561,416}, {561,507}, {561,622}, {740,416}, {740,507}, {740,635}, {915,44}, {915,416}, {915,635}, {1203,83} };*/

		for (int i = 0; i < 12; i++)
			for (int j = 0; j < 2; j++)
				Attraction[i][j] = oto[i][j];

		for (int i = 0; i < 12; i++)
			for (int j = 0; j < 2; j++)
				Roads[i][j] = tot[i][j];
	}
	int win::swap_point(float X, float Y)
	{
		int oto[12][4];
		int min = 10000, buf = 50;


		for (int i = 0; i < 12; i++)
		{
			if (X >= Roads[i][0])
				oto[i][0] = X - Roads[i][0];
			if (X < Roads[i][0])
				oto[i][0] = Roads[i][0] - X;
			if (Y >= Roads[i][1])
				oto[i][1] = Y - Roads[i][1];
			if (Y < Roads[i][1])
				oto[i][1] = Roads[i][1] - Y;
			oto[i][2] = oto[i][0] + oto[i][1];
			oto[i][3] = i;


			//cout << oto[i][0] << "  " << oto[i][1] << "  " << oto[i][2] << "  " << oto[i][3] << endl;

			if (min >= oto[i][2])
			{
				min = oto[i][2];
				buf = oto[i][3];
			}
		}
		//cout << "\n\n" << min << "\n\n";

		return buf;
	}
	View win::GetPlayerView(int x, int y)
	{
		int temp_x = x, temp_y = y;

		if (x < window_x / 2) temp_x = window_x / 2;
		if (x > 3231 - (window_x / 2)) temp_x = 3231 - (window_x / 2);
		if (y < window_y / 2) temp_y = window_y / 2;
		if (y > 4468 - (window_y / 2)) temp_y = 4468 - (window_y / 2);

		view.setCenter(temp_x, temp_y);
		return view;
	}
	int win::route_search(int num, int point)
	{
		point++;
		I_want_to_sleep::Im_stupid one;

		if (num == 1 || num == 8 || num == 10)
		{
			for (int i = 1; i < one.five_one[0]; i++)
			{
				if (one.five_one[i] == point)
				{
					if (i == one.five_one[0])
						return 0;
					else
						return one.five_one[++i];
				}
			}
			for (int i = 1; i < one.seven_one[0]; i++)
			{
				if (one.seven_one[i] == point)
				{
					if (i == one.seven_one[0])
						return 0;
					else
						return one.seven_one[++i];
				}
			}
			for (int i = 1; i < one.two_one[0]; i++)
			{
				if (one.two_one[i] == point)
				{
					if (i == one.two_one[0])
						return 0;
					else
						return one.two_one[++i];
				}
			}
			for (int i = 1; i < one.three_one[0]; i++)
			{
				if (one.three_one[i] == point)
				{
					if (i == one.three_one[0])
						return 0;
					else
						return one.three_one[++i];
				}
			}
			for (int i = 1; i < one.four_one[0]; i++)
			{
				if (one.four_one[i] == point)
				{
					if (i == one.four_one[0])
						return 0;
					else
						return one.four_one[++i];
				}
			}
		}
		else if (num == 2 || num == 9)
		{
			for (int i = 1; i < one.five_two[0]; i++)
			{
				if (one.five_two[i] == point)
				{
					if (i == one.five_two[0])
						return 0;
					else
						return one.five_two[++i];
				}
			}
			for (int i = 1; i < one.seven_two[0]; i++)
			{
				if (one.seven_two[i] == point)
				{
					if (i == one.seven_two[0])
						return 0;
					else
						return one.seven_two[++i];
				}
			}
			for (int i = 1; i < one.one_two[0]; i++)
			{
				if (one.one_two[i] == point)
				{
					if (i == one.one_two[0])
						return 0;
					else
						return one.one_two[++i];
				}
			}
			for (int i = 1; i < one.three_two[0]; i++)
			{
				if (one.three_two[i] == point)
				{
					if (i == one.five_two[0])
						return 0;
					else
						return one.five_two[++i];
				}
			}
			for (int i = 1; i < one.four_two[0]; i++)
			{
				if (one.four_two[i] == point)
				{
					if (i == one.four_two[0])
						return 0;
					else
						return one.four_two[++i];
				}
			}
		}
		else if (num == 3 || num == 11 || num == 12)
		{
			for (int i = 1; i < one.five_three[0]; i++)
			{
				if (one.five_three[i] == point)
				{
					if (i == one.five_three[0])
						return 0;
					else
						return one.five_three[++i];
				}
			}
			for (int i = 1; i < one.seven_three[0]; i++)
			{
				if (one.seven_three[i] == point)
				{
					if (i == one.seven_three[0])
						return 0;
					else
						return one.seven_three[++i];
				}
			}
			for (int i = 1; i < one.one_three[0]; i++)
			{
				if (one.one_three[i] == point)
				{
					if (i == one.one_three[0])
						return 0;
					else
						return one.one_three[++i];
				}
			}
			for (int i = 1; i < one.two_three[0]; i++)
			{
				if (one.two_three[i] == point)
				{
					if (i == one.two_three[0])
						return 0;
					else
						return one.two_three[++i];
				}
			}
			for (int i = 1; i < one.four_three[0]; i++)
			{
				if (one.four_three[i] == point)
				{
					if (i == one.four_three[0])
						return 0;
					else
						return one.four_three[++i];
				}
			}

		}
		else if (num == 5 || num == 6)
		{
			for (int i = 1; i < one.three_five[0]; i++)
			{
				if (one.three_five[i] == point)
				{
					if (i == one.three_five[0])
						return 0;
					else
						return one.three_five[++i];
				}
			}
			for (int i = 1; i < one.seven_five[0]; i++)
			{
				if (one.seven_five[i] == point)
				{
					if (i == one.seven_five[0])
						return 0;
					else
						return one.seven_five[++i];
				}
			}
			for (int i = 1; i < one.one_five[0]; i++)
			{
				if (one.one_five[i] == point)
				{
					if (i == one.one_five[0])
						return 0;
					else
						return one.one_five[++i];
				}
			}
			for (int i = 1; i < one.two_five[0]; i++)
			{
				if (one.two_five[i] == point)
				{
					if (i == one.two_five[0])
						return 0;
					else
						return one.two_five[++i];
				}
			}
			for (int i = 1; i < one.four_five[0]; i++)
			{
				if (one.four_five[i] == point)
				{
					if (i == one.four_five[0])
						return 0;
					else
						return one.four_five[++i];
				}
			}
		}
		else if (num == 4)
		{
			for (int i = 1; i < one.three_four[0]; i++)
			{
				if (one.three_four[i] == point)
				{
					if (i == one.three_four[0])
						return 0;
					else
						return one.three_four[++i];
				}
			}
			for (int i = 1; i < one.five_four[0]; i++)
			{
				if (one.five_four[i] == point)
				{
					if (i == one.five_four[0])
						return 0;
					else
						return one.five_four[++i];
				}
			}
			for (int i = 1; i < one.one_four[0]; i++)
			{
				if (one.one_four[i] == point)
				{
					if (i == one.one_four[0])
						return 0;
					else
						return one.one_four[++i];
				}
			}
			for (int i = 1; i < one.two_four[0]; i++)
			{
				if (one.two_four[i] == point)
				{
					if (i == one.two_four[0])
						return 0;
					else
						return one.two_four[++i];
				}
			}
			for (int i = 1; i < one.seven_four[0]; i++)
			{
				if (one.seven_four[i] == point)
				{
					if (i == one.seven_four[0])
						return 0;
					else
						return one.seven_four[++i];
				}
			}

		}
		else if (num == 7)
		{
			for (int i = 1; i < one.three_seven[0]; i++)
			{
				if (one.three_seven[i] == point)
				{
					if (i == one.three_seven[0])
						return 0;
					else
						return one.three_seven[++i];
				}
			}
			for (int i = 1; i < one.five_seven[0]; i++)
			{
				if (one.five_seven[i] == point)
				{
					if (i == one.five_seven[0])
						return 0;
					else
						return one.five_seven[++i];
				}
			}
			for (int i = 1; i < one.one_seven[0]; i++)
			{
				if (one.one_seven[i] == point)
				{
					if (i == one.one_seven[0])
						return 0;
					else
						return one.one_seven[++i];
				}
			}
			for (int i = 1; i < one.two_seven[0]; i++)
			{
				if (one.two_seven[i] == point)
				{
					if (i == one.two_seven[0])
						return 0;
					else
						return one.two_seven[++i];
				}
			}
			for (int i = 1; i < one.four_seven[0]; i++)
			{
				if (one.four_seven[i] == point)
				{
					if (i == one.four_seven[0])
						return 0;
					else
						return one.four_seven[++i];
				}
			}
		}

		return 0;
	}
	int win::accurate_pointer(float X, float Y)
	{
		int oto[12][4];
		int px = 10000;


		for (int i = 0; i < 12; i++)
		{
			if (X >= Roads[i][0])
				oto[i][0] = X - Roads[i][0];
			if (X < Roads[i][0])
				oto[i][0] = Roads[i][0] - X;
			if (Y >= Roads[i][1])
				oto[i][1] = Y - Roads[i][1];
			if (Y < Roads[i][1])
				oto[i][1] = Roads[i][1] - Y;
			oto[i][2] = oto[i][0] + oto[i][1];

			if (px >= oto[i][2])
				px = oto[i][2];
		}
		if (px < 5)
			return px;
		else
			return 50;
	}
	void win::menu()
	{
		int menuNum = 0;
		for (int i = 0; i < 7; i++)
			flag[i] = 0;

		RenderWindow window(VideoMode(320, 470), "Window");

		image but_1("button.png", 250, 24, 0, 0, 30, 30);
		image but_2("button.png", 250, 69, 0, 0, 30, 30);
		image but_3("button.png", 250, 114, 0, 0, 30, 30);
		image but_4("button.png", 250, 159, 0, 0, 30, 30);
		image but_5("button.png", 250, 204, 0, 0, 30, 30);
		image but_6("button.png", 250, 249, 0, 0, 30, 30);

		image not_but("roun2.png", 85, 320);

		image but_low("b1.png");

		image but_7("plus.png", 241, 305);
		image but_8("minus.png", 5, 305);
		image but_9("but_8.png", 60, 410, 0, 0, 200, 44);

		Font font;
		font.loadFromFile("SSR56__C.ttf");
		Text text("", font, 34);
		text.setFillColor(Color::Black);

		Font fon;
		fon.loadFromFile("ubuntu.ttf");
		Text size("", fon, 24);
		size.setFillColor(Color::Black);

		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}

			if (IntRect(250, 24, 30, 30).contains(Mouse::getPosition(window))) { menuNum = 1; }
			else if (IntRect(250, 69, 30, 30).contains(Mouse::getPosition(window))) { menuNum = 2; }
			else if (IntRect(250, 114, 30, 30).contains(Mouse::getPosition(window))) { menuNum = 3; }
			else if (IntRect(250, 159, 30, 30).contains(Mouse::getPosition(window))) { menuNum = 4; }
			else if (IntRect(250, 204, 30, 30).contains(Mouse::getPosition(window))) { menuNum = 5; }
			else if (IntRect(250, 249, 30, 30).contains(Mouse::getPosition(window))) { menuNum = 6; }

			else if (IntRect(241, 305, 74, 94).contains(Mouse::getPosition(window))) { menuNum = 7; }
			else if (IntRect(5, 305, 74, 94).contains(Mouse::getPosition(window))) { menuNum = 8; }
			else if (IntRect(60, 410, 200, 44).contains(Mouse::getPosition(window))) { menuNum = 9; }
			else { menuNum = 0; }

			if (Mouse::isButtonPressed(Mouse::Left)) 
			{
				if (flag[6] == 0)
				{
					if (menuNum == 1)
					{
						if (flag[0] == 0)
						{
							but_1.sprite.setTextureRect(IntRect(30, 0, 30, 30));
							flag[0] = 1;
						}
						else if (flag[0] == 1)
						{
							but_1.sprite.setTextureRect(IntRect(0, 0, 30, 30));
							flag[0] = 0;
						}
					}
					if (menuNum == 2)
					{
						if (flag[1] == 0)
						{
							but_2.sprite.setTextureRect(IntRect(30, 0, 30, 30));
							flag[1] = 1;
						}
						else if (flag[1] == 1)
						{
							but_2.sprite.setTextureRect(IntRect(0, 0, 30, 30));
							flag[1] = 0;
						}
					}
					if (menuNum == 3)
					{
						if (flag[2] == 0)
						{
							but_3.sprite.setTextureRect(IntRect(30, 0, 30, 30));
							flag[2] = 1;
						}
						else if (flag[2] == 1)
						{
							but_3.sprite.setTextureRect(IntRect(0, 0, 30, 30));
							flag[2] = 0;
						}
					}
					if (menuNum == 4)
					{
						if (flag[3] == 0)
						{
							but_4.sprite.setTextureRect(IntRect(30, 0, 30, 30));
							flag[3] = 1;
						}
						else if (flag[3] == 1)
						{
							but_4.sprite.setTextureRect(IntRect(0, 0, 30, 30));
							flag[3] = 0;
						}
					}
					if (menuNum == 5)
					{
						if (flag[4] == 0)
						{
							but_5.sprite.setTextureRect(IntRect(30, 0, 30, 30));
							flag[4] = 1;
						}
						else if (flag[4] == 1)
						{
							but_5.sprite.setTextureRect(IntRect(0, 0, 30, 30));
							flag[4] = 0;
						}
					}
					if (menuNum == 6)
					{
						if (flag[5] == 0)
						{
							but_6.sprite.setTextureRect(IntRect(30, 0, 30, 30));
							flag[5] = 1;
						}
						else if (flag[5] == 1)
						{
							but_6.sprite.setTextureRect(IntRect(0, 0, 30, 30));
							flag[5] = 0;
						}
					}
				}
				if (menuNum == 7)
				{
					if (min + 15 >= 720)
						min = 720;
					else
						min += 15;
				}
				if (menuNum == 8)
				{
					if (min - 15 < 0)
						min = 0;
					else
						min -= 15;
				}
				if (menuNum == 9)
				{
					if (flag[6] == 0)
					{
						but_9.sprite.setTextureRect(IntRect(200, 0, 200, 44));
						flag[6] = 1;
					}
					else if (flag[6] == 1)
					{
						but_9.sprite.setTextureRect(IntRect(0, 0, 200, 44));
						flag[6] = 0;
					}
				}
				Sleep(100);
			}

			window.clear();
			window.draw(but_low.sprite);
			window.draw(but_1.sprite);
			window.draw(but_2.sprite);
			window.draw(but_3.sprite);
			window.draw(but_4.sprite);
			window.draw(but_5.sprite);
			window.draw(but_6.sprite);
			window.draw(but_7.sprite);
			window.draw(but_8.sprite);
			window.draw(but_9.sprite);
			window.draw(not_but.sprite);

			ostringstream a, b;
			a << "Ёкстерьер\n»скуство\nѕарки\n–елиги€\nѕам€тники\nћузеи";
			b << min;
			size.setString(b.str() + " min");
			size.setPosition(100, 335);

			text.setString(a.str());
			text.setPosition(10, 10);
			SetConsoleCP(1251);
			SetConsoleOutputCP(1251);

			window.draw(text);
			window.draw(size);

			window.display();
		}
	}

	void win::test(float x, float y)
	{
		//int b[6] = { 0,0,0,1,1,1 };

		/*int* g = new int[6];
		for (int i = 0; i < 6; i++)
			g[i] = b[i];*/

		QL::Q_learning ql;
		//ql.initializeQ();
		ql.fake(flag, range_to_objects(x, y), min);

		/*for (int i = 0; i <= 11; i++)
			cout << g[i] << " ";*/

		//cout << ql.predict() << endl;

	}

	float* win::range_to_objects(float x, float y)
	{
		float cache[10];

		for (int i = 0; i < 10; i++)
		{
			cache[i] = 0;
			if (x >= Attraction[i][0])
				cache[i] += x - Attraction[i][0];
			if (x < Attraction[i][0])
				cache[i] += Attraction[i][0] - x;
			if (y >= Attraction[i][1])
				cache[i] += y - Attraction[i][1];
			if (y < Attraction[i][1])
				cache[i] += Attraction[i][1] - y;

			//cout << cache[i] << "  ";
		}
		//cout << "\n";
		
		return cache;
	}
	win::~win()
	{
	}
}
