#include "mapEntities.h"

MapEntities::MapEntities(std::string t, float xPos, float yPos, float xScale, float yScale, bool breakable) : type(t), posX(xPos), posY(yPos), scaleX(xScale), scaleY(yScale) {
	sprite.setPosition(xPos, yPos);
	sprite.setScale(xScale, yScale);
	breakableWall = breakable;
}
MapEntities::MapEntities(std::string t, std::string lockNumber, float xPos, float yPos, float xScale, float yScale)
	: type(t), lockNumber(lockNumber), posX(xPos), posY(yPos), scaleX(xScale), scaleY(yScale) {
	sprite.setPosition(xPos, yPos);
	sprite.setScale(xScale, yScale);
}