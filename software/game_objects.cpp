
/********************************

          Pixel Dungeon
           by Djidane

     Game objects-specific functions

********************************/

/**
 *	@author Djidane
 * 	@file game_objects.cpp
 *  @brief Game objects-specific functions
 */

#include "game_objects.h"

struct objectEmpty 	  objectEmptyList[GAME_OBJECT_EMPTY_N]       = { GAME_OBJECT_INIT_EMPTY0    };
struct objectWall 	  objectWallList[GAME_OBJECT_WALL_N]         = { GAME_OBJECT_INIT_WALL0     };
struct objectSwitch   objectSwitchList[GAME_OBJECT_SWITCH_N]     = { GAME_OBJECT_INIT_SWITCH0   };
struct objectDoor 	  objectDoorList[GAME_OBJECT_DOOR_N]         = { GAME_OBJECT_INIT_DOOR0     };
struct objectTeleport objectTeleportList[GAME_OBJECT_TELEPORT_N] = { GAME_OBJECT_INIT_TELEPORT0 };
struct objectGoldp 	  objectGoldpList[GAME_OBJECT_GOLDP_N]       = { GAME_OBJECT_INIT_GOLDP0    };
struct objectHppot 	  objectHppotList[GAME_OBJECT_HPPOT_N]       = { GAME_OBJECT_INIT_HPPOT0    };
struct objectMppot    objectMppotList[GAME_OBJECT_MPPOT_N] 	     = { GAME_OBJECT_INIT_MPPOT0    };
struct objectMonster  objectMonsterList[GAME_OBJECT_MONSTER_N]   = { GAME_OBJECT_INIT_MONSTER0  };
struct objectHero 	  objectHeroList[GAME_OBJECT_HERO_N] 	     = { GAME_OBJECT_INIT_THEHERO   };

int getGameObjectTypeColor(int type)
{
	     if (type == GAME_OBJECT_EMPTY) 	return GAME_OBJECT_EMPTY_COLOR;
	else if (type == GAME_OBJECT_WALL) 		return GAME_OBJECT_WALL_COLOR;
	else if (type == GAME_OBJECT_SWITCH) 	return GAME_OBJECT_SWITCH_COLOR;
	else if (type == GAME_OBJECT_DOOR) 		return GAME_OBJECT_DOOR_COLOR;
	else if (type == GAME_OBJECT_GOLDP) 	return GAME_OBJECT_GOLDP_COLOR;
	else if (type == GAME_OBJECT_MONSTER) 	return GAME_OBJECT_MONSTER_COLOR;
	else if (type == GAME_OBJECT_HPPOT) 	return GAME_OBJECT_HPPOT_COLOR;
	else if (type == GAME_OBJECT_MPPOT) 	return GAME_OBJECT_MPPOT_COLOR;
	else if (type == GAME_OBJECT_HERO) 		return GAME_OBJECT_HERO_COLOR;
	else if (type == GAME_OBJECT_SWITCH_ON) return GAME_OBJECT_SWITCH_ON_COLOR;
	else if (type == GAME_OBJECT_DOOR_OPEN) return GAME_OBJECT_DOOR_OPEN_COLOR;
	else return GAME_OBJECT_EMPTY_COLOR;
}


int isWalkable(int game_object_type)
{

	int walkableList[GAME_OBJECT_WALKABLE_N] = GAME_OBJECT_WALKABLE;

	for (int i = 0 ; i < GAME_OBJECT_WALKABLE_N ; i++)
		if (walkableList[i] == game_object_type) return 1;

	return 0;

}


int isSolid(int game_object_type)
{
	int solidList[GAME_OBJECT_SOLID_N] = GAME_OBJECT_SOLID;

	for (int i = 0 ; i < GAME_OBJECT_SOLID_N ; i++)
		if (solidList[i] == game_object_type) return 1;

	return 0;
}

