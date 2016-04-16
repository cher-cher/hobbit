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
	Texture menuTexture1, menuTexture2, menuTexture3, menuBackground, gameDescriptionTexture, gameRuleTexture, nextTexture;
	menuTexture1.loadFromFile("images/start.png");
	menuTexture2.loadFromFile("images/exit.png");
	menuTexture3.loadFromFile("images/hobbit.png");
	menuBackground.loadFromFile("images/BackGround11.png");
	gameRuleTexture.loadFromFile("images/BackGround2.png");
	gameDescriptionTexture.loadFromFile("images/dialog.png");
	nextTexture.loadFromFile("images/next.png");
	Sprite startSpr(menuTexture1), exitSpr(menuTexture2), hobbit(menuTexture3), menuBg(menuBackground);
	Sprite descriptionSprite(gameDescriptionTexture), nextSpr(nextTexture), ruleSprite(gameRuleTexture);
	bool isMenu = true;
	bool gameDicription = false;
	bool gameRule = false;
	int menuNum = 0;
	hobbit.setPosition(325, 75);
	startSpr.setPosition(325, 400);
	exitSpr.setPosition(325, 450);
	menuBg.setPosition(0, 0);
	descriptionSprite.setPosition(0, 0);
	ruleSprite.setPosition(0, 0);
	nextSpr.setPosition(650, 500);
	musicMenu.play();
	while (isMenu || gameDicription|| gameRule)
	{
		if (isMenu)
		{
			startSpr.setColor(Color::Black);
			exitSpr.setColor(Color::Black);
			hobbit.setColor(Color::Black);
			menuNum = 0;

			if (IntRect(325, 400, 250, 75).contains(Mouse::getPosition(window))) { startSpr.setColor(Color::White); menuNum = 1; }
			if (IntRect(325, 450, 250, 75).contains(Mouse::getPosition(window))) { exitSpr.setColor(Color::White); menuNum = 2; }

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
					gameRule = true;
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
		else if (gameRule)
		{
			nextSpr.setPosition(325, 525);
			nextSpr.setColor(Color::Black);
			menuNum = 0;

			if (IntRect(325, 525, 250, 75).contains(Mouse::getPosition(window))) { nextSpr.setColor(Color::White); menuNum = 1; }

			if (Mouse::isButtonPressed(Mouse::Left))
			{
				if (menuNum == 1)
				{
					gameRule = false;
				}
			}

			window.clear();

			window.draw(ruleSprite);
			window.draw(nextSpr);

			window.display();
		}
	}
}

void DrawMap(Sprite &s_ark, Sprite &s_map, float &CurrentFrameMoney, float & CurrentFrameRing, float & CurrentFrameArk, float time, Sprite &s_money, Sprite &s_ring, RenderWindow &window, Game & game, vector<string> const& TileMap)
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
			if (TileMap[i][j] == 'k')
			{
				s_map.setTextureRect(IntRect(4 * SIZE_BLOCK, 0, SIZE_BLOCK, SIZE_BLOCK));
				s_map.setPosition(j * SIZE_BLOCK, i * SIZE_BLOCK);
				window.draw(s_map);
			}
			if (TileMap[i][j] == 'o')
			{
				s_map.setTextureRect(IntRect(5 * SIZE_BLOCK, 0, SIZE_BLOCK, SIZE_BLOCK));
				s_map.setPosition(j * SIZE_BLOCK, i * SIZE_BLOCK);
				window.draw(s_map);
			}
			if (TileMap[i][j] == 'm')
			{
				s_money.setTextureRect(IntRect(SIZE_BLOCK * int(CurrentFrameMoney), 0, SIZE_BLOCK, SIZE_BLOCK));
				s_money.setPosition(j * SIZE_BLOCK, i * SIZE_BLOCK);
				window.draw(s_money);
			}
			if (TileMap[i][j] == 'a')
			{
				s_ark.setTextureRect(IntRect(SIZE_BLOCK * int(CurrentFrameArk), 0, SIZE_BLOCK, SIZE_BLOCK));
				s_ark.setPosition(j * SIZE_BLOCK, i * SIZE_BLOCK);
				window.draw(s_ark);
			}
			if (TileMap[i][j] == 'r')
				{
				s_ring.setTextureRect(IntRect(SIZE_BLOCK * int(CurrentFrameRing), 0, SIZE_BLOCK, SIZE_BLOCK));
				s_ring.setPosition(j * SIZE_BLOCK, i * SIZE_BLOCK);
				window.draw(s_ring);
				}
			if (TileMap[i][j] == 'e')
			{
				s_map.setTextureRect(IntRect(SIZE_BLOCK * 2, 0, SIZE_BLOCK * 2, SIZE_BLOCK));
				s_map.setPosition(j * SIZE_BLOCK, i * SIZE_BLOCK);
				window.draw(s_map);
			}
		}
	}
	CurrentFrameArk += time * 0.015;
	if (CurrentFrameArk > 3) CurrentFrameArk -= 3;
	CurrentFrameMoney += time * 0.015;
	if (CurrentFrameMoney > 7) CurrentFrameMoney -= 7;
	CurrentFrameRing += time * 0.01;
	if (CurrentFrameRing > 7) CurrentFrameRing -= 7;
}

