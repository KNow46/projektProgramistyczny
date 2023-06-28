#pragma once

#include "GameObject.h"
#include <vector>
#include "BlockCrack.h"
#include "Text.h"
#include <string>
#include "Global.h""
#include "Block.h"

class YellowBlock : public Block
{
public:
	YellowBlock(int x, int y, int height, int width, std::string texturePath, Text* points)
		:Block(x, y, height, width, texturePath, points) {
		hp = 3;
	};

	virtual void ballCollisionEffect(int damage, Owner ballBouncer);


}; 
