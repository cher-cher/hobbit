#include <SFML/Graphics.hpp>
#include <iostream> 
#include "player.h"

float GetPlayerCoordinateX(Player & player)
{
	return player.x;
}

float GetPlayerCoordinateY(Player & player)
{
	return player.y;
}

void DrawPlayer(RenderWindow & window, Player * player)
{
	window.draw(player->elf);
}