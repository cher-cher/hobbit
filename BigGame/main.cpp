#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include "map.h"
#include "player.h"
#include "view.h"
#include "const.h"
#include <time.h>
#include "nazgul.h"
#include <cmath>

using namespace sf;
using namespace std;

void SelectPlayer(RenderWindow &window)
{
	
}

void Menu(RenderWindow & window) 
{
	Music musicMenu;
	musicMenu.openFromFile("audio/menu.wav");
	Texture menuTexture1, menuTexture2, menuTexture3, menuBackground, menuSelectPlayer;
	menuTexture1.loadFromFile("images/start.png");
	menuTexture2.loadFromFile("images/exit.png");
	menuTexture3.loadFromFile("images/hobbit.png");
	menuBackground.loadFromFile("images/BackGround11.png");
	menuSelectPlayer.loadFromFile("images/BackGround111.png");
	Sprite menu1(menuTexture1), menu2(menuTexture2), hobbit(menuTexture3), menuBg(menuBackground), menuSelect(menuSelectPlayer);
	bool isMenu = 1;
	int menuNum = 0;
	hobbit.setPosition(325, 75);
	menu1.setPosition(325, 375);
	menu2.setPosition(325, 425);
	menuBg.setPosition(0, 0);
	musicMenu.play();
	while (isMenu)
	{
		menu1.setColor(Color::Black);
		menu2.setColor(Color::Black);
		hobbit.setColor(Color::Black);
		menuNum = 0;

		if (IntRect(325, 375, 250, 75).contains(Mouse::getPosition(window))) { menu1.setColor(Color::White); menuNum = 1; }
		if (IntRect(325, 425, 250, 75).contains(Mouse::getPosition(window))) { menu2.setColor(Color::White); menuNum = 2; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
			{
				isMenu = false;
			}
			if (menuNum == 2) 
			{ 
				window.close(); isMenu = false; 
			}

		}

		window.draw(menuBg);
		window.draw(menu1);
		window.draw(menu2);
		window.draw(hobbit);

		window.display();
	}
}

void DrawMap(Sprite &s_map, float &CurrentFrameMoney, float time, Sprite &s_money, RenderWindow &window)
{
	for (int i = 0; i < HEIGHT_MAP; i++)
	{
		for (int j = 0; j < WIDTH_MAP; j++)
		{
			if (TileMap[i][j] == 's')
			{
				s_map.setTextureRect(IntRect(0, 0, SIZE_BLOCK, SIZE_BLOCK));
				s_map.setPosition(j * SIZE_BLOCK, i * SIZE_BLOCK);
				window.draw(s_map);
			}
			if (TileMap[i][j] == 'w')
			{
				s_map.setTextureRect(IntRect(SIZE_BLOCK, 0, SIZE_BLOCK, SIZE_BLOCK));
				s_map.setPosition(j * SIZE_BLOCK, i * SIZE_BLOCK);
				window.draw(s_map);
			}
			if (TileMap[i][j] == 'm')
			{
				s_money.setTextureRect(IntRect(SIZE_BLOCK * int(CurrentFrameMoney), 0, SIZE_BLOCK, SIZE_BLOCK));
				s_money.setPosition(j * SIZE_BLOCK, i * SIZE_BLOCK);
				window.draw(s_money);
			}
		}
	}
	CurrentFrameMoney += time * 0.015;
	if (CurrentFrameMoney > 7) CurrentFrameMoney -= 7;
}

void TimeGame(RenderWindow &window,Text &text, int gameTime, int &timer)
{
	std::ostringstream gameTimeString;   
	gameTimeString << timer - gameTime;
	text.setString("Time: " + gameTimeString.str());
	text.setPosition(view.getCenter().x - 450, view.getCenter().y - 300);
}

void CounterCoins(RenderWindow &window, Text &text1, int counterCoins)
{
	std::ostringstream gameCounterCoinsString;
	gameCounterCoinsString << counterCoins;
	text1.setString("Coins: " + gameCounterCoinsString.str());
	text1.setPosition(view.getCenter().x + 300, view.getCenter().y - 300);
}

