#include "boss.h"

Projectile<float>::Projectile(float xSpeed, float ySpeed, float xPos, float yPos)
    : speedX(xSpeed), speedY(ySpeed), posX(xPos), posY(yPos) {
    sprite.setPosition(xPos, yPos);
}

Boss::Boss(float xPos, float yPos) {
    sprite.setPosition(xPos, yPos);
    type = "boss";
    health = 200;
    speedX = randomSpeed[rand() % randomSpeed.size()];
    speedY = randomSpeed[rand() % randomSpeed.size()];
}

void Boss::update(float deltaTime) {

    //PROJECTILES
    if (!projectiles.empty()) {
        for (auto& obj : projectiles) {
            obj->sprite.move(obj->speedX * deltaTime, obj->speedY * deltaTime);
        }
    }
    if (!projectiles.empty()) {
        for (int i = 0; i < projectiles.size(); i++) {
            if (projectiles[i]->state == false) {
                projectiles.erase(projectiles.begin() + i);
            }
        }
    }
    if (health < 0)
    {
        state = false;
    }
}

void Boss::draw(sf::RenderWindow& window, sf::Sprite& sprite1, sf::Sprite& sprite2, sf::Texture& texture1, sf::Texture& texture2) {
    sprite.setTexture(texture1);
    sprite.setScale(0.5f, 0.5f);
    window.draw(sprite);
    if (!projectiles.empty()) {
        for (auto& obj : projectiles) {
            obj->sprite.setTexture(texture2);
            obj->sprite.setScale(0.1f, 0.1f);
            window.draw(obj->sprite);
        }
    }
}

void Boss::behavior(float& deltaTime, sf::View& view, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player) {
    if (abs(player.sprite.getPosition().x - sprite.getPosition().x) < view.getSize().x
        && abs(player.sprite.getPosition().y - sprite.getPosition().y) < view.getSize().y) {

        sprite.move(speedX * deltaTime, speedY * deltaTime);

        if (sprite.getGlobalBounds().contains(player.sprite.getPosition())) {
            player.hitLimit = true;
        }
        else if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds()) == false) {
            player.hitLimit = false;
        }

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
                        sprite.move(-speedX * 2 * deltaTime, -speedY * 2 * deltaTime);
                        speedX = randomSpeed[rand() % randomSpeed.size()];
                        speedY = randomSpeed[rand() % randomSpeed.size()];
                    }
                    if (!projectiles.empty()) {
                        for (auto& obj : projectiles) {
                            if (obj->sprite.getGlobalBounds().intersects(wall->sprite.getGlobalBounds())) {
                                obj->state = false;
                            }
                        }
                    }
                }
            }
        }
        for (auto& obj : projectiles) {
            if (obj->sprite.getGlobalBounds().intersects(player.sprite.getGlobalBounds())) {
                if (player.gotHit == false) {
                    obj->state = false;
                    player.gotHit = true;
                    player.hp -= atk;
                }
            }
        }

        //SHOOT
        shootTimer += deltaTime;
        if (shootTimer > shootCooldown) {
            projectileInitialPosX = sprite.getPosition().x + (sprite.getLocalBounds().width * sprite.getScale().x) / 2 - 25;
            projectileInitialPosY = sprite.getPosition().y + (sprite.getLocalBounds().height * sprite.getScale().y) / 2 - 25;

            projectiles.emplace_back(std::make_unique<Projectile<float>>(-300, -300, projectileInitialPosX, projectileInitialPosY));
            projectiles.emplace_back(std::make_unique<Projectile<float>>(-300, 300, projectileInitialPosX, projectileInitialPosY));
            projectiles.emplace_back(std::make_unique<Projectile<float>>(300, 300, projectileInitialPosX, projectileInitialPosY));
            projectiles.emplace_back(std::make_unique<Projectile<float>>(300, -300, projectileInitialPosX, projectileInitialPosY));

            shootTimer = 0;
        }
    }
}
