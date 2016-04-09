#include <SFML/Graphics.hpp>
#include <iostream> 
#include "const.h"

using namespace sf;

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
	Nazgul(Sprite & spr, float posX, float posY, int dir)
	{
		x = posX;
		y = posY;
		direction = dir;
		sprite = spr;
		rect = {(int)x, (int)y, WIDTH_NAZGUL, HEIGHT_NAZGUL};
	}
};

void DrawNazgul(RenderWindow & window, Nazgul * nazgul);
void NazgulCollision(Nazgul & nazgul, float & time, String TileMap[]);
FloatRect GetRect(Nazgul & nazgul);
void NazgulUpdate(Nazgul & nazgul, float & time, String TileMap[]);