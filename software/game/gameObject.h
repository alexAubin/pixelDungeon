/*
 ##############################################################################
 #                                                                            #
 #    This file is part of PixelDungeon.                                      #
 #                                                                            #
 #    PixelDungeon is free software: you can redistribute it and/or modify    #
 #    it under the terms of the GNU General Public License as published by    #
 #    the Free Software Foundation, either version 3 of the License, or       #
 #     (at your option) any later version.                                    #
 #                                                                            #
 #    PixelDungeon is distributed in the hope that it will be useful,         #
 #    but WITHOUT ANY WARRANTY; without even the implied warranty of          #
 #    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           #
 #    GNU General Public License for more details.                            #
 #                                                                            #
 #    You should have received a copy of the GNU General Public License       #
 #    along with PixelDungeon.  If not, see <http://www.gnu.org/licenses/>.   #
 #                                                                            #
 ##############################################################################
*/

/**
 *    @author Alexandre Aubin
 *  @brief Game objects class definition
*/

#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

#include "../hal/display.h"
#include "gameCommon.h"

enum ObjectType
{
    OBJECTTYPE_EMPTY,
    OBJECTTYPE_WALL,
    OBJECTTYPE_HERO,
    OBJECTTYPE_SWITCH,
    OBJECTTYPE_DOOR,
    OBJECTTYPE_TELEPORT,
    OBJECTTYPE_GOLDP,
    OBJECTTYPE_MONSTER,
    OBJECTTYPE_HPPOT,
    OBJECTTYPE_MPPOT
};

enum ObjectColor
{
    OBJECTCOLOR_EMPTY       = DISPLAYCOLOR_EMPTY,
    OBJECTCOLOR_WALL        = DISPLAYCOLOR_WHITE,
    OBJECTCOLOR_SWITCH_OFF  = DISPLAYCOLOR_KINGBLUE,
    OBJECTCOLOR_SWITCH_ON   = DISPLAYCOLOR_ORANGE,
    OBJECTCOLOR_DOOR_CLOSED = DISPLAYCOLOR_CYAN,
    OBJECTCOLOR_DOOR_OPEN   = DISPLAYCOLOR_EMPTY,
    OBJECTCOLOR_TELEPORT    = DISPLAYCOLOR_ORANGE,
    OBJECTCOLOR_GOLDP       = DISPLAYCOLOR_YELLOW,
    OBJECTCOLOR_MONSTER     = DISPLAYCOLOR_RED,
    OBJECTCOLOR_HPPOT       = DISPLAYCOLOR_GREEN,
    OBJECTCOLOR_MPPOT       = DISPLAYCOLOR_VIOLET,
    OBJECTCOLOR_HERO        = DISPLAYCOLOR_BLUE
};

class gameObject
{
    public:

        // Constructor
        gameObject(int id_, bool walkable_, bool solid_, ObjectType type_, ObjectColor color_)
        {
              id     =   id_;
            walkable = walkable_;
             solid   =  solid_;
             type    =  type_;
             color   =  color_;
        }


        // Accessors
        int getId()            const { return id;       };
        ObjectType getType()   const { return type;     };
        bool isWalkable()      const { return walkable; };
        bool isSolid()         const { return solid;    };
        ObjectColor getColor() const { return color;    };

        // Triggers
        virtual void triggerAction() = 0;
        virtual void triggerActionViaLink() = 0;

    protected:

        int id;
        bool walkable;
        bool solid;
        ObjectType type;
        ObjectColor color;

};

// ####################
// #   Empty object   #
// ####################

class gameObject_Empty : public gameObject
{
    public:

        gameObject_Empty(int id_):
        gameObject::gameObject(id_,true,false,OBJECTTYPE_EMPTY,OBJECTCOLOR_EMPTY) { }

        void triggerAction() {}
        void triggerActionViaLink() {}
};

// #############
// #   Walls   #
// #############

class gameObject_Wall : public gameObject
{
    public:

        gameObject_Wall(int id_):
        gameObject::gameObject(id_,false,true,OBJECTTYPE_WALL,OBJECTCOLOR_WALL) { } 

        void triggerAction() {}
        void triggerActionViaLink() {}
};

// ################
// #   Switches   #
// ################

class gameObject_Switch : public gameObject
{
    public:

        gameObject_Switch(int id_, bool activated_, gameObject* link_):
        gameObject::gameObject(id_,true,false,OBJECTTYPE_SWITCH,OBJECTCOLOR_SWITCH_OFF)
        {
            activated = activated_;
            link = link_;
            
            if (activated_) color = OBJECTCOLOR_SWITCH_ON;
        }

        void switchOn()
        {
            activated = true;
            color = OBJECTCOLOR_SWITCH_ON;
            link->triggerActionViaLink();
        }

