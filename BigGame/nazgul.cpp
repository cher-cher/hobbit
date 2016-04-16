#include "nazgul.h"
#include <SFML/Graphics.hpp>
#include <iostream> 
#include "player.h"
#include "const.h"
#include <cmath>

void DrawNazgul(RenderWindow & window, Nazgul & nazgul)
{
	window.draw(nazgul.sprite);
}

void NazgulCollision(Nazgul & nazgul, float & time, vector<string> & TileMap)
{
	if ((nazgul.y < 0) || (nazgul.x < 0) || (nazgul.x > WIDTH_MAP * SIZE_BLOCK) || (nazgul.y > HEIGHT_MAP * (SIZE_BLOCK - 1)))
	{
		nazgul.life = false;
	}
	if (nazgul.life)
	{
		for (int i = nazgul.y / SIZE_BLOCK; i < (nazgul.y + HEIGHT_NAZGUL) / SIZE_BLOCK; i++)
		{
			for (int j = nazgul.x / SIZE_BLOCK; j < (nazgul.x + WIDTH_NAZGUL) / SIZE_BLOCK; j++)
			{
				if ((TileMap[i][j] == 'w') || (TileMap[i][j] == 'k') || (TileMap[i][j] == 'n') || (TileMap[i][j] == 'e') || (TileMap[i][j] == 'x'))
				{
					Vector2f pos = nazgul.sprite.getPosition();
					if (nazgul.dy > 0)
					{
						nazgul.y = i * SIZE_BLOCK - HEIGHT_NAZGUL;
						pos.y -= nazgul.dy*time;
					}
					if (nazgul.dy < 0)
					{
						nazgul.y = i * SIZE_BLOCK + SIZE_BLOCK;
						pos.y -= nazgul.dy*time;
					}
					if (nazgul.dx > 0)
					{
						nazgul.x = j * SIZE_BLOCK - WIDTH_NAZGUL;
						pos.x -= nazgul.dx*time;
					}
					if (nazgul.dx < 0)
					{
						nazgul.x = j * SIZE_BLOCK + SIZE_BLOCK;
						pos.x -= nazgul.dx*time;
					}
					nazgul.sprite.setPosition(pos);
					nazgul.direction = rand() % 4;
				}
			}
		}
	}
}

FloatRect GetRect(Nazgul & nazgul)
{
	return FloatRect(nazgul.x, nazgul.y, nazgul.w, nazgul.h);
}

void RoadToHobbit(Nazgul & nazgul, Player & player)
{

}

void NazgulUpdate(Nazgul & nazgul, float & time, vector<string> & TileMap, Game & game, Player & player)
{

	switch (nazgul.direction)
	{
	case Direction::RIGHT:
	{
		nazgul.dx = nazgul.speed;
		nazgul.dy = 0;
		nazgul.sprite.setTextureRect(IntRect(WIDTH_NAZGUL, 0, WIDTH_NAZGUL, HEIGHT_NAZGUL));
		break;
	}
	case Direction::LEFT:
	{
		nazgul.dx = -nazgul.speed;
		nazgul.dy = 0;
		nazgul.sprite.setTextureRect(IntRect(0, 0, WIDTH_NAZGUL, HEIGHT_NAZGUL));
		break;
	}
	case Direction::DOWN:
	{
		nazgul.dx = 0;
		nazgul.dy = nazgul.speed;
		break;
	}
	case Direction::UP:
	{
		nazgul.dx = 0;
		nazgul.dy = -nazgul.speed;
		break;
	}

	}
	if (game.invisibleMood)
	{
		AttackMode(player, nazgul, time);
	}
	else
	{
		nazgul.x += nazgul.dx * time;
		nazgul.y += nazgul.dy * time;
	}
	NazgulCollision(nazgul, time, TileMap);

	nazgul.sprite.setPosition(nazgul.x, nazgul.y);
	nazgul.rect = { (int)nazgul.x, (int)nazgul.y, WIDTH_NAZGUL, HEIGHT_NAZGUL };
	
}

void AttackMode(Player & player, Nazgul & nazgul, float time)
{
	if (player.x > nazgul.x)//увеличиваем
	{
		nazgul.dx = nazgul.speed;
	}
	if (player.x < nazgul.x)//уменьшаем
	{
		nazgul.dx = -nazgul.speed;
	}
	if (player.y < nazgul.y)//увеличиваем
	{
		nazgul.dy = -nazgul.speed;
	}
	if (player.y > nazgul.y)//уменьшаем
	{
		nazgul.dy = nazgul.speed;
	}
	if (abs(player.x - nazgul.x) < abs(player.y - nazgul.y))
	{
		nazgul.dx = 0;
	}
	else
	{
		nazgul.dy = 0;
	}
	nazgul.x += nazgul.dx * time;
	nazgul.y += nazgul.dy * time;
}