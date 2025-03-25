#include "map.h"
#include "game.h"

Map::Map() {}

void Map::loadMap(Player& player) {
	//sf::Texture wallTexture;
	//sf::Texture paveTexture;
	//wallTexture.loadFromFile("assets/wall.png");
	//paveTexture.loadFromFile("assets/pave.png");

	/*mapFile.clear();
	mapFile.seekg(0, mapFile.beg);
	line.clear();*/
	mapFile.open("assets/mapFile.txt");
	int y = 0;
	int yEnemy = 0;
	int yInteractables = 0;
	while (getline(mapFile, line)) {
		for (int i = 0; i < line.size(); i++) {
			if (line[i] == '#') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("wall", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, false));
			}
			if (line[i] == '@') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("wallDebris", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, false));
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("wall", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, true));
			}
			if (line[i] == ' ') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, false));
			}
			//CHASER
			if (line[i] == 'c') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, false));
				enemies.emplace_back(std::make_unique<ChaserEnemy>((float)i * 50.f, (float)y * 50.f));
				yEnemy++;
			}
			//PATROLLING
			if (line[i] == 'p') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, false));
				enemies.emplace_back(std::make_unique<PatrollingEnemy>((float)i * 50.f, (float)y * 50.f));
				yEnemy++;
			}
			//BOSS
			if (line[i] == 'B') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, false));
				enemies.emplace_back(std::make_unique<Boss>((float)i * 50.f, (float)y * 50.f));
				yEnemy++;
			}
			//SPEED POTION
			if (line[i] == 'b') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, false));
				objects.emplace_back(std::make_shared<Bomb>((float)i * 50.f, (float)y * 50.f));
				yInteractables++;
			}
			//KEY
			if (line[i] == 'k') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, false));
				if (/*player.key1 == false ||*/ player.lock1opened == false) {
					objects.emplace_back(std::make_shared<Key>("key1", (float)i * 50.f, (float)y * 50.f));
				}
				yInteractables++;
			}
			if (line[i] == 'h') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, false));
				objects.emplace_back(std::make_shared<Heart>("heart", (float)i * 50.f, (float)y * 50.f));
				yInteractables++;
			}
			if (line[i] == 'P') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, false));
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("pnj", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, false));
			}
			//LOCK
			if (line[i] == 'l') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("floor", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, false));
				if (player.lock1opened == false) {
					mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
					mapObjects[y].emplace_back(std::make_unique<MapEntities>("lock", "lock1", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f));
				}
			}
			if (line[i] == '1') {
				mapObjects.emplace_back(std::vector<std::unique_ptr<MapEntities>>());
				mapObjects[y].emplace_back(std::make_unique<MapEntities>("checkpoint", (float)i * 50.f, (float)y * 50.f, 0.1f, 0.1f, false));
			}
		}
		y++;
	}
	y = 0;
	yEnemy = 0;
	yInteractables = 0;
	mapFile.close();
}