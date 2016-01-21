#include <SFML/Graphics.hpp>
#include <iostream> 
#include "map.h"
#include "player.h"

using namespace sf;

int main()
{
	Player player;
	RenderWindow window(sf::VideoMode(720, 342), "big game");

	Image map_image;//объект изображения для карты
	map_image.loadFromFile("images/map4.png");//загружаем файл для карты
	Texture map;//текстура карты
	map.loadFromImage(map_image);//заряжаем текстуру картинкой
	Sprite s_map;//создаём спрайт для карты
	s_map.setTexture(map);//заливаем текстуру спрайтом

	Texture herotexture;
	herotexture.loadFromFile("images/hero4.png");

	player.elf.setTexture(herotexture);
	player.elf.setTextureRect(IntRect(0, 0, 32, 48));
	player.elf.setPosition(20, 185);

	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;

	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}


		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Left))) { //если нажата клавиша стрелка влево или англ буква А
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			player.elf.setTextureRect(IntRect(32 * int(CurrentFrame), 48, 32, 48)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			player.elf.move(-0.1*time, 0);//происходит само движение персонажа влево
			//tryToMove(herosprite, time);
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right))) {
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			player.elf.setTextureRect(IntRect(32 * int(CurrentFrame), 96, 32, 48)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			player.elf.move(0.1*time, 0);//происходит само движение персонажа вправо
			//tryToMove(herosprite, time);

		}


		if ((Keyboard::isKeyPressed(Keyboard::Up))) {
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			player.elf.setTextureRect(IntRect(32 * int(CurrentFrame), 144, 32, 48)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			player.elf.move(0, -0.1*time);//происходит само движение персонажа вверх
			//tryToMove(herosprite, time);
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down))) {
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			player.elf.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 48)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			player.elf.move(0, 0.1*time);//происходит само движение персонажа вниз
			//tryToMove(herosprite, time);
		}

		window.clear();
		/////////////////////////////Рисуем карту/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == 'b')  s_map.setTextureRect(IntRect(0, 0, 18, 18)); 
				if (TileMap[i][j] == 'e')  s_map.setTextureRect(IntRect(0, 0, 18, 18));
				if (TileMap[i][j] == 's') s_map.setTextureRect(IntRect(36, 0, 18, 18));
				if (TileMap[i][j] == 'g')  s_map.setTextureRect(IntRect(36, 0, 18, 18));
				if (TileMap[i][j] == 'h')  s_map.setTextureRect(IntRect(18, 0, 18, 18));

				s_map.setPosition(j * 18, i * 18);//по сути раскидывает квадратики, превращая в карту. то есть задает каждому из них позицию. если убрать, то вся карта нарисуется в одном квадрате 32*32 и мы увидим один квадрат

				window.draw(s_map);//рисуем квадратики на экран
			}


		DrawPlayer(window, &player);
		window.display();
	}

	return 0;
}