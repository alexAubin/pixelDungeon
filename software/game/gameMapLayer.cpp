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
 *	@author Alexandre Aubin
 *  @brief Game map layer methods
*/

#include "gameMapLayer.h"

ObjectColor gameMapLayer::getColor(int tile) const
{
	return layer[tile]->getColor();
}

ObjectType  gameMapLayer::getType(int tile) const
{
	return layer[tile]->getType();
}

void gameMapLayer::setTile(int tile,gameObject* object)
{
	layer[tile] = object;
}

bool gameMapLayer::isWalkable(int tile) const
{
    return layer[tile]->isWalkable();
}

void gameMapLayer::triggerAction(int tile)
{
    return layer[tile]->triggerAction();
}
