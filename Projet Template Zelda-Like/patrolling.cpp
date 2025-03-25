#include "patrolling.h"

PatrollingEnemy::PatrollingEnemy(float xPos, float yPos) {
    type = "patrolling";
    sprite.setScale(0.1f, 0.1f);
    sprite.setPosition({ xPos, yPos });
    posX = xPos;
    posY = yPos;
    /*speedX = 100;
    speedY = 100;*/
    speedX = randomSpeed[rand() % 6];
    speedY = randomSpeed[rand() % 6];
    atk = 10;
}

void PatrollingEnemy::behavior(float& deltaTime, sf::View& view, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player) {
    if (abs(player.sprite.getPosition().x - sprite.getPosition().x) < view.getSize().x /1.7
        && abs(player.sprite.getPosition().y - sprite.getPosition().y) < view.getSize().y /1.7) {

        if (sprite.getGlobalBounds().contains(player.sprite.getPosition())) {
            player.hitLimit = true;
        }
        else if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()) == false) {
            player.hitLimit = false;
        }
        sprite.move(speedX * deltaTime, speedY * deltaTime);

        if (player.hitLimit == false) {
            if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
                if (player.gotHit == false) {
                    player.hitLimit = true;
                    player.gotHit = true;
                    player.hp -= atk;
                }
            }
        }

        for (auto& wallz : walls) {
            for (auto& wall : wallz) {
                if (wall->type == "wall") {
                    if (sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                        /*speedY = -speedY;
                        speedX = -speedX;*/
                        sprite.move(-speedX * 2 * deltaTime, -speedY * 2 * deltaTime); //pour éviter qu'ils s'enfoncent dans le murx
                        speedX = randomSpeed[rand() % randomSpeed.size()];
                        speedY = randomSpeed[rand() % randomSpeed.size()];
                    }
                }
            }
        }
    }
}