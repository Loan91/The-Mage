#pragma once

#include "chaser.h"
#include "interactable.h"
#include "boss.h"

class Map {
public:
	std::ifstream mapFile;
	std::vector<std::vector<std::unique_ptr<MapEntities>>> mapObjects;
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::shared_ptr<Interactable>> objects;
	bool wallDestroyed = false; //pour �viter de faire des boucles inutiles quand aucun mur n'est d�truit

	std::string line;

	Map();

	void loadMap(Player& player);
};