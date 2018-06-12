#include "player.h"

namespace Players
{
	player::player(String File, float X, float Y)
	{
		image.loadFromFile("img/" + File);
		texture.loadFromImage(image);//закидываем наше изображение в текстуру
		sprite.setTexture(texture);//заливаем спрайт текстурой
		x = X; y = Y;//координата по¤влени¤ спрайта
		sprite.setTexture(texture);

		sprite.setPosition(x, y);
	}

	void player::color_player()
	{
		srand(time(nullptr));
		int a[3];
		for (int i = 0; i<3; i++)
			a[i] = rand() % (255);

		sprite.setColor(Color::Color(a[0], a[1], a[2]));
	}

	void player::motion(string b, int P_X, int P_Y, float time, int status)
	{
		//speed = 25;
		//system("pause");
		if (b == "STOP")
		{
			dx = 0;
			dy = 0;
		}
		else if (b == "TELEPORT")
		{
			x = 1562; 
			y = 957;
			sprite.setPosition(x, y);
			return;
		}
		else if (b == "UP")
		{
			speed = 0.1; dx = 0; dy = -speed;
		}
		else if (b == "DOWN")
		{
			speed = 0.1; dx = 0; dy = speed;
		}
		else if (b == "LEFT")
		{
			speed = 0.1; dx = -speed; dy = 0; //system("pause");
		}
		else if (b == "RIGHT")
		{
			speed = 0.1; dx = speed; dy = 0;
		}

		
		x += dx * time;
		y += dy * time;

		//cout << P_X << "  " << P_Y << endl;
		speed = 0;
		sprite.setPosition(x, y);
	}

	String player::network_player(string b, int P_X, int P_Y)
	{
		if (b == "TELEPORT")
			return "TELEPORT";

		if (P_X > x)
		{
			if ((P_X - x) < 1)
			{
				if (b == "RIGHT")
					x += P_X - x;
			}
		}
		else if (P_Y > y)
		{
			if ((P_Y - y) < 1)
			{
				if (b == "DOWN")
					y += P_Y - y;
			}
		}
		else if (P_X < x)
		{
			if ((x - P_X) < 1)
			{
				if (b == "LEFT")
					x -= x - P_X;
			}
		}
		else if (P_Y < y)
		{
			if ((y - P_Y) < 1)
			{
				if (b == "UP")
					y -= y - P_Y;
			}
		}

		if (x < P_X)
			b = "RIGHT";
		else if (x > P_X)
			b = "LEFT";
		else if (y < P_Y)
			b = "DOWN";
		else if (y > P_Y)
			b = "UP";

		return b;
	}
}