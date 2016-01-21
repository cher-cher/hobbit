#include <SFML/Graphics.hpp>
#include <iostream> 
#include "map.h"
#include "player.h"

using namespace sf;

int main()
{
	Player player;
	RenderWindow window(sf::VideoMode(720, 342), "big game");

	Image map_image;//������ ����������� ��� �����
	map_image.loadFromFile("images/map4.png");//��������� ���� ��� �����
	Texture map;//�������� �����
	map.loadFromImage(map_image);//�������� �������� ���������
	Sprite s_map;//������ ������ ��� �����
	s_map.setTexture(map);//�������� �������� ��������

	Texture herotexture;
	herotexture.loadFromFile("images/hero4.png");

	player.elf.setTexture(herotexture);
	player.elf.setTextureRect(IntRect(0, 0, 32, 48));
	player.elf.setPosition(20, 185);

	float CurrentFrame = 0;//������ ������� ����
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


		///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Left))) { //���� ������ ������� ������� ����� ��� ���� ����� �
			CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			player.elf.setTextureRect(IntRect(32 * int(CurrentFrame), 48, 32, 48)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
			player.elf.move(-0.1*time, 0);//���������� ���� �������� ��������� �����
			//tryToMove(herosprite, time);
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right))) {
			CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			player.elf.setTextureRect(IntRect(32 * int(CurrentFrame), 96, 32, 48)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
			player.elf.move(0.1*time, 0);//���������� ���� �������� ��������� ������
			//tryToMove(herosprite, time);

		}


		if ((Keyboard::isKeyPressed(Keyboard::Up))) {
			CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			player.elf.setTextureRect(IntRect(32 * int(CurrentFrame), 144, 32, 48)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
			player.elf.move(0, -0.1*time);//���������� ���� �������� ��������� �����
			//tryToMove(herosprite, time);
		}

		if ((Keyboard::isKeyPressed(Keyboard::Down))) {
			CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			player.elf.setTextureRect(IntRect(32 * int(CurrentFrame), 0, 32, 48)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
			player.elf.move(0, 0.1*time);//���������� ���� �������� ��������� ����
			//tryToMove(herosprite, time);
		}

		window.clear();
		/////////////////////////////������ �����/////////////////////
		for (int i = 0; i < HEIGHT_MAP; i++)
			for (int j = 0; j < WIDTH_MAP; j++)
			{
				if (TileMap[i][j] == 'b')  s_map.setTextureRect(IntRect(0, 0, 18, 18)); 
				if (TileMap[i][j] == 'e')  s_map.setTextureRect(IntRect(0, 0, 18, 18));
				if (TileMap[i][j] == 's') s_map.setTextureRect(IntRect(36, 0, 18, 18));
				if (TileMap[i][j] == 'g')  s_map.setTextureRect(IntRect(36, 0, 18, 18));
				if (TileMap[i][j] == 'h')  s_map.setTextureRect(IntRect(18, 0, 18, 18));

				s_map.setPosition(j * 18, i * 18);//�� ���� ����������� ����������, ��������� � �����. �� ���� ������ ������� �� ��� �������. ���� ������, �� ��� ����� ���������� � ����� �������� 32*32 � �� ������ ���� �������

				window.draw(s_map);//������ ���������� �� �����
			}


		DrawPlayer(window, &player);
		window.display();
	}

	return 0;
}