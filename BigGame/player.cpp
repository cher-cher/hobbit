#include <SFML/Graphics.hpp>
#include <iostream> 
#include "player.h"
#include "const.h"
//#include "map.h"

void DrawPlayer(RenderWindow & window, Player * player)
{
	window.draw(player->elf);
}

Position SyncPlayerPostion(Player & player)
{
	Vector2f pos = player.elf.getPosition();
	player.x = pos.x;
	player.y = pos.y;
	return Position(player.x, player.y);
}
void CheckPlayerCollision(Player & player, float time, int &counterCoins, String TileMap[])
{
	for (int i = player.y / SIZE_BLOCK; i < (player.y + HEIGHT_PLAYER) / SIZE_BLOCK; i++)
		for (int j = player.x / SIZE_BLOCK; j < (player.x + WIDTH_PLAYER) / SIZE_BLOCK; j++)
		{
			if (TileMap[i][j] == 'w')
			{
				Vector2f pos = player.elf.getPosition();
				if (player.dy > 0)
				{
					player.y = i * SIZE_BLOCK - HEIGHT_PLAYER;
					pos.y -= player.dy*time;
				}
				if (player.dy < 0)
				{
					player.y = i * SIZE_BLOCK + SIZE_BLOCK;
					pos.y -= player.dy*time;
				}
				if (player.dx > 0)
				{
					player.x = j * SIZE_BLOCK - WIDTH_PLAYER;
					pos.x -= player.dx*time;
				}
				if (player.dx < 0)
				{
					player.x = j * SIZE_BLOCK + SIZE_BLOCK;
					pos.x -= player.dx*time;
				}
				player.elf.setPosition(pos);
			}

			if (TileMap[i][j] == 'm')
			{
				TileMap[i][j] = 's';
				counterCoins += 1;
			}
		}
}
void UpdatePlayer(float time, Player & player, int &counterCoins, String TileMap[])
{
	switch (player.direction)
	{
	case Direction::RIGHT:
	{
		player.dx = player.speed;
		player.dy = 0;
		break;
	}
	case Direction::LEFT:
	{
		player.dx = -player.speed;
		player.dy = 0;
		break;
	}
	case Direction::DOWN:
	{
		player.dx = 0;
		player.dy = player.speed;
		break;
	}
	case Direction::UP:
	{
		player.dx = 0;
		player.dy = -player.speed;
		break;
	}

	}

	player.x += player.dx*time;
	player.y += player.dy*time;

	player.rect = { (int)player.x, (int)player.y, WIDTH_PLAYER, HEIGHT_PLAYER};

	player.speed = 0;

	player.elf.setPosition(player.x, player.y);
	CheckPlayerCollision(player, time, counterCoins, TileMap);
}
float ProcessInput(Player &player, float time)
{
	bool syncPlayerNeeded = false;

	if ((Keyboard::isKeyPressed(Keyboard::Left))
		|| (Keyboard::isKeyPressed(Keyboard::Right))
		|| (Keyboard::isKeyPressed(Keyboard::Up))
		|| (Keyboard::isKeyPressed(Keyboard::Down)))
	{
		player.speed = 0.2;
		player.currentAnimationFrame += 0.005*time;
		player.currentAnimationFrame = std::fmod(player.currentAnimationFrame, player.animationFramesCount);
		syncPlayerNeeded = true;
	}

	if ((Keyboard::isKeyPressed(Keyboard::Left))) {
		player.direction = Direction::LEFT;
		player.elf.setTextureRect(IntRect(WIDTH_PLAYER * int(player.currentAnimationFrame), HEIGHT_PLAYER, WIDTH_PLAYER, HEIGHT_PLAYER));
	}

	if ((Keyboard::isKeyPressed(Keyboard::Right))) {
		player.direction = Direction::RIGHT;
		player.elf.setTextureRect(IntRect(WIDTH_PLAYER * int(player.currentAnimationFrame), 2 * HEIGHT_PLAYER, WIDTH_PLAYER, HEIGHT_PLAYER));
	}


	if ((Keyboard::isKeyPressed(Keyboard::Up))) {
		player.direction = Direction::UP;
		player.elf.setTextureRect(IntRect(WIDTH_PLAYER * int(player.currentAnimationFrame), 3 * HEIGHT_PLAYER, WIDTH_PLAYER, HEIGHT_PLAYER));
	}

	if ((Keyboard::isKeyPressed(Keyboard::Down))) {
		player.direction = Direction::DOWN;
		player.elf.setTextureRect(IntRect(WIDTH_PLAYER * int(player.currentAnimationFrame), 0 * HEIGHT_PLAYER, WIDTH_PLAYER, HEIGHT_PLAYER));
	}

	if (syncPlayerNeeded)
	{
		SyncPlayerPostion(player);
	}

	return player.currentAnimationFrame;
}