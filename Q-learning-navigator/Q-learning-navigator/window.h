#pragma once
#include <thread>
#include "headers.h"
#include "player.h"
#include "Q_learning.h"
//#include "menu.h"

using namespace Players;
//using namespace MENU;

namespace Win
{
	class win
	{
	private:
		Clock clock;
		float time_window;
		int window_x = 870, window_y = 530;
		string lave;
		View view;

		int Roads[12][2];
		int Attraction[10][2];
		int cache_log[2];
		int cache_x, cache_y;

		int status, status_2;
		int point, point_2, point_3;

		int min;
		int flag[7];
	public:
		win();
		void main();
		player logic(player p);
		void start_options();
		int swap_point(float x, float y);
		View GetPlayerView(int x, int y);
		int route_search(int num, int point);
		int accurate_pointer(float x, float y);
		float* range_to_objects(float x, float y);
		void menu();
		void test(float x, float y);
		~win();
	};
	class image
	{
	public:
		Texture texture;
		Sprite sprite;
		string File;

		image(string File, int dx = 0, int dy = 0)
		{
			texture.loadFromFile("img/" + File);
			sprite.setTexture(texture);
			sprite.setPosition(dx, dy);
		}
		image(string File, int dx, int dy, int t1, int t2, int t3, int t4)
		{
			texture.loadFromFile("img/" + File);
			sprite.setTexture(texture);
			sprite.setTextureRect(IntRect(t1, t2, t3, t4));
			sprite.setPosition(dx, dy);
		}
	};
}
