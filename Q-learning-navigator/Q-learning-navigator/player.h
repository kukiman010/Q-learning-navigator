#pragma once

#include "headers.h"

namespace Players
{
	class player
	{
	private:
		Image image;
		Texture texture;
		float dx, dy, speed;
	public:
		float x, y;
		Sprite sprite;
		int retu = 0;
	public:
		player(String F, float X, float Y);
		void color_player();
		void motion(string b, int P_X, int P_Y, float time, int status);
		String network_player(string b, int oto, int tot);
	};
}
