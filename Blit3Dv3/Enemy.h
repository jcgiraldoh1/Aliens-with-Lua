#pragma once
#include "Entity.h"

enum class EnemyType { GREEN = 0, BLUE, YELLOW, END };

enum class MatType { WOOD = 0, METAL, ICE, END };

class EnemyEntity : public Entity
{
public:
	EnemyType enemyType;
	MatType materialType;
	int hp;
	int maxHP;
	std::vector<Sprite*> spriteList;


	EnemyEntity()
	{
		typeID = ENTITYALIEN;
		enemyType = EnemyType::GREEN;
		materialType = MatType::WOOD;
		maxHP = hp = 100;

	}

	//Damage() returns true if we should kill this object
	bool Damage(int damage)
	{
		hp -= damage;
		if (hp < 1) return true;
		if (hp < maxHP / 3) sprite = spriteList[1];
		else if (hp < maxHP * 0.66) sprite = spriteList[0];

		return false;
	}
};

EnemyEntity* MakeEnemy(EnemyType etype, MatType mtype, b2Vec2 pixelCoords,
	float angleInDegrees, int maximumHP);