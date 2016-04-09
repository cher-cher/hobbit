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
#include "game.h"
#include <string>
#include <vector>

using namespace sf;
using namespace std;


void Menu(RenderWindow & window) 
{
	Music musicMenu;
	musicMenu.openFromFile("audio/menu.wav");
	Texture menuTexture1, menuTexture2, menuTexture3, menuBackground, menuSelectPlayer, gameDescriptionTexture, nextTexture;
	menuTexture1.loadFromFile("images/start.png");
	menuTexture2.loadFromFile("images/exit.png");
	menuTexture3.loadFromFile("images/hobbit.png");
	menuBackground.loadFromFile("images/BackGround11.png");
	menuSelectPlayer.loadFromFile("images/BackGround111.png");
	gameDescriptionTexture.loadFromFile("images/dialog.png");
	nextTexture.loadFromFile("images/next.png");
	Sprite startSpr(menuTexture1), exitSpr(menuTexture2), hobbit(menuTexture3), menuBg(menuBackground);
	Sprite descriptionSprite(gameDescriptionTexture), nextSpr(nextTexture) ;
	bool isMenu = true;
	bool gameDicription = false;
	int menuNum = 0;
	hobbit.setPosition(325, 75);
	startSpr.setPosition(325, 375);
	exitSpr.setPosition(325, 425);
	menuBg.setPosition(0, 0);
	descriptionSprite.setPosition(0, 0);
	nextSpr.setPosition(650, 500);
	musicMenu.play();
	while (isMenu || gameDicription)
	{
		if (isMenu)
		{
			startSpr.setColor(Color::Black);
			exitSpr.setColor(Color::Black);
			hobbit.setColor(Color::Black);
			menuNum = 0;

			if (IntRect(325, 375, 250, 75).contains(Mouse::getPosition(window))) { startSpr.setColor(Color::White); menuNum = 1; }
			if (IntRect(325, 425, 250, 75).contains(Mouse::getPosition(window))) { exitSpr.setColor(Color::White); menuNum = 2; }

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menuNum == 1)
				{
					isMenu = false;
					gameDicription = true;
				}
				if (menuNum == 2)
				{
					window.close();
					isMenu = false;
				}

			}
			window.clear();

			window.draw(menuBg);
			window.draw(startSpr);
			window.draw(exitSpr);
			window.draw(hobbit);

			window.display();
		}
		else if (gameDicription)
		{
			exitSpr.setPosition(0, 500);
			exitSpr.setColor(Color::Black);
			nextSpr.setColor(Color::Black);
			menuNum = 0;

			if (IntRect(650, 500, 250, 75).contains(Mouse::getPosition(window))) { nextSpr.setColor(Color::White); menuNum = 1; }
			if (IntRect(0, 500, 250, 75).contains(Mouse::getPosition(window))) { exitSpr.setColor(Color::White); menuNum = 2; }

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menuNum == 1)
				{
					gameDicription = false;
				}
				if (menuNum == 2)
				{
					window.close();
					gameDicription = false;
				}

			}

			window.clear();

			window.draw(descriptionSprite);
			window.draw(nextSpr);
			window.draw(exitSpr);

			window.display();
		}
	}
}