        void switchOff()
        {
            activated = false;
            color = OBJECTCOLOR_SWITCH_OFF;
            link->triggerActionViaLink();
        }

        void triggerAction()
        {
            if (activated) switchOff();
            else       switchOn();
        }
        void triggerActionViaLink() {}

    private:

        bool activated;
        gameObject* link;
};

// #############
// #   Doors   #
// #############

class gameObject_Door : public gameObject
{
    public:

        gameObject_Door(int id_, bool opened_):
        gameObject::gameObject(id_,false,true,OBJECTTYPE_DOOR,OBJECTCOLOR_DOOR_CLOSED)
        {
            opened = opened_;

            if (opened) open();
        }

        void open()
        {
            solid = false;
            opened = true;
            walkable = true;
            //gameMonsterAI::setWalkableMap(tile,isWalkable(tile));
            color = OBJECTCOLOR_DOOR_OPEN;
        }
    
        void close()
        {
            solid = true;
            opened = false;
            walkable = false;
            color = OBJECTCOLOR_DOOR_CLOSED;
        }

        void triggerAction() {}
        void triggerActionViaLink() 
        {
            if (opened) close();
            else       open();
        }

    private:

        bool opened;


};

// #################
// #   Teleports   #
// #################

class gameObject_Teleport : public gameObject
{
    public:

        gameObject_Teleport(int id_, gameObject* link_):
        gameObject::gameObject(id_,true,false,OBJECTTYPE_TELEPORT,OBJECTCOLOR_TELEPORT)
        {
            link = link_;
        }

        void triggerAction() {}
        void triggerActionViaLink() {}

    private:

        gameObject* link;
};

// ###################
// #   Gold pieces   #
// ###################

class gameObject_Goldp : public gameObject
{
    public:

        gameObject_Goldp(int id_, short int value_):
        gameObject::gameObject(id_,true,false,OBJECTTYPE_GOLDP,OBJECTCOLOR_GOLDP)
        {
            state = true;
            value = value_;
        }

        void triggerAction() {}
        void triggerActionViaLink() {}

    private:

        bool state;
        short int value;
};

// ##############
// #   HP Pot   #
// ##############

class gameObject_Hppot : public gameObject
{
    public:

        gameObject_Hppot(int id_, short int value_):
        gameObject::gameObject(id_,true,false,OBJECTTYPE_HPPOT,OBJECTCOLOR_HPPOT)
        {
            state = true;
            value = value_;
        }

        void triggerAction() {}
        void triggerActionViaLink() {}

    private:

        bool state;
        short int value;
};

// ##############
// #   MP Pot   #
// ##############

class gameObject_Mppot : public gameObject
{
    public:

        gameObject_Mppot(int id_, short int value_):
        gameObject::gameObject(id_,true,false,OBJECTTYPE_MPPOT,OBJECTCOLOR_MPPOT)
        {
            state = true;
            value = value_;
        }

        void triggerAction() {}
        void triggerActionViaLink() {}

    private:

        bool state;
        short int value;
};

// #################
// #   Creatures   #
// #################

class gameObject_Creature : public gameObject
{
     public:

        gameObject_Creature(int id, int x_, int y_, short int hp_, ObjectType type, ObjectColor color):
        gameObject::gameObject(id,false,true,type,color)
        {
            alive = true;
            hp = hp_;
            x = x_;
            y = y_;
        }

        virtual void triggerAction() {}
        virtual void triggerActionViaLink() {}

        int getX() { return x; }
        int getY() { return y; }
    
        void setX(int x_) { x = x_; }
        void setY(int y_) { y = y_; }

        void setPosition(int x_, int y_) { x = x_; y = y_; }

    private:

        int x;
        int y;
        bool alive;
        short int hp;
  
};

// ###############
// #   Monster   #
// ###############

class gameObject_Monster : public gameObject_Creature
{
    public:

        gameObject_Monster(int id, int x, int y, short int hp):
        gameObject_Creature::gameObject_Creature(id,x,y,hp,OBJECTTYPE_MONSTER,OBJECTCOLOR_MONSTER)
        {
        }

        void triggerAction() {}
        void triggerActionViaLink() { }

 //   private:

};

// ############
// #   Hero   #
// ############

class gameObject_Hero : public gameObject_Creature
{
    public:

        gameObject_Hero(int id, int x, int y):
        gameObject_Creature::gameObject_Creature(id,x,y,10,OBJECTTYPE_HERO,OBJECTCOLOR_HERO)
        {
            mp = 10;
            goldp = 0;
        }

        void triggerAction() { }
        void triggerActionViaLink() { }

    private:

        short int mp;
        short int goldp;
};

#endif
