#include "RedBlock.h"

void RedBlock::ballCollisionEffect(int damage, Owner ballBouncer)
{
	hp = hp - damage;
	if (hp <= 0)
	{
		if (ballBouncer == player)
		{
			*playerPoints += 70;
			points->changeText(std::to_string(*playerPoints));
		}
		isDestroyed = true;

	}
}