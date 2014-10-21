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

class gameManager;

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
    OBJECTCOLOR_EMPTY              = DISPLAYCOLOR_EMPTY,
    OBJECTCOLOR_WALL               = DISPLAYCOLOR_WHITE,
    OBJECTCOLOR_SWITCH_OFF         = DISPLAYCOLOR_KINGBLUE,
    OBJECTCOLOR_SWITCH_ON          = DISPLAYCOLOR_ORANGE,
    OBJECTCOLOR_DOOR_CLOSED        = DISPLAYCOLOR_CYAN,
    OBJECTCOLOR_DOOR_OPEN          = DISPLAYCOLOR_EMPTY,
    OBJECTCOLOR_TELEPORT           = DISPLAYCOLOR_ORANGE,
    OBJECTCOLOR_GOLDP              = DISPLAYCOLOR_YELLOW,
    OBJECTCOLOR_HPPOT              = DISPLAYCOLOR_GREEN,
    OBJECTCOLOR_MPPOT              = DISPLAYCOLOR_VIOLET,

    OBJECTCOLOR_HERO_FULLHEALTH    = DISPLAYCOLOR_GREEN,
    OBJECTCOLOR_HERO_3QRTHEALTH    = DISPLAYCOLOR_LIGHTGREEN,
    OBJECTCOLOR_HERO_2QRTHEALTH    = DISPLAYCOLOR_YELLOW,
    OBJECTCOLOR_HERO_1QRTHEALTH    = DISPLAYCOLOR_ORANGE,

    OBJECTCOLOR_MONSTER_FULLHEALTH = DISPLAYCOLOR_RED,
    OBJECTCOLOR_MONSTER_3QRTHEALTH = DISPLAYCOLOR_RED_HIGH,
    OBJECTCOLOR_MONSTER_2QRTHEALTH = DISPLAYCOLOR_RED_MEDIUM,
    OBJECTCOLOR_MONSTER_1QRTHEALTH = DISPLAYCOLOR_RED_LOW

};

class gameObject_Hero;

class gameObject
{
    public:

        // Constructor
        gameObject(bool walkable_, bool solid_, ObjectType type_, ObjectColor color_)
        {
             walkable = walkable_;
             solid   =  solid_;
             type    =  type_;
             color   =  color_;

             if (type == OBJECTTYPE_HERO)  theHero = (gameObject_Hero*) this;
             if (type == OBJECTTYPE_EMPTY) emptyObject = this;
        }


        // Accessors
        ObjectType getType()   const { return type;     };
        bool isWalkable()      const { return walkable; };
        bool isSolid()         const { return solid;    };
        ObjectColor getColor() const { return color;    };

        // Triggers
        virtual void triggerFromAction() = 0;
        virtual void triggerFromLink() = 0;

        static gameObject_Hero* theHero;
        static gameObject* emptyObject;

    protected:

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

        gameObject_Empty():
        gameObject::gameObject(true,false,OBJECTTYPE_EMPTY,OBJECTCOLOR_EMPTY) { }

        void triggerFromAction() {}
        void triggerFromLink() {}
};

// #############
// #   Walls   #
// #############

class gameObject_Wall : public gameObject
{
    public:

        gameObject_Wall():
        gameObject::gameObject(false,true,OBJECTTYPE_WALL,OBJECTCOLOR_WALL) { } 

        void triggerFromAction() {}
        void triggerFromLink() {}
};

// ################
// #   Switches   #
// ################

class gameObject_Switch : public gameObject
{
    public:

        gameObject_Switch(bool activated_, bool invisibleAndSingleUse_, gameObject** links_, short int nLinks_):
        gameObject::gameObject(true,false,OBJECTTYPE_SWITCH,OBJECTCOLOR_EMPTY)
        {
            activated = activated_;

            nLinks = nLinks_;
            links = new gameObject*[nLinks];
            for (short int i = 0 ; i < nLinks ; i++)
            {
                links[i] = links_[i]; 
            }

            if (invisibleAndSingleUse_) usage = 1;
            else
            {
                usage = -1;
                if (activated_) color = OBJECTCOLOR_SWITCH_ON;
                else            color = OBJECTCOLOR_SWITCH_OFF;
            }
        }

        void switchOn()
        {
            activated = true;
            if (usage < 0) color = OBJECTCOLOR_SWITCH_ON;
           
            for (int i = 0 ; i < nLinks ; i++)
            {
                if (links[i]) links[i]->triggerFromLink();
            }
        }

        void switchOff()
        {
            activated = false;
            if (usage < 0) color = OBJECTCOLOR_SWITCH_OFF;

            for (int i = 0 ; i < nLinks ; i++)
            {
                if (links[i]) links[i]->triggerFromLink();
            }
        }

        void triggerFromAction()
        {
            if (!usage) return;

            if (activated) switchOff();
            else           switchOn();

            if (usage > 0) usage--;
        }
        void triggerFromLink() { triggerFromAction(); }

    private:

        bool activated;
        short int usage;
        gameObject** links;
        short int nLinks;
};

// #############
// #   Doors   #
// #############

class gameObject_Door : public gameObject
{
    public:

        gameObject_Door(bool opened_):
        gameObject::gameObject(false,true,OBJECTTYPE_DOOR,OBJECTCOLOR_DOOR_CLOSED)
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

