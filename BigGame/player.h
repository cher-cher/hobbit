#ifndef Player_H
#define Player_H
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "const.h"
#include "game.h"

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
	float x = 200;
	float y = 200;
	Sprite elf;
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
void CheckPlayerCollision(Player & player, float time, int &counterCoins, Game & game, vector<string> & TileMap);
FloatRect GetRect(Player & player);
void UpdatePlayer(float time, Player & player, int &counterCoins, Game & game, vector<string> & TileMap);
float ProcessInput(Player &player, float time);
#endif