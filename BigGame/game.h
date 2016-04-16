#pragma once
#include <string>
#include "const.h"
#include <vector>

using namespace std;

struct Game
{
	unsigned level = 1;
	bool restart = false;
	int counterCoins = 0;
	int timer = 180;
	bool ring = false;
	bool findRing = false;
	bool findArk = false;
	bool invisibleMood = false;
};