void DrawMap(Sprite &s_map, float &CurrentFrameMoney, float time, Sprite &s_money, RenderWindow &window, Game & game, vector<string> const& TileMap)
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
			if (TileMap[i][j] == 'e')
			{
				s_map.setTextureRect(IntRect(SIZE_BLOCK * 2, 0, SIZE_BLOCK * 2, SIZE_BLOCK));
				s_map.setPosition(j * SIZE_BLOCK, i * SIZE_BLOCK);
				window.draw(s_map);
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

void EntitiesIntersection(Player & player, vector<Nazgul> &enemies, int & timer)
{
	vector<Nazgul> ::iterator enemies1 = enemies.begin();
	vector<Nazgul> ::iterator enemies2;

	for (enemies2 = enemies.begin(); enemies2 != enemies.end(); enemies2++) {
		for (enemies1 = enemies.begin(); enemies1 != enemies.end(); enemies1++)
		{
			if ((enemies1->rect.intersects(enemies2->rect)))
			{
				if ((enemies1->rect) != (enemies2->rect))
				{
					enemies1->direction = rand() % 4;
					enemies2->direction = rand() % 4;
				}
			}
		}
		if ((enemies2->rect.intersects((player.rect))))
		{
			if (enemies2->dx > 0)
			{
				enemies2->x = player.x - WIDTH_NAZGUL;
				enemies2->direction = rand() % 4;
				if (player.dx < 0)
				{
					player.x = enemies2->x + WIDTH_NAZGUL;
				}
			}
			if (enemies2->dx < 0)
			{
				enemies2->x = player.x + WIDTH_NAZGUL;
				enemies2->direction = rand() % 4;
				if (player.dx > 0)
				{
					player.x = enemies2->x - WIDTH_NAZGUL;
				}
			}
			if (enemies2->dy > 0)
			{
				enemies2->y = player.y - HEIGHT_NAZGUL;
				enemies2->direction = rand() % 4;
				if (player.dy < 0)
				{
					player.y = enemies2->y + HEIGHT_NAZGUL;
				}
			}
			if (enemies2->dy < 0)
			{
				enemies2->y = player.y + HEIGHT_NAZGUL;
				enemies2->direction = rand() % 4;
				if (player.dy > 0)
				{
					player.y = enemies2->y - HEIGHT_NAZGUL;
				}
			}
		}
	}
}

void SetLevel(Game & game, vector<string> & TileMap)
{
	switch (game.level)
	{
	case 1:
		for (auto it : TileMap1)
		{
			TileMap.push_back(it);
		}
		break;
	case 2:
		for (auto it : TileMap2)
		{
			TileMap.push_back(it);
		}
		break;
	default:
		for (auto it : TileMap1)
		{
			TileMap.push_back(it);
		}
		break;
	}
}

bool StartGame(Game & game, RenderWindow & window)
{
	vector<string> TileMap;
	Player player;
	vector<Nazgul> enemies;
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

	float CurrentFrameMoney = 0;
	game.restart = false;
	Clock clock;
	Clock gameTimeClock;
	int gameTime = 0;

	SetLevel(game, TileMap);

	enemies.push_back(Nazgul(nazgulsprite, 100, 100, 1));
	enemies.push_back(Nazgul(nazgulsprite, 200, 250, 1));
	enemies.push_back(Nazgul(nazgulsprite, 56, 360, 1));
	enemies.push_back(Nazgul(nazgulsprite, 120, 150, 1));
	enemies.push_back(Nazgul(nazgulsprite, 147, 360, 1));
	enemies.push_back(Nazgul(nazgulsprite, 85, 74, 1));

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
			{
				window.close();
				return false;
			}
		}
		if (game.timer > 0)
		{
			player.currentAnimationFrame = ProcessInput(player, time);
		}
		if (game.restart)
		{
			return true;
		}

		GetPlayerCoordinateForView(player.x, player.y);
		UpdatePlayer(time, player, game.counterCoins, game, TileMap);
		EntitiesIntersection(player, enemies, game.timer);

		for (auto it = enemies.begin(); it != enemies.end();)
		{
			if (it->life)
			{
				NazgulUpdate(*it, time, TileMap);
				++it;
			}
			else
			{
				enemies.erase(it);
			}
		}
		s_fon.setPosition(view.getCenter().x - 450, view.getCenter().y - 300);

		TimeGame(window, text, gameTime, game.timer);
		CounterCoins(window, text1, game.counterCoins);

		ViewMap(time, player);
		window.setView(view);

		window.clear();
		DrawMap(s_map, CurrentFrameMoney, time, s_money, window, game, TileMap);

		DrawPlayer(window, &player);
		for (auto it : enemies)
		{
			DrawNazgul(window, it);
		}
		window.draw(s_fon);
		window.draw(text);
		window.draw(text1);
		window.display();
	}
}

void GameRunning(Game & game, RenderWindow & window)
{
	if (StartGame(game, window))
	{
		GameRunning(game, window);
	}
}

int main()
{
	Game game;
	RenderWindow window(sf::VideoMode(900, 600), "hobbit");
	Menu(window);
	GameRunning(game, window);
	return 0;
}