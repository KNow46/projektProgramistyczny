#include "YellowBlock.h"

void YellowBlock::ballCollisionEffect(int damage, Owner ballBouncer)
{
	hp = hp - damage;
	if (hp <= 0)
	{
		if (ballBouncer == player)
		{
			*playerPoints += 50;
			points->changeText(std::to_string(*playerPoints));
		}
		isDestroyed = true;

	}
}