/********************************

          Pixel Dungeon
           by Djidane

   Game objects class definition

********************************/

/**
 *	@author Djidane
 * 	@file gameObject.h
 *  @brief Game objects class definition
 */

#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "gameCommon.h"

class gameObject
{
	public:

		enum Type
		{
			EMPTY,
			WALL,
			HERO,
			SWITCH,
			DOOR,
			TELEPORT,
			GOLDP,
			MONSTER,
			HPPOT,
			MPPOT
		};

		enum Color
		{
			EMPTY 		= EMPTY_ID,
			WALL  		= WHITE_ID,
			SWITCH_OFF 	= KINGBLUE_ID,
			SWITCH_ON 	= ORANGE_ID,
			DOOR_CLOSED = CYAN_ID,
			DOOR_OPEN 	= EMPTY_ID,
			TELEPORT 	= ORANGE_ID,
			GOLDP 		= YELLOW_ID,
			MONSTER 	= RED_ID,
			HPPOT 		= GREEN_ID,
			MPPOT 		= VIOLET_ID,
			HERO	 	= BLUE_ID
		};

		// Constructor
		gameObject();

		// Destructor
		~gameObject();

		// Accessors
		bool isWalkable() { return walkable; };
		bool isSolid()    { return solid;    };
		short int getColor() { return color;    };
		short int getType()  { return type;     };
		int id()          { return id;       };

	private:

		bool walkable;
		bool solid;

		short int color;
		gameObjectType type;
		int id;

};

// #############
// # Empty object
// #############
class gameObject_Empty
{
	public:

		gameObject_Empty(int id_)
		{
			walkable = true;
			solid = false;
			color = Color::EMPTY;
			type = Type::EMPTY;
			id = id_;
		}
};

// #############
// # Walls
// #############
class gameObject_Wall
{
	public:

		gameObject_Wall(int id_)
		{
			walkable = false;
			solid = true;
			color = Color::WALL;
			type = Type::WALL;
			id = id_;
		}
};

// #############
// # Switches
// #############
class gameObject_Switch
{
	public:

		gameObject_Switch(int id_, bool state_, short int linkId_)
		{
			walkable = false;
			solid = true;
			color = Color::SWITCH_OFF;
			type = Type::SWITCH;
			id = id_;

			state = state_;
			linkId = linkId_;
		}

	private:

		bool state;
		short int linkID;
};

// #############
// # Doors
// #############
class gameObject_Door
{
	public:

		gameObject_Door(int id_, bool state_)
		{
			walkable = false;
			solid = true;
			color = Color::DOOR_OPEN;
			type = Type::DOOR;
			id = id_;

			state = state_;
		}

	private:

		bool state;
};

// #############
// # Teleports
// #############
class gameObject_Teleport
{
	public:

		gameObject_Teleport(int id_, short int linkId_)
		{
			walkable = true;
			solid = false;
			color = Color::TELEPORT;
			type = Type::TELEPORT;
			id = id_;

			linkId = linkId;
		}

	private:

		short int linkId;
};

// #############
// # Gold pieces
// #############
class gameObject_Goldp
{
	public:

		gameObject_Goldp(int id_, short int value_)
		{
			walkable = true;
			solid = false;
			color = Color::GOLDP;
			type = Type::GOLDP;
			id = id_;

			state = true;
			value = value_;
		}

	private:

		bool state;
		short int value;
};

// #############
// # HP Pot
// #############
class gameObject_Hppot
{
	public:

		gameObject_Hppot(int id_, short int value_)
		{
			walkable = true;
			solid = false;
			color = Color::HPPOT;
			type = Type::HPPOT;
			id = id_;

			state = true;
			value = value_;
		}

	private:

		bool state;
		short int value;
};

// #############
// # MP Pot
// #############
class gameObject_Hppot
{
	public:

		gameObject_Hppot(int id_, short int value_)
		{
			walkable = true;
			solid = false;
			color = Color::MPPOT;
			type = Type::MPPOT;
			id = id_;

			state = true;
			value = value_;
		}

	private:

		bool state;
		short int value;
};

// #############
// # Monster
// #############

class gameObject_Monster
{
	public:

		gameObject_Monster(int id_, int x_, int y_, short int hp_)
		{
			walkable = true;
			solid = false;
			color = Color::MPPOT;
			type = Type::MPPOT;
			id = id_;

			state = true;
			hp = hp_;
			x = x_;
			y = y_;
		}

	private:

		int x;
		int y;
		bool state;
		short int hp;
};

// #############
// # Hero
// #############

class gameObject_Hero
{
	public:

		gameObject_Hero(int id_, int x_, int y_)
		{
			walkable = true;
			solid = false;
			color = Color::MPPOT;
			type = Type::MPPOT;
			id = id_;

			x = x_;
			y = y_;

			hp = hp_;
			mp = mp_;
			goldp = goldp_;
		}

	private:

		int x;
		int y;

		short int hp;
		short int mp;
		short int goldp;
};

#endif
