#include <SFML/Graphics.hpp>
#include <iostream> 

using namespace sf;

struct Player 
{
	Sprite elf;
	float x;
	float y;

};

float getPlayerCoordinateX(Player & player);
float getPlayerCoordinateY(Player & player);
void DrawPlayer(RenderWindow &window, Player * player);