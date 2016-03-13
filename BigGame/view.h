#include <SFML/Graphics.hpp>
#include "const.h"

using namespace sf;

View view;

void GetPlayerCoordinateForView(float x, float y) { //функция для считывания координат игрока
	float tempX = x; float tempY = y;//считываем коорд игрока и проверяем их, чтобы убрать края

	if (x < 500) tempX = 500;
	if (x > 1740) tempX = 1740;
	if (y < 300) tempY = 300;
	if (y > 820) tempY = 820;

	view.setCenter(tempX, tempY); //следим за игроком, передавая его координаты. 
}

void ViewMap(float time, Player & player) { //функция для перемещения камеры по карте. принимает время sfml

	float speed = player.speed;

	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		view.move(-speed * time, 0);//скроллим карту влево 
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		view.move(speed * time, 0);//скроллим карту вправо 
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		view.move(0, -speed * time);
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		view.move(0, speed * time);
	}
}