#include "Enemy.h"

Enemy::Enemy(Point pos, char symbol)
    : Entity(pos, symbol)
{
}

void Enemy::move(char direction, Board& board)
{
    moveInDirection(direction, board);
}