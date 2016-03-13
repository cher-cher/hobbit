#include <SFML/Graphics.hpp>
#include <iostream> 
#include "map.h"
#include "player.h"
#include "view.h"
#include "const.h"

using namespace sf;

void Menu(RenderWindow & window) 
{
	Texture menuTexture1, menuTexture2, menuBackground;
	menuTexture1.loadFromFile("images/Start1.png");
	menuTexture2.loadFromFile("images/Exit1.png");
	menuBackground.loadFromFile("images/BackGround11.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(300, 225);
	menu2.setPosition(300, 275);
	menuBg.setPosition(0, 0);

	while (isMenu)
	{
		menu1.setColor(Color::Black);
		menu2.setColor(Color::Black);
		menuNum = 0;

		if (IntRect(300, 250, 300, 75).contains(Mouse::getPosition(window))) { menu1.setColor(Color(192, 192, 192)); menuNum = 1; }
		if (IntRect(300, 300, 300, 75).contains(Mouse::getPosition(window))) { menu2.setColor(Color(192, 192, 192)); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;//если нажали первую кнопку, то выходим из меню 
			if (menuNum == 2) { window.close(); isMenu = false; }

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);

		window.display();
	}
}

void CheckPlayerCollision(Player & player, float time)
{
	for (int i = player.y / SIZE_BLOCK; i < (player.y + HEIGHT_PLAYER) / SIZE_BLOCK; i++)//проходимся по тайликам, контактирующим с игроком,, то есть по всем квадратикам размера 32*32, которые мы окрашивали в 9 уроке. про условия читайте ниже.
		for (int j = player.x / SIZE_BLOCK; j < (player.x + WIDTH_PLAYER) / SIZE_BLOCK; j++)//икс делим на 32, тем самым получаем левый квадратик, с которым персонаж соприкасается. (он ведь больше размера 32*32, поэтому может одновременно стоять на нескольких квадратах). А j<(x + w) / 32 - условие ограничения координат по иксу. то есть координата самого правого квадрата, который соприкасается с персонажем. таким образом идем в цикле слева направо по иксу, проходя по от левого квадрата (соприкасающегося с героем), до правого квадрата (соприкасающегося с героем)
		{
			if (TileMap[i][j] == 'w')
			{
				Vector2f pos = player.elf.getPosition();
				if (player.dy > 0)//если мы шли вниз,
				{
					player.y = i * SIZE_BLOCK - HEIGHT_PLAYER;//то стопорим координату игрек персонажа. сначала получаем координату нашего квадратика на карте(стены) и затем вычитаем из высоты спрайта персонажа.
					pos.y -= player.dy*time;
				}
				if (player.dy < 0)
				{
					player.y = i * SIZE_BLOCK + SIZE_BLOCK;//аналогично с ходьбой вверх. dy<0, значит мы идем вверх (вспоминаем координаты паинта)
					pos.y -= player.dy*time;
				}
				if (player.dx > 0)
				{
					player.x = j * SIZE_BLOCK - WIDTH_PLAYER;//если идем вправо, то координата Х равна стена (символ 0) минус ширина персонажа
					pos.x -= player.dx*time;
				}
				if (player.dx < 0)
				{
					player.x = j * SIZE_BLOCK + SIZE_BLOCK;//аналогично идем влево
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

float ProcessInput(Player &player, float time)
{
	bool syncPlayerNeeded = false;

	if ((Keyboard::isKeyPressed(Keyboard::Left))
		|| (Keyboard::isKeyPressed(Keyboard::Right))
		|| (Keyboard::isKeyPressed(Keyboard::Up))
		|| (Keyboard::isKeyPressed(Keyboard::Down)))
	{
		player.speed = 0.15;
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
	}
	return CurrentFrameMoney;
}

int main()
{
	Player player;
	RenderWindow window(sf::VideoMode(900, 600), "big game");
	Menu(window);

	view.reset(FloatRect(0, 0, 1000, 600));

	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/mmap.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Image money_image;//объект изображения для карты
	money_image.loadFromFile("images/money.png");//загружаем файл для карты
	Texture money;//текстура карты
	money.loadFromImage(money_image);//заряжаем текстуру картинкой
	Sprite s_money;//создаём спрайт для карты
	s_money.setTexture(money);//заливаем текстуру спрайтом

	Texture herotexture;
	herotexture.loadFromFile("images/hero1.png");

	player.elf.setTexture(herotexture);
	player.elf.setTextureRect(IntRect(0, 0, WIDTH_PLAYER, HEIGHT_PLAYER));

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