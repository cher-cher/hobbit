#ifndef Player_H
#define Player_H
#include <SFML/Graphics.hpp>
#include <iostream> 
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

enum Direction
{
	RIGHT = 0,
	LEFT = 1,
	DOWN = 2,
	UP = 3
};

struct Player
{
	float currentAnimationFrame = 0;
	unsigned animationFramesCount = 3;
	Sprite elf;
	float x = 100;
	float y = 100;
	float dx;
	float dy;
	Direction direction = Direction::RIGHT;
	float speed = 0;
	int health = 100;
	bool life = true;
};

Position SyncPlayerPostion(Player & player);
void DrawPlayer(RenderWindow &window, Player * player);
void CheckPlayerCollision(Player & player);
void Update(float time, Player & player);
#endif