void TimeGame(RenderWindow &window,Text &text, int gameTime, int &timer)
{
	std::ostringstream gameTimeString;   
	gameTimeString << timer - gameTime;
	text.setString("Время: " + gameTimeString.str());
	text.setPosition(view.getCenter().x - 450, view.getCenter().y - 300);
}

void CounterCoins(RenderWindow &window, Text &text1, int counterCoins)
{
	std::ostringstream gameCounterCoinsString;
	gameCounterCoinsString << counterCoins;
	text1.setString("Монеты: " + gameCounterCoinsString.str());
	text1.setPosition(view.getCenter().x + 280, view.getCenter().y - 300);
}

void EntitiesIntersection(Game & game, Player & player, vector<Nazgul> &enemies, int & timer, float time)
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
					if (enemies1->direction = 0)
					{
						enemies1->direction = 1;
						enemies2->direction = 0;
					}
					else if (enemies1->direction = 1)
					{
						enemies1->direction = 0;
						enemies2->direction = 1;
					}
					else if (enemies1->direction = 2)
					{
						enemies1->direction = 3;
						enemies2->direction = 2;
					}
					else if (enemies1->direction = 3)
					{
						enemies1->direction = 2;
						enemies2->direction = 3;
					}
				}
			}
		}
		if (game.invisibleMood)
		{
			if ((enemies2->rect.intersects((player.rect))))
			{
				player.life = false;
				/*Vector2f pos = player.elf.getPosition();
				if (enemies2->dx > 0)
				{
					if (enemies2->direction == 0)
						enemies2->direction = 1;
					else if (enemies2->direction == 1)
						enemies2->direction = 0;
					else if (enemies2->direction == 2)
						enemies2->direction = 3;
					else if (enemies2->direction == 3)
						enemies2->direction = 2;
					if (player.dx < 0)
					{
						player.x -= player.dx*time;
					}
				}
				if (enemies2->dx < 0)
				{
					if (enemies2->direction == 0)
						enemies2->direction = 1;
					else if (enemies2->direction == 1)
						enemies2->direction = 0;
					else if (enemies2->direction == 2)
						enemies2->direction = 3;
					else if (enemies2->direction == 3)
						enemies2->direction = 2;
					if (player.dx > 0)
					{
						player.x -= player.dx*time;
					}
				}
				if (enemies2->dy > 0)
				{
					if (enemies2->direction == 0)
						enemies2->direction = 1;
					else if (enemies2->direction == 1)
						enemies2->direction = 0;
					else if (enemies2->direction == 2)
						enemies2->direction = 3;
					else if (enemies2->direction == 3)
						enemies2->direction = 2;
					if (player.dy < 0)
					{
						player.y -= player.dy*time;
					}
				}
				if (enemies2->dy < 0)
				{
					if (enemies2->direction == 0)
						enemies2->direction = 1;
					else if (enemies2->direction == 1)
						enemies2->direction = 0;
					else if (enemies2->direction == 2)
						enemies2->direction = 3;
					else if (enemies2->direction == 3)
						enemies2->direction = 2;
					if (player.dy > 0)
					{
						player.y -= player.dy*time;
					}
				}*/
				SyncPlayerSprite(player);
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

	Image ark_image;
	ark_image.loadFromFile("images/arkenstone.png");
	Texture ark;
	ark.loadFromImage(ark_image);
	Sprite s_ark;
	s_ark.setTexture(ark);

	Image ring_image;
	ring_image.loadFromFile("images/ring.png");
	Texture ring;
	ring.loadFromImage(ring_image);
	Sprite s_ring;
	s_ring.setTexture(ring);

	Image find_ring_image;
	find_ring_image.loadFromFile("images/ring_ring.png");
	Texture fring;
	fring.loadFromImage(find_ring_image);
	Sprite s_fring;
	s_fring.setTexture(fring);

	Sprite ringAnimSpr = s_fring;
	ringAnimSpr.setOrigin(25, 25);

	Image hand_ring_image;
	hand_ring_image.loadFromFile("images/hand_ring.png");
	Texture hand_ring;
	hand_ring.loadFromImage(hand_ring_image);
	Sprite s_hand_ring;
	s_hand_ring.setTexture(hand_ring);

	Image fon;
	fon.loadFromFile("images/fons.png");
	Texture fons;
	fons.loadFromImage(fon);
	Sprite s_fon;
	s_fon.setTexture(fons);

	Image gendalf_image;
	gendalf_image.loadFromFile("images/gendalf1.png");
	Texture gendalf;
	gendalf.loadFromImage(gendalf_image);
	Sprite s_gendalf;
	s_gendalf.setTexture(gendalf);

	Font font;
	font.loadFromFile("anicb___.ttf");
	Text text("", font, 20);
	text.setColor(Color::White);

	Font font1;
	font1.loadFromFile("anicb___.ttf");
	Text text1("", font, 20);
	text1.setColor(Color::White);

	Music music;
	music.openFromFile("audio/main theme.wav");

	Music voiceGendalf;
	voiceGendalf.openFromFile("audio/not_pass.ogg");

	Texture herotexture;
	herotexture.loadFromFile("images/hero1.png");
	player.elf.setTexture(herotexture);
	player.elf.setTextureRect(IntRect(0, 0, WIDTH_PLAYER, HEIGHT_PLAYER));

	Texture nazgultexture;
	nazgultexture.loadFromFile("images/lord1.png");
	Sprite nazgulsprite;
	nazgulsprite.setTexture(nazgultexture);

	game.restart = false;
	Clock clock;
	Clock gameTimeClock;
	int gameTime = 0;

	float CurrentFrameMoney = 0;
	float CurrentFrameRing = 0;
	float CurrentFrameHand = 0;
	float CurrentFrameFon = 0;
	float CurrentFrameArk = 0;
	float CurrentFrameGendalf = 0;

	SetLevel(game, TileMap);

	enemies.push_back(Nazgul(nazgulsprite, 64, 64, 1));
	enemies.push_back(Nazgul(nazgulsprite, 450, 250, 1));
	enemies.push_back(Nazgul(nazgulsprite, 356, 360, 1));
	enemies.push_back(Nazgul(nazgulsprite, 140, 150, 1));
	enemies.push_back(Nazgul(nazgulsprite, 760, 360, 1));
	enemies.push_back(Nazgul(nazgulsprite, 150, 74, 1));

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
		if (game.timer > 0 && player.life)
		{
			player.currentAnimationFrame = ProcessInput(player, time, game);
		}
		if (game.restart)
		{
			return true;
		}

		GetPlayerCoordinateForView(player.x, player.y);
		UpdatePlayer(time, player, game.counterCoins, game, TileMap);
		EntitiesIntersection(game, player, enemies, game.timer, time);

		for (auto it = enemies.begin(); it != enemies.end();)
		{
			if (it->life)
			{
				NazgulUpdate(*it, time, TileMap, game, player);
				++it;
			}
			else
			{
				it = enemies.erase(it);
			}
		}
		s_fon.setPosition(view.getCenter().x - 450, view.getCenter().y - 300);

		TimeGame(window, text, gameTime, game.timer);
		CounterCoins(window, text1, game.counterCoins);

		ViewMap(time, player);
		window.setView(view);

		window.clear();
		DrawMap(s_ark,s_map, CurrentFrameMoney, CurrentFrameArk, CurrentFrameRing, time, s_money, s_ring, window, game, TileMap);
		DrawPlayer(window, &player);

		for (auto it : enemies)
		{
			DrawNazgul(window, it);
		}

		if (!game.invisibleMood)
		{
			s_fon.setTextureRect(IntRect(0, 0, 900, 600));
			s_fon.setPosition(view.getCenter().x - 450, view.getCenter().y - 300);
			window.draw(s_fon);
		}
		else
		{
			if (CurrentFrameFon < 2)
			{
				CurrentFrameFon += time * 0.01;
				s_fon.setTextureRect(IntRect(0, 600 * int(CurrentFrameFon), 900, 600));
				s_fon.setPosition(view.getCenter().x - 450, view.getCenter().y - 300);
				window.draw(s_fon);
			}
			else
			{
				s_fon.setTextureRect(IntRect(0, 600 * 2, 900, 600));
				s_fon.setPosition(view.getCenter().x - 450, view.getCenter().y - 300);
				window.draw(s_fon);
			}
			if (CurrentFrameHand < 4) 
			{
				CurrentFrameHand += time * 0.01;
				s_hand_ring.setTextureRect(IntRect(60 * int(CurrentFrameHand), 0, 60, 60));
				s_hand_ring.setPosition(view.getCenter().x - 30, view.getCenter().y - 300);
				window.draw(s_hand_ring);
			}
			else
			{
				s_hand_ring.setTextureRect(IntRect(60 * 3, 0, 60, 60));
				s_hand_ring.setPosition(view.getCenter().x - 30, view.getCenter().y - 300);
				window.draw(s_hand_ring);
			}
		}
		if (game.ring && !game.invisibleMood)
		{
			s_fring.setPosition(view.getCenter().x - 25, view.getCenter().y - 300);
			window.draw(s_fring);
			CurrentFrameHand = 0;
			CurrentFrameFon = 0;
		}


		if (game.findRing)
		{
			Vector2f pos = ringAnimSpr.getPosition();
			float newX = pos.x;
			float newY = pos.y;
			if (((int)pos.x == view.getCenter().x) && ((int)pos.y == view.getCenter().y - 275))
			{
				game.findRing = false;
				game.ring = true;
			}
			if (pos.x < view.getCenter().x)
			{
				newX += time * 0.4;
			}
			else if (pos.x < view.getCenter().x)
			{
				newX -= time * 0.4;
			}
			if (pos.y > view.getCenter().y - 275)
			{
				newY -= time * 0.4;
			}
			else if (pos.y < view.getCenter().y - 275)
			{
				newY += time * 0.4;
			}	
			
			ringAnimSpr.setPosition(newX, newY);
			window.draw(ringAnimSpr);
		}
		else
		{
			ringAnimSpr.setPosition(player.x + 19, player.y);
		}
		//CurrentFrameGendalf = 0;
		window.draw(text);
		window.draw(text1);
		if (!player.life)
		{
			cout << player.life << endl;
			if (CurrentFrameGendalf < 13)
			{
				cout << CurrentFrameGendalf << endl;
				CurrentFrameGendalf += time * 0.015;
				s_gendalf.setTextureRect(IntRect(0, 600 * int(CurrentFrameGendalf), 900, 600));
				s_gendalf.setPosition(view.getCenter().x - 450, view.getCenter().y - 300);
				window.draw(s_gendalf);
				voiceGendalf.play();
			}
		}
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