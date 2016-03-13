#include <SFML/Graphics.hpp>
#include "const.h"

using namespace sf;

View view;

void GetPlayerCoordinateForView(float x, float y) { //������� ��� ���������� ��������� ������
	float tempX = x; float tempY = y;//��������� ����� ������ � ��������� ��, ����� ������ ����

	if (x < 500) tempX = 500;
	if (x > 1740) tempX = 1740;
	if (y < 300) tempY = 300;
	if (y > 820) tempY = 820;

	view.setCenter(tempX, tempY); //������ �� �������, ��������� ��� ����������. 
}

void ViewMap(float time, Player & player) { //������� ��� ����������� ������ �� �����. ��������� ����� sfml

	float speed = player.speed;

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		view.move(-speed * time, 0);//�������� ����� ����� 
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		view.move(speed * time, 0);//�������� ����� ������ 
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		view.move(0, -speed * time);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		view.move(0, speed * time);
	}
}