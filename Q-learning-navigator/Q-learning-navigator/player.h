#pragma once

#include "headers.h"
//#include "View.h"

namespace Players
{
	class player
	{
	private:
		Image image;//сфмл изображение
		Texture texture;//сфмл текстура
		float dx, dy, speed;
	public:
		float x, y;
		Sprite sprite;//сфмл спрайт
		int retu = 0;
	public:
		player(String F, float X, float Y);
		void color_player();
		void motion(string b, int P_X, int P_Y, float time, int status);
		String network_player(string b, int oto, int tot);
	};

}