void EntitiesIntersection(Player & player, vector<Nazgul*> &enemies, int & timer)
{
	vector<Nazgul*> ::iterator enemies1 = enemies.begin();
	vector<Nazgul*> ::iterator enemies2;

	for (enemies2 = enemies.begin(); enemies2 != enemies.end(); enemies2++) {
		for (enemies1 = enemies.begin(); enemies1 != enemies.end(); enemies1++) 
		{
			if (((*enemies1)->rect.intersects((*enemies2)->rect)))
			{
				if (((*enemies1)->rect) != ((*enemies2)->rect))
				{
					(*enemies1)->direction = 3;
					(*enemies2)->direction = 1;
				}
			}
			else if (((*enemies1)->rect.intersects((player.rect))))
			{
				//timer -= 10;
				if ((*enemies1)->dx > 0)
				{
					(*enemies1)->x = player.x - WIDTH_NAZGUL;
					(*enemies1)->direction = rand() % 4;
					if (player.dx < 0)
					{
						player.x = (*enemies1)->x + WIDTH_NAZGUL;
					}
				}
				if ((*enemies1)->dx < 0)
				{
					(*enemies1)->x = player.x + WIDTH_NAZGUL;
					(*enemies1)->direction = rand() % 4;
					if (player.dx > 0)
					{
						player.x = (*enemies1)->x - WIDTH_NAZGUL;
					}
				}
				if ((*enemies1)->dy > 0)
				{
					(*enemies1)->y = player.y - HEIGHT_NAZGUL;
					(*enemies1)->direction = rand() % 4;
					if (player.dy < 0)
					{
						player.y = (*enemies1)->y + HEIGHT_NAZGUL;
					}
				}
				if ((*enemies1)->dy < 0)
				{
					(*enemies1)->y = player.y + HEIGHT_NAZGUL;
					(*enemies1)->direction = rand()%4;
					if (player.dy > 0)
					{
						player.y = (*enemies1)->y - HEIGHT_NAZGUL;
					}
				}
			}
		}
	}
}

int main()
{
	Player player;
	vector<Nazgul*> enemies;
	RenderWindow window(sf::VideoMode(900, 600), "hobbit");
	Menu(window);

	view.reset(FloatRect(0, 0, 900, 600));

	Image map_image;
	map_image.loadFromFile("images/mmap.png");
	Texture map;
	map.loadFromImage(map_image);
	Sprite s_map;
	s_map.setTexture(map);

	Image money_image;
	money_image.loadFromFile("images/money.png");
	Texture money;
	money.loadFromImage(money_image);
	Sprite s_money;
	s_money.setTexture(money);

	Image fon;
	fon.loadFromFile("images/fon.png");
	Texture fons;
	fons.loadFromImage(fon);
	Sprite s_fon;
	s_fon.setTexture(fons);

	Font font;
	font.loadFromFile("font4.ttf");
	Text text("", font, 30);
	text.setColor(Color::White);

	Font font1;
	font1.loadFromFile("font4.ttf");
	Text text1("", font, 30);
	text1.setColor(Color::White);

	Music music;
	music.openFromFile("audio/main theme.wav");

	Texture herotexture;
	herotexture.loadFromFile("images/hero1.png");
	player.elf.setTexture(herotexture);
	player.elf.setTextureRect(IntRect(0, 0, WIDTH_PLAYER, HEIGHT_PLAYER));

	Texture nazgultexture;
	nazgultexture.loadFromFile("images/lord1.png");
	Sprite nazgulsprite;
	nazgulsprite.setTexture(nazgultexture);


	int counterCoins = 0;
	float CurrentFrameMoney = 0;
	int timer = 180;
	Clock clock;
	Clock gameTimeClock;
	int gameTime = 0;

	enemies.push_back(new Nazgul(nazgulsprite, 100, 100, 1));
	enemies.push_back(new Nazgul(nazgulsprite, 200, 250, 1));
	enemies.push_back(new Nazgul(nazgulsprite, 56, 360, 1));
	enemies.push_back(new Nazgul(nazgulsprite, 120, 150, 1));
	enemies.push_back(new Nazgul(nazgulsprite, 147, 360, 1));
	enemies.push_back(new Nazgul(nazgulsprite, 85, 74, 1));

	music.play();
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		gameTime = gameTimeClock.getElapsedTime().asSeconds();
		clock.restart();
		time = time * 0.001;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (timer > 0)
		{
			player.currentAnimationFrame = ProcessInput(player, time);
		}
		
		
		GetPlayerCoordinateForView(player.x, player.y);
		UpdatePlayer(time, player, counterCoins, TileMap);
		EntitiesIntersection(player, enemies, timer);

		for (auto i : enemies)
		{
			NazgulUpdate(*i, time, TileMap);
			i++;
		}
		s_fon.setPosition(view.getCenter().x - 450, view.getCenter().y - 300);

		TimeGame(window, text, gameTime, timer);
		CounterCoins(window, text1, counterCoins);

		ViewMap(time, player);
		window.setView(view);
		
		window.clear();
		DrawMap(s_map, CurrentFrameMoney, time, s_money, window);

		DrawPlayer(window, &player);
		for (auto i : enemies)
		{
			DrawNazgul(window, i);
			i++;
		}
		window.draw(s_fon);
		window.draw(text);
		window.draw(text1);
		window.display();
	}
	return 0;
}