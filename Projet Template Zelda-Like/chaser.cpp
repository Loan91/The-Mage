#include "chaser.h"

ChaserEnemy::ChaserEnemy(float xPos, float yPos) {
	type = "chaser";
	sprite.setScale(0.1f, 0.1f);
	sprite.setPosition({ xPos, yPos });
	posX = xPos;
	posY = yPos;
	speedX = 100;
	speedY = 100;
	atk = 10;
}

void ChaserEnemy::behavior(float& deltaTime, sf::View& view, std::vector<std::vector<std::unique_ptr<MapEntities>>>& walls, Player& player) {
	playerPosX = player.sprite.getPosition().x + (player.sprite.getLocalBounds().width * player.sprite.getScale().x
		+ player.sprite.getLocalBounds().height * player.sprite.getScale().y
		- sprite.getLocalBounds().width * sprite.getScale().x
		- sprite.getLocalBounds().height * sprite.getScale().y) / 4;
	playerPosY = player.sprite.getPosition().y + (player.sprite.getLocalBounds().width * player.sprite.getScale().x
		+ player.sprite.getLocalBounds().height * player.sprite.getScale().y
		- sprite.getLocalBounds().width * sprite.getScale().x
		- sprite.getLocalBounds().height * sprite.getScale().y) / 4;

	if (abs(player.sprite.getPosition().x - sprite.getPosition().x) < view.getSize().x /3
		&& abs(player.sprite.getPosition().y - sprite.getPosition().y) < view.getSize().y /3) {

		if (posX > playerPosX) {
			sprite.move(-speedX * deltaTime, 0);
			if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
				if (player.gotHit == false) {
					/*playing = false;
					gameOver = true;*/
					/*enemy->state = false;*/
					sprite.move(speedX * 0.5f, 0);
					player.gotHit = true;
					player.hp -= atk;
				}
				else { sprite.move(speedX * deltaTime, 0); }
			}
			if (player.attackHitbox.getGlobalBounds().intersects(sprite.getGlobalBounds()) && player.isAttacking)
			{
				sprite.move(speedX * 0.5f, 0);
			}
		}
		if (posX < playerPosX) {
			sprite.move(speedX * deltaTime, 0);
			if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
				if (player.gotHit == false) {
					/*playing = false;
					gameOver = true;*/
					/*enemy->state = false;*/
					sprite.move(-speedX * 0.5f, 0);
					player.gotHit = true;
					player.hp -= atk;
				}
				else { sprite.move(-speedX * deltaTime, 0); }
			}
			if (player.attackHitbox.getGlobalBounds().intersects(sprite.getGlobalBounds()) && player.isAttacking)
			{
				sprite.move(-speedX * 0.5f, 0);
			}
		}
		if (posY > playerPosY) {
			sprite.move(0, -speedY * deltaTime);
			if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
				if (player.gotHit == false) {
					/*playing = false;
					gameOver = true;*/
					/*enemy->state = false;*/
					sprite.move(0, speedY * 0.5f);
					player.gotHit = true;
					player.hp -= atk;
				}
				else { sprite.move(0, speedY * deltaTime); }
			}
			if (player.attackHitbox.getGlobalBounds().intersects(sprite.getGlobalBounds()) && player.isAttacking)
			{
				sprite.move(0, speedY * 0.5f);
			}
		}
		if (posY < playerPosY) {
			sprite.move(0, speedY * deltaTime);
			if (player.sprite.getGlobalBounds().intersects(sprite.getGlobalBounds())) {
				if (player.gotHit == false) {
					/*playing = false;
					gameOver = true;*/
					/*enemy->state = false;*/
					sprite.move(0, -speedY * 0.5f);
					player.gotHit = true;
					player.hp -= atk;
				}
				else { sprite.move(0, -speedY * deltaTime); }
			}
		}
		if (player.attackHitbox.getGlobalBounds().intersects(sprite.getGlobalBounds()) && player.isAttacking)
		{
			sprite.move(0, -speedY * 0.5f);
		}
	}
}