        void triggerFromAction() {}
        void triggerFromLink() 
        {
            if (opened) close();
            else        open();
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

        gameObject_Teleport(gameObject* link_):
        gameObject::gameObject(true,false,OBJECTTYPE_TELEPORT,OBJECTCOLOR_TELEPORT)
        {
            link = link_;
        }

        void triggerFromAction() {}
        void triggerFromLink() {}

    private:

        gameObject* link;
};

// ###################
// #   Gold pieces   #
// ###################

class gameObject_Goldp : public gameObject
{
    public:

        gameObject_Goldp(short int value_):
        gameObject::gameObject(true,false,OBJECTTYPE_GOLDP,OBJECTCOLOR_GOLDP)
        {
            state = true;
            value = value_;
        }

        void triggerFromAction() {}
        void triggerFromLink() {}

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

        gameObject_Mppot(short int value_):
        gameObject::gameObject(true,false,OBJECTTYPE_MPPOT,OBJECTCOLOR_MPPOT)
        {
            state = true;
            value = value_;
        }

        void triggerFromAction() {}
        void triggerFromLink() {}

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

        gameObject_Creature(int x_, int y_, short int hpMax_, ObjectType type, ObjectColor color):
        gameObject::gameObject(false,true,type,color)
        {
            alive = true;
            hpMax = hpMax_;
            hp = hpMax;

            x = x_;
            y = y_;
            objectStandingOn = emptyObject;
        }

        virtual void triggerFromAction() { }
        virtual void triggerFromDeath() = 0;

        int         getX()                { return x; }
        int         getY()                { return y; }
        gameObject* getObjectStandingOn() { return objectStandingOn; }
    
        void setX(int x_)                            { x = x_; }
        void setY(int y_)                            { y = y_; }
        void setPosition(int x_, int y_)             { x = x_; y = y_; }
        void setObjectStandingOn(gameObject* object) { objectStandingOn = object; }
       
        short int receiveAttack()                  { return modifyHealth(-1);      }
        short int restoreHealth(short int restore) { return modifyHealth(restore); }

        short int modifyHealth(short int modifier)
        {
            if (hp <= 0) return 0;

            hp += modifier;

            if (hp <= 0)  { hp = 0; triggerFromDeath(); }
            if (hp > hpMax) hp = hpMax;

            color = healthToColor();
        
            return hp;
        }

        virtual ObjectColor healthToColor() = 0;

    protected:

        int x;
        int y;
        bool alive;
        short int hp;
        short int hpMax;

        gameObject* objectStandingOn;
  
};

// ###############
// #   Monster   #
// ###############

class gameObject_Monster : public gameObject_Creature
{
    public:

        gameObject_Monster(int x, int y, short int hpMax, gameObject** deathLinks_ = 0, short int nDeathLinks_ = 0):
        gameObject_Creature::gameObject_Creature(x,y,hpMax,OBJECTTYPE_MONSTER,OBJECTCOLOR_MONSTER_FULLHEALTH)
        {
            nDeathLinks = nDeathLinks_;
            deathLinks = new gameObject*[nDeathLinks];
            for (short int i = 0 ; i < nDeathLinks ; i++)
            {
                deathLinks[i] = deathLinks_[i]; 
            }
        }

        void triggerFromAction() { }
        void triggerFromDeath();
        void triggerFromLink();

        virtual ObjectColor healthToColor()
        {
                 if (hp >= 7) return OBJECTCOLOR_MONSTER_FULLHEALTH;
            else if (hp >= 5) return OBJECTCOLOR_MONSTER_3QRTHEALTH;
            else if (hp >= 3) return OBJECTCOLOR_MONSTER_2QRTHEALTH;
            else if (hp >= 1) return OBJECTCOLOR_MONSTER_1QRTHEALTH;
            else              return OBJECTCOLOR_MONSTER_1QRTHEALTH;
        }
        

    private:

        gameObject** deathLinks;
        short int nDeathLinks;
};

// ############
// #   Hero   #
// ############

class gameObject_Hero : public gameObject_Creature
{
    public:

        gameObject_Hero(int x, int y):
        gameObject_Creature::gameObject_Creature(x,y,8,OBJECTTYPE_HERO,OBJECTCOLOR_HERO_FULLHEALTH)
        {
            mp = 10;
            goldp = 0;
        }

        void triggerFromAction() { }
        void triggerFromLink()   { }
        void triggerFromDeath(); 

        virtual ObjectColor healthToColor()
        {
                 if (hp >= 7) return OBJECTCOLOR_HERO_FULLHEALTH;
            else if (hp >= 5) return OBJECTCOLOR_HERO_3QRTHEALTH;
            else if (hp >= 3) return OBJECTCOLOR_HERO_2QRTHEALTH;
            else if (hp >= 1) return OBJECTCOLOR_HERO_1QRTHEALTH;
            else              return OBJECTCOLOR_MONSTER_FULLHEALTH;
        }


    private:

        short int mp;
        short int goldp;
};


// ##############
// #   HP Pot   #
// ##############

class gameObject_Hppot : public gameObject
{
    public:

        gameObject_Hppot(short int value_):
        gameObject::gameObject(true,false,OBJECTTYPE_HPPOT,OBJECTCOLOR_HPPOT)
        {
            state = true;
            value = value_;
        }

        void triggerFromAction() 
        {
            if (state == true)
            {
                color = OBJECTCOLOR_EMPTY;
                gameObject::theHero->restoreHealth(value);
                state = false;
            }
        }
        void triggerFromLink() {}

    private:

        bool state;
        short int value;
};

#endif
