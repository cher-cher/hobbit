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
	if ((nazgul.y < 0) || (nazgul.x < 0) || (nazgul.x > 900) || (nazgul.y > 600))
	{
		nazgul.life = false;
	}
	for (int i = nazgul.y / SIZE_BLOCK; i < (nazgul.y + HEIGHT_NAZGUL) / SIZE_BLOCK; i++)
		for (int j = nazgul.x / SIZE_BLOCK; j < (nazgul.x + WIDTH_NAZGUL) / SIZE_BLOCK; j++)
		{
			if (TileMap[i][j] == 'w')
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

FloatRect GetRect(Nazgul & nazgul)
{
	return FloatRect(nazgul.x, nazgul.y, nazgul.w, nazgul.h);
}

void NazgulUpdate(Nazgul & nazgul, float & time, vector<string> & TileMap)
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

	nazgul.x += nazgul.dx * time;
	nazgul.y += nazgul.dy * time;
	
	nazgul.sprite.setPosition(nazgul.x, nazgul.y);
	NazgulCollision(nazgul, time, TileMap);
	nazgul.rect = { (int)nazgul.x, (int)nazgul.y, WIDTH_NAZGUL, HEIGHT_NAZGUL };
	
}