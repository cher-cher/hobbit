#ifndef Player_H
#define Player_H
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "const.h"
//#include "map.h"

using namespace sf;

struct Position
{
	float x;
	float y;

	Position(float newX, float newY)
		: x(newX)
		, y(newY)
	{ };
};



struct Player
{
	float currentAnimationFrame = 0;
	unsigned animationFramesCount = 3;
	Sprite elf;
	float x = 100;
	float y = 100;
	float w;
	float h;
	float dx;
	float dy;
	Direction direction = Direction::RIGHT;
	float speed = 0;
	int health = 100;
	bool life = true;
	IntRect rect;
};

Position SyncPlayerPostion(Player & player);
void DrawPlayer(RenderWindow &window, Player * player);
void CheckPlayerCollision(Player & player, float time, int &counterCoins, String TileMap[]);
FloatRect GetRect(Player & player);
void UpdatePlayer(float time, Player & player, int &counterCoins, String TileMap[]);
float ProcessInput(Player &player, float time);
#endif