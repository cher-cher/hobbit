#include <SFML/Graphics.hpp>
#include <iostream> 
#include "player.h"
#include "const.h"
//#include "map.h"

void DrawPlayer(RenderWindow & window, Player * player)
{
	window.draw(player->elf);
}

Position SyncPlayerPostion(Player & player)
{
	Vector2f pos = player.elf.getPosition();
	player.x = pos.x;
	player.y = pos.y;
	return Position(player.x, player.y);
}

