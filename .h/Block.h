#pragma once
#include "Texture.h"
#include "GameObject.h"
#include <vector>
#include "BlockCrack.h"
#include "Text.h"
#include <string>
#include "Global.h"
class Block: public GameObject
{
public:
	Block(int x, int y, int height, int width, std::string texturePath, Text* points)
		:GameObject(x, y, height, width, texturePath), hp(2), crackTexturePath("res/textures/crack.png"), points(points){};

	virtual void ballCollisionEffect(int damage, Owner ballBouncer);
	void ballCollisionEffect() {};
	void addCrack(int x, int y);
	std::vector<BlockCrack*> getCracks();
	BlockCrack *getCrackAtIndex(int index);
	static void SetPlayerPoints(int* points)
	{
		playerPoints = points;
	}
protected:
	int hp;
	std::string crackTexturePath;
	std::vector<BlockCrack*> cracks;
	static int* playerPoints;
	Text* points;

};