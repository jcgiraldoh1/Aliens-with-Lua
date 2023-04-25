#include "Enemy.h"

extern b2World* world;
extern std::vector<Sprite*> enemySprites;

EnemyEntity* MakeEnemy(EnemyType etype, MatType mtype, b2Vec2 pixelCoords,
	float angleInDegrees, int maximumHP)
{
	EnemyEntity* enemyEntity = new EnemyEntity();
	enemyEntity->enemyType = etype;
	enemyEntity->materialType = mtype;

	b2BodyDef bodyDef;

	bodyDef.type = b2_dynamicBody; //make it a dynamic body i.e. one moved by physics
	bodyDef.position = Pixels2Physics(pixelCoords); //set its position in the world
	bodyDef.angle = deg2rad(angleInDegrees);

	bodyDef.angularDamping = 1.8f;

	bodyDef.userData.pointer = reinterpret_cast<uintptr_t> (enemyEntity);

	enemyEntity->body = world->CreateBody(&bodyDef); //create the body and add it to the world

	b2FixtureDef fixtureDef;

	// Define a shape for our body.
	b2PolygonShape polygon;
	b2CircleShape circle;

	switch (etype)
	{	
	case EnemyType::GREEN:
	{
		polygon.SetAsBox(35 / PTM_RATIO, 35 / PTM_RATIO, b2Vec2(0, 0), 0);
		fixtureDef.shape = &polygon;
	}
	break;
	case EnemyType::BLUE:
	{
		polygon.SetAsBox(35 / PTM_RATIO, 35 / PTM_RATIO, b2Vec2(0, 0), 0);
		fixtureDef.shape = &polygon;
	}
	break;

	case EnemyType::YELLOW:
	{
		polygon.SetAsBox(35 / PTM_RATIO, 35 / PTM_RATIO, b2Vec2(0, 0), 0);
		fixtureDef.shape = &polygon;
		
	}
	break;
	default:
		assert(false);

	}//end switch(btype)

	switch (mtype)
	{
	case MatType::WOOD:
		fixtureDef.density = 0.5f;
		fixtureDef.restitution = 0.05;
		fixtureDef.friction = 0.5;
		break;
	case MatType::METAL:
		fixtureDef.density = 0.1f;
		fixtureDef.restitution = 0.05;
		fixtureDef.friction = 1;
		break;
	case MatType::ICE:
		fixtureDef.density = 1.1f;
		fixtureDef.restitution = 0.05;
		fixtureDef.friction = 0.1;
		break;
	default:
		assert(false);
	}//end switch(mtype)

	enemyEntity->body->CreateFixture(&fixtureDef);

	int numEnemyTypesToSkip = (int)etype;
	int numMaterials = (int)MatType::END;
	int numSpritesToSkip = numEnemyTypesToSkip * numMaterials * 3; //3 sprites per material/shape

	//add sprites
	enemyEntity->sprite = enemySprites[numSpritesToSkip + (int)mtype * 3];
	enemyEntity->spriteList.push_back(enemySprites[numSpritesToSkip + (int)mtype * 3 + 1]);
	enemyEntity->spriteList.push_back(enemySprites[numSpritesToSkip + (int)mtype * 3 + 2]);

	enemyEntity->maxHP = enemyEntity->hp = maximumHP;

	return enemyEntity;
}