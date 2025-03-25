#pragma once

#include "player.h"
#include "mapEntities.h"

template <typename T>
class Projectile {
public:
    T speedX = 0;
    T speedY = 0;
    T posX = 0;
    T posY = 0;
    bool state = true;
    sf::Sprite sprite;

    Projectile(T xSpeed, T ySpeed, T xPos, T yPos) : speedX(xSpeed), speedY(ySpeed), posX(xPos), posY(yPos) {
        sprite.setPosition(xPos, yPos);
    }
};

class Boss : public Enemy {
public:
    float atk = 10;
    std::vector<float> randomSpeed = { 100, -100, 300, -300, 500, -500 };
    float shootTimer = 0;
    float shootCooldown = 1;
    std::vector<std::unique_ptr<Projectile<float>>> projectiles;
    float projectileInitialPosX = 0;
    float projectileInitialPosY = 0;

    Boss(float xPos, float yPos);

    void update(float deltaTime) override;
    void draw(sf::RenderWindow& window, sf::Sprite& sprite1, sf::Sprite& sprite2, sf::Texture& texture1, sf::Texture& texture2) override;
    void behavior(float& deltaTime, sf::View& view, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player) override;
};