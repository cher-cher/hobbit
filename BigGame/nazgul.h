#include <SFML/Graphics.hpp>
#include <iostream> 
#include "const.h"
#include <string>

using namespace sf;
using namespace std;

struct Nazgul
{
	Sprite sprite;
	float x;
	float y;
	float w;
	float h;
	float dx;
	float dy;
	int direction;
	IntRect rect;
	float speed = 0.1;
	bool life;
	Nazgul(Sprite & spr, float posX, float posY, int dir)
	{
		life = true;
		x = posX;
		y = posY;
		direction = dir;
		sprite = spr;
		rect = {(int)x, (int)y, WIDTH_NAZGUL, HEIGHT_NAZGUL};
		sprite.setTextureRect(IntRect(WIDTH_NAZGUL, 0, WIDTH_NAZGUL, HEIGHT_NAZGUL));
	}
};

void DrawNazgul(RenderWindow & window, Nazgul & nazgul);
void NazgulCollision(Nazgul & nazgul, float & time, vector<string> & TileMap);
FloatRect GetRect(Nazgul & nazgul);
void NazgulUpdate(Nazgul & nazgul, float & time, vector<string> & TileMap);