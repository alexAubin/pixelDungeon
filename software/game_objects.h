
/********************************

          Pixel Dungeon
           by Djidane

     Game objects-specific definitions

********************************/

/**
 *	@author Djidane
 * 	@file game_objects.h
 *  @brief Game objects-specific definitions
 */

#ifndef GAME_OBJECTS_H_
#define GAME_OBJECTS_H_

#include "common.h"
#include "hal_display.h"

// *********************************************************************
//                           Objects
// *********************************************************************

enum { 	GAME_OBJECT_EMPTY,
		GAME_OBJECT_WALL,
		GAME_OBJECT_SWITCH,
		GAME_OBJECT_DOOR,
		GAME_OBJECT_TELEPORT,
		GAME_OBJECT_GOLDP,
		GAME_OBJECT_MONSTER,
		GAME_OBJECT_HPPOT,
		GAME_OBJECT_MPPOT,
		GAME_OBJECT_HERO,
		GAME_OBJECT_SWITCH_ON,
		GAME_OBJECT_DOOR_OPEN };

// *********************************************************************
//						Easy/light objects
// *********************************************************************

struct object
{
	bool walkable;
	bool solid;
};

// # ####### #
// #  Empty  #
// # ####### #

struct objectEmpty
{
	struct object object_;
};

#define GAME_OBJECT_EMPTY_N 1
#define GAME_OBJECT_INIT_EMPTY0 { {1,0} }

// # ####### #
// #  Walls  #
// # ####### #

struct objectWall
{
	struct object object_;
};

#define GAME_OBJECT_WALL_N 1
#define GAME_OBJECT_INIT_WALL0 { {0,1} }

// *********************************************************************
//						Doors and switches
// *********************************************************************

// # ########## #
// #  Switches  #
// # ########## #

struct objectSwitch
{
	struct object object_;
	bool state;
	short int links[10];
};

#define GAME_OBJECT_SWITCH_N 1
#define GAME_OBJECT_INIT_SWITCH0 { {0,1},0,{0,-1,-1,-1,-1,-1,-1,-1,-1,-1} }

// # ####### #
// #  Doors  #
// # ####### #

struct objectDoor
{
	struct object object_;
	bool state;
};

#define GAME_OBJECT_DOOR_N 1
#define GAME_OBJECT_INIT_DOOR0 { {0,1},0 }

// # ########### #
// #  Teleports  #
// # ########### #

struct objectTeleport
{
	struct object object_;
	int x_dest;
	int y_dest;
};

#define GAME_OBJECT_TELEPORT_N 1
#define GAME_OBJECT_INIT_TELEPORT0 { {0,1},1,2 }

// *********************************************************************
//						Consommables
// *********************************************************************

// # ########### #
// #    Goldp    #
// # ########### #

struct objectGoldp
{
	struct object object_;
	bool state;
	int value;
};

#define GAME_OBJECT_GOLDP_N 1
#define GAME_OBJECT_INIT_GOLDP0 { {0,1},1,1 }

// # ########### #
// #    HP Pot   #
// # ########### #

struct objectHppot
{
	struct object object_;
	bool state;
	int value;
};

#define GAME_OBJECT_HPPOT_N 1
#define GAME_OBJECT_INIT_HPPOT0 { {0,1},1,2 }

// # ########### #
// #    MP Pot   #
// # ########### #

struct objectMppot
{
	struct object object_;
	bool state;
	int value;
};

#define GAME_OBJECT_MPPOT_N 1
#define GAME_OBJECT_INIT_MPPOT0 { {0,1},1,2 }

// *********************************************************************
//						Creatures
// *********************************************************************

// # ########### #
// #   Monster   #
// # ########### #

struct objectMonster
{
	struct object object_;
	int x;
	int y;
	bool state;
	int hp;
};

#define GAME_OBJECT_MONSTER_N 1
#define GAME_OBJECT_INIT_MONSTER0 { {0,1},1,6,1,3 }

// # ########### #
// #     Hero    #
// # ########### #

struct objectHero
{
	struct object object_;
	int x;
	int y;
	bool state;
	int hp;
	int mp;
	int goldp;
};

#define GAME_OBJECT_HERO_N 1
#define GAME_OBJECT_INIT_THEHERO { {0,1},6,6,1,3,0,0 }

// *********************************************************************
//						Defines
// *********************************************************************

#define GAME_OBJECT_SOLID { GAME_OBJECT_WALL, GAME_OBJECT_DOOR, GAME_OBJECT_MONSTER }
#define GAME_OBJECT_SOLID_N 3
#define GAME_OBJECT_WALKABLE	{ GAME_OBJECT_EMPTY, GAME_OBJECT_SWITCH , GAME_OBJECT_GOLDP, GAME_OBJECT_TELEPORT, GAME_OBJECT_MPPOT, GAME_OBJECT_HPPOT, GAME_OBJECT_SWITCH_ON, GAME_OBJECT_DOOR_OPEN }
#define GAME_OBJECT_WALKABLE_N 9

#define GAME_OBJECT_EMPTY_COLOR 	EMPTY_ID
#define GAME_OBJECT_WALL_COLOR		WHITE_ID
#define GAME_OBJECT_SWITCH_COLOR	KINGBLUE_ID
#define GAME_OBJECT_DOOR_COLOR		CYAN_ID
#define GAME_OBJECT_TELEPORT_COLOR	ORANGE_ID
#define GAME_OBJECT_GOLDP_COLOR		YELLOW_ID
#define GAME_OBJECT_MONSTER_COLOR	RED_ID
#define GAME_OBJECT_HPPOT_COLOR		GREEN_ID
#define GAME_OBJECT_MPPOT_COLOR		VIOLET_ID
#define GAME_OBJECT_HERO_COLOR 		BLUE_ID
#define GAME_OBJECT_SWITCH_ON_COLOR ORANGE_ID
#define GAME_OBJECT_DOOR_OPEN_COLOR EMPTY_ID

// *********************************************************************
//                           Prototypes
// *********************************************************************

int getGameObjectTypeColor(int type);

int isWalkable(int game_object_type);
int isSolid(int game_object_type);

#endif
