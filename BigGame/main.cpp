#include <SFML/Graphics.hpp>
#include <iostream> 
#include "map.h"
#include "player.h"
#include "view.h"
#include "const.h"

using namespace sf;

void CheckPlayerCollision(Player & player, float time)//�-��� �������������� � ������
{

	for (int i = player.y / SIZE_BLOCK; i < (player.y + HEIGHT_PLAYER) / SIZE_BLOCK; i++)//���������� �� ��������, �������������� � �������,, �� ���� �� ���� ����������� ������� 32*32, ������� �� ���������� � 9 �����. ��� ������� ������� ����.
		for (int j = player.x / SIZE_BLOCK; j < (player.x + WIDTH_PLAYER) / SIZE_BLOCK; j++)//��� ����� �� 32, ��� ����� �������� ����� ���������, � ������� �������� �������������. (�� ���� ������ ������� 32*32, ������� ����� ������������ ������ �� ���������� ���������). � j<(x + w) / 32 - ������� ����������� ��������� �� ����. �� ���� ���������� ������ ������� ��������, ������� ������������� � ����������. ����� ������� ���� � ����� ����� ������� �� ����, ������� �� �� ������ �������� (���������������� � ������), �� ������� �������� (���������������� � ������)
		{
			if (TileMap[i][j] == 'w')
			{
				Vector2f pos = player.elf.getPosition();
				if (player.dy > 0)//���� �� ��� ����,
				{
					player.y = i * SIZE_BLOCK - HEIGHT_PLAYER;//�� �������� ���������� ����� ���������. ������� �������� ���������� ������ ���������� �� �����(�����) � ����� �������� �� ������ ������� ���������.
					pos.y -= player.dy*time;
				}
				if (player.dy < 0)
				{
					player.y = i * SIZE_BLOCK + SIZE_BLOCK;//���������� � ������� �����. dy<0, ������ �� ���� ����� (���������� ���������� ������)
					pos.y -= player.dy*time;
				}
				if (player.dx > 0)
				{
					player.x = j * SIZE_BLOCK - WIDTH_PLAYER;//���� ���� ������, �� ���������� � ����� ����� (������ 0) ����� ������ ���������
					pos.x -= player.dx*time;
				}
				if (player.dx < 0)
				{
					player.x = j * SIZE_BLOCK + SIZE_BLOCK;//���������� ���� �����
					pos.x -= player.dx*time;
				}
				player.elf.setPosition(pos);
			}

			if (TileMap[i][j] == 'm') { 
				TileMap[i][j] = 's';
			}
		}
}

void Update(float time, Player & player)
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

	player.speed = 0;

	player.elf.setPosition(player.x, player.y);
	CheckPlayerCollision(player, time);
}

///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
float ProcessInput(Player &player, float time)
{
	bool syncPlayerNeeded = false;

	if ((Keyboard::isKeyPressed(Keyboard::Left))
		|| (Keyboard::isKeyPressed(Keyboard::Right))
		|| (Keyboard::isKeyPressed(Keyboard::Up))
		|| (Keyboard::isKeyPressed(Keyboard::Down)))
	{
		player.speed = 0.1;
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

float DrawMap(Sprite &s_map, float CurrentFrameMoney, float time, Sprite &s_money, RenderWindow &window)
{
	for (int i = 0; i < HEIGHT_MAP; i++)
	{
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == 's')
			{
				s_map.setTextureRect(IntRect(0, 0, SIZE_BLOCK, SIZE_BLOCK));
			}
			if (TileMap[i][j] == 'h')
			{
				s_map.setTextureRect(IntRect(10 * SIZE_BLOCK, 0, SIZE_BLOCK, SIZE_BLOCK));
			}
			if (TileMap[i][j] == 'w')
			{
				s_map.setTextureRect(IntRect(SIZE_BLOCK, 0, SIZE_BLOCK, SIZE_BLOCK));
			}
			if (TileMap[i][j] == 'm')
			{
				CurrentFrameMoney += 0.001*time;
				if (CurrentFrameMoney > 7) CurrentFrameMoney -= 7;
				s_money.setTextureRect(IntRect(SIZE_BLOCK * int(CurrentFrameMoney), 0, SIZE_BLOCK, SIZE_BLOCK));
				s_money.setPosition(j * SIZE_BLOCK, i * SIZE_BLOCK);
			}

			s_map.setPosition(j * SIZE_BLOCK, i * SIZE_BLOCK);
			window.draw(s_map);
			window.draw(s_money);
		}
	}		return CurrentFrameMoney;
}

int main()
{
	Player player;
	RenderWindow window(sf::VideoMode(900, 600), "big game");

	view.reset(FloatRect(0, 0, 1000, 600));

	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/mmap.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	Image money_image;//������ ����������� ��� �����
	money_image.loadFromFile("images/money.png");//��������� ���� ��� �����
	Texture money;//�������� �����
	money.loadFromImage(money_image);//�������� �������� ���������
	Sprite s_money;//������ ������ ��� �����
	s_money.setTexture(money);//�������� �������� ��������

	Texture herotexture;
	herotexture.loadFromFile("images/hero4.png");

	player.elf.setTexture(herotexture);
	player.elf.setTextureRect(IntRect(0, 0, 64, 96));
	//player.elf.setPosition(1792, 768);

	//float currentPlayerAnimationFrame = 0;//������ ������� ����
	float CurrentFrameMoney = 0;
	Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time * 0.001;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (player.life)
		{
			player.currentAnimationFrame = ProcessInput(player, time);
		}
		

		GetPlayerCoordinateForView(player.x, player.y);
		Update(time, player);
		ViewMap(time, player);
		window.setView(view);

		window.clear();

		CurrentFrameMoney = DrawMap(s_map, CurrentFrameMoney, time, s_money, window);

		DrawPlayer(window, &player);
		window.display();
	}

	return 0;
}