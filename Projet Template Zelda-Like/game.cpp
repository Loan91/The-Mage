#include "game.h"
#include "menu.h"

Game::Game(std::vector<sf::VideoMode> modes) : /*window(sf::VideoMode(1920,1080), "Escape the Dungeon", sf::Style::Fullscreen)*/
    window(sf::VideoMode(modes[0].width, modes[0].height), "Zelda-like", sf::Style::Fullscreen), volume(50), view(sf::Vector2f(75.f, 75.f),
        sf::Vector2f((float)modes[9].width, (float)modes[9].height)) { //modes[9].width = 1280, modes[9].height = 800
    //window.setFramerateLimit(60);
}

void Game::showMenu() {
    window.setView(window.getDefaultView());
    Menu menu((float)window.getSize().x, (float)window.getSize().y);
    baseFont.loadFromFile("assets/Arial.ttf");
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    menu.moveUp();
                if (event.key.code == sf::Keyboard::Down)
                    menu.moveDown();
                if (event.key.code == sf::Keyboard::Enter) {
                    int selection = menu.getSelectedIndex();
                    if (selection == 0)
                    {
                        reset();
                        playing = true;
                        return;
                    }
                    if (selection == 1) {
                        showOptionsMenu();
                    }
                    if (selection == 2) {
                        window.close();
                    }
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                menu.handleMouseHover(window);
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int selection = menu.handleMouseClick(window);
                    if (selection == 0)
                    {

                        reset();
                        playing = true;
                        return;
                    }
                    if (selection == 1) {
                        showOptionsMenu();
                    }
                    if (selection == 2) {
                        window.close();
                    }
                }
            }
        }

        window.clear();
        menu.draw(window);
        window.display();
    }
}

void Game::loadFont() {
    if (!baseFont.loadFromFile("assets/Arial.ttf")) {
        std::cout << "Erreur de chargement de la police !" << std::endl;
    }
}

void Game::showOptionsMenu() {
    window.setView(window.getDefaultView());
    bool inOptionsMenu = true;

    volumeText.setFont(baseFont);
    volumeText.setString("Volume :");
    volumeText.setCharacterSize(80);
    volumeText.setFillColor(sf::Color::White);
    volumeText.setPosition((float)window.getSize().x / 2 - volumeText.getGlobalBounds().width / 2, (float)window.getSize().y / 3 - volumeText.getCharacterSize());

    backText.setFont(baseFont);
    backText.setString("Back");
    backText.setCharacterSize(50);
    backText.setPosition((window.getSize().x / 6 - backText.getGlobalBounds().width) / 2, menuText.getPosition().y / 1 - backText.getCharacterSize());
    backText.setFillColor(sf::Color::White);

    sf::RectangleShape volumeBar(sf::Vector2f(400, 10));
    volumeBar.setPosition((float)window.getSize().x / 2 - volumeBar.getSize().x / 2, (float)window.getSize().y / 2);
    volumeBar.setFillColor(sf::Color(100, 100, 100));

    sf::CircleShape volumeHandle(15);
    volumeHandle.setPosition(window.getSize().x / 2 - volumeHandle.getRadius() + (volume / 100.f) * volumeBar.getSize().x, window.getSize().y / 2 - volumeHandle.getRadius());
    volumeHandle.setFillColor(sf::Color::Red);

    bool isDragging = false;

    while (inOptionsMenu) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    inOptionsMenu = false;
                }
            }
            if (backText.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
                inOptionsMenu = false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (volumeHandle.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
                        isDragging = true;
                    }
                }
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    isDragging = false;
                }
            }
            if (event.type == sf::Event::MouseMoved) {
                if (isDragging) {
                    float newX = event.mouseMove.x - volumeHandle.getRadius();
                    if (newX < volumeBar.getPosition().x) {
                        newX = volumeBar.getPosition().x;
                    }
                    else if (newX > volumeBar.getPosition().x + volumeBar.getSize().x - volumeHandle.getRadius() * 2) {
                        newX = volumeBar.getPosition().x + volumeBar.getSize().x - volumeHandle.getRadius() * 2;
                    }
                    volumeHandle.setPosition(newX, volumeHandle.getPosition().y);

                    volume = (newX - volumeBar.getPosition().x) / volumeBar.getSize().x * 100.f;
                }
            }
        }

        volumeText.setString("Volume: " + std::to_string(static_cast<int>(volume)) + "%");

        volumeText.setPosition((float)window.getSize().x / 2 - volumeText.getGlobalBounds().width / 2, (float)window.getSize().y / 3 - volumeText.getCharacterSize());

        window.clear();
        window.draw(backText);
        window.draw(volumeText);
        window.draw(volumeBar);
        window.draw(volumeHandle);
        window.display();
    }
}

void Game::gameLoop() {
    while (window.isOpen()) {
        deltaTime = Clock.restart().asSeconds();
        /*std::thread updateThread(updateAll);
        updateThread.join();*/
        updateAll();
        pollEvent();
        try {
            drawAll();
        }
        catch (const std::exception& e) {
            std::cerr << "Exception attrapée : " << e.what() << std::endl;
        }
    }
}

void Game::pollEvent() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                if (playing) {
                    pause = true;
                    playing = false;
                }
            }
            if (event.key.code == sf::Keyboard::X) { //TEMPORAIRE
                /*playing = false;
                win = false;
                gameOver = false;
                showMenu();*/
                window.close();
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                if (gameOver || win) {
                    if (retryText.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
                        reset();
                        win = false;
                        gameOver = false;
                        pause = false;
                        playing = true;
                    }
                    else if (menuText.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
                        win = false;
                        gameOver = false;
                        pause = false;
                        showMenu();  // Retourner au menu principal
                    }
                }
                if (pause) {
                    if (reprendreText.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
                        playing = true;
                        pause = false;
                    }
                    else if (optionText.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
                        showOptionsMenu();
                    }
                    else if (menuText.getGlobalBounds().contains((float)event.mouseButton.x, (float)event.mouseButton.y)) {
                        win = false;
                        gameOver = false;
                        pause = false;
                        showMenu();  // Retourner au menu principal
                    }
                }
            }
        }
        if (event.type == sf::Event::MouseMoved) {
            if (gameOver || win || pause) {
                if (retryText.getGlobalBounds().contains((float)event.mouseMove.x, (float)event.mouseMove.y)) {
                    retryText.setFillColor(sf::Color::Yellow);
                }
                else {
                    retryText.setFillColor(sf::Color::White);
                }

                if (menuText.getGlobalBounds().contains((float)event.mouseMove.x, (float)event.mouseMove.y)) {
                    menuText.setFillColor(sf::Color::Yellow);
                }
                else {
                    menuText.setFillColor(sf::Color::White);
                }

                if (reprendreText.getGlobalBounds().contains((float)event.mouseMove.x, (float)event.mouseMove.y)) {
                    reprendreText.setFillColor(sf::Color::Yellow);
                }
                else {
                    reprendreText.setFillColor(sf::Color::White);
                }
                if (optionText.getGlobalBounds().contains((float)event.mouseMove.x, (float)event.mouseMove.y)) {
                    optionText.setFillColor(sf::Color::Yellow);
                }
                else {
                    optionText.setFillColor(sf::Color::White);
                }
            }
        }
    }
}

void Game::updateAll() {
    if (playing) {
        view.setCenter(player.sprite.getPosition().x, player.sprite.getPosition().y);
        //std::thread playerUpdateThread(player.update(deltaTime));
        player.update(deltaTime);
        player.handleInput(deltaTime, window, wallSprite, theMap.mapObjects, view, theMap.enemies, swordSlashSound);

        if (player.pnj) {
            dialogueTimer += deltaTime;
        }

        if (pnjPositionReached == false) {
            if (player.pnjMove) {
                for (auto& row : theMap.mapObjects) {
                    for (auto& obj : row) {
                        if (obj->type == "pnj") {
                            if (pnjMoveTime < pnjMoveDuration && pnjMoveDistance < maxDistance) {
                                obj->sprite.move(20.f * deltaTime, 0.f);
                                pnjMoveTime += deltaTime;
                                pnjMoveDistance += 5.f * deltaTime;
                            }
                            else {
                                pnjPositionReached = true;
                                pnjFinalPosition = obj->sprite.getPosition();
                            }
                        }
                    }
                }
            }
        }


        //COLLISIONS
        if (!theMap.enemies.empty()) {
            for (auto& enemy : theMap.enemies) {
                enemy->update(deltaTime);
                enemy->behavior(deltaTime, view, theMap.mapObjects, player);
                if (!player.moovingBomb.empty()) {
                    for (int j = 0; j < player.moovingBomb.size(); j++) {
                        if (enemy->sprite.getGlobalBounds().intersects(player.moovingBomb[j]->sprite.getGlobalBounds())) {
                            enemy->takeDamage(player.bombAtk);
                            player.moovingBomb.erase(player.moovingBomb.begin() + j);
                            explosionSound.play();
                        }
                    }
                }
            }
            for (int i = 0; i < theMap.enemies.size(); i++) {                     
                if (theMap.enemies[i]->state == false) {
                    if (theMap.enemies[i]->type == "boss") {
                        win = true;
                        playing = false;
                    }
                    theMap.enemies.erase(theMap.enemies.begin() + i);
                }
            }
        }
        if (!theMap.objects.empty()) {
            for (auto& obj : theMap.objects) {
                if (player.sprite.getGlobalBounds().intersects(obj->sprite.getGlobalBounds())) {
                    if (obj->type == "heart") {
                        if (player.hp < player.hpMax) {
                            if (obj->interact(player.sprite, theMap.objects, player.inventaire)) player.hp += obj->regen;
                        }
                    }
                    else if (obj->type == "bomb") {
                        if (player.bombCount < player.bombCountMax) {
                            obj->interact(player.sprite, theMap.objects, player.inventaire);
                        }
                    }
                    else {
                        obj->interact(player.sprite, theMap.objects, player.inventaire);
                    }
                }
            }
            for (int i = 0; i < theMap.objects.size(); i++) {
                if (theMap.objects[i]->state == false) {
                    theMap.objects.erase(theMap.objects.begin() + i);
                }
            }
        }
        for (auto& objz : theMap.mapObjects) {
            for (auto& obj : objz) {
                if (obj->type == "pnj") {
                    dialogue.setPosition(obj->sprite.getPosition().x + obj->sprite.getLocalBounds().width * obj->sprite.getScale().x,
                        obj->sprite.getPosition().y - dialogue.getCharacterSize() * 3);
                    if (pnjPositionReached) {
                        obj->sprite.setPosition(pnjFinalPosition);
                    }
                }
                if (obj->type == "wall") {
                    if (!player.moovingBomb.empty()) {
                        for (int j = 0; j < player.moovingBomb.size(); j++) {
                            if (obj->sprite.getGlobalBounds().intersects(player.moovingBomb[j]->sprite.getGlobalBounds())) {
                                player.moovingBomb.erase(player.moovingBomb.begin() + j);
                                explosionSound.play();
                                if (obj->breakableWall) {
                                    obj->state = false;
                                    theMap.wallDestroyed = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        if (theMap.wallDestroyed) {
            for (int i = 0; i < theMap.mapObjects.size(); i++) {
                for (int j = 0; j < theMap.mapObjects[i].size(); j++) {
                    if (theMap.mapObjects[i][j]->state == false) {
                        theMap.mapObjects[i].erase(theMap.mapObjects[i].begin() + j);
                    }
                }
            }
            theMap.wallDestroyed = false;
        }
        /*WIN CONDITION*/
        /*if (theMap.enemies[i]->type == "boss") {
            win = true;
            playing = false;
        }*/
        //LOSE CONDITION
        if (player.hp <= 0) {
            playing = false;
            win = false;
            gameOver = true;
        }
        // UPDATE POSITION INCONES (clés, potions etc)
        keyIcone.setPosition(player.sprite.getPosition().x + (player.sprite.getGlobalBounds().width * player.sprite.getScale().x)/2 - view.getSize().x / 2
        + keyIcone.getGlobalBounds().width * keyIcone.getScale().x,
        player.sprite.getPosition().y + (player.sprite.getGlobalBounds().height * player.sprite.getScale().y) / 2 - view.getSize().y / 2
        + keyIcone.getGlobalBounds().height * keyIcone.getScale().y);

        bombIcone.setPosition(keyIcone.getPosition().x + /*(float)*/view.getSize().x - (bombIcone.getLocalBounds().width * bombIcone.getScale().x)*2.2f, keyIcone.getPosition().y);
        heartIcone.setPosition(keyIcone.getPosition().x, keyIcone.getPosition().y + (float)view.getSize().y - heartIcone.getLocalBounds().height * bombIcone.getScale().y);
        //TIMER UPDATE
        
    }
}

void Game::drawAll() {
    window.clear();
    if (playing) {
        window.setView(view);

        if (!theMap.mapObjects.empty()) {
            for (auto& objz : theMap.mapObjects) {
                for (auto& obj : objz) {
                    if (obj->type == "wall") { 
                        if (obj->breakableWall) obj->sprite.setTexture(breakableWallTexture);
                        else { obj->sprite.setTexture(wallTexture); }
                    }
                    else {
                        if (obj->breakableWall) throw std::runtime_error("Erreur : Objet different de mur cassable. Veuillez l'initialiser en breakable = false.");
                        if (obj->type == "wallDebris") obj->sprite.setTexture(wallDebrisTexture);
                        else if (obj->type == "floor") obj->sprite.setTexture(floorTexture);
                        else if (obj->type == "pnj")
                        {
                            obj->sprite.setTexture(pnjTexture);
                            pnjSprite = obj->sprite;
                        }
                        else if (obj->type == "checkpoint") {
                            if (obj->sprite.getPosition() == player.checkpoint) {
                                obj->sprite.setTexture(checkpointOnTexture);
                            }
                            else {
                                obj->sprite.setTexture(checkpointTexture);
                            }
                        }
                        else if (obj->type == "lock") obj->sprite.setTexture(lockTexture);
                    }
                    window.draw(obj->sprite);
                }
            }
        }
        window.draw(pnjSprite);
        player.sprite.setTexture(playerTexture);
        player.draw(window, heartIcone, bombIcone, bombTexture, patrollingTexture);
        if (player.key1) window.draw(keyIcone);
        if (!theMap.enemies.empty()) {
            for (auto& enemy : theMap.enemies) {
                if (enemy->type == "chaser") enemy->sprite.setTexture(chaserTexture);
                else if (enemy->type == "patrolling") enemy->sprite.setTexture(patrollingTexture);
                if (enemy->type != "boss") enemy->draw(window, keyIcone, bombIcone, chaserTexture, patrollingTexture);
                else { enemy->draw(window, keyIcone, bombIcone, bossTexture, projectileTexture); }
            }
        }
        if (!theMap.objects.empty()) {
            for (auto& obj : theMap.objects) {
                if (obj->type == "bomb") obj->sprite.setTexture(bombTexture);
                else if (obj->type == "key") obj->sprite.setTexture(keyTexture);
                else if (obj->type == "pnj") obj->sprite.setTexture(pnjTexture);
                else if (obj->type == "heart") obj->sprite.setTexture(heartTexture);
                window.draw(obj->sprite);
            }
        }
        if (dialogueTimer > 0)
        {
            if (dialogueTimer < dialogueLimit)
            {
                
                window.draw(dialogue);
            }
            else {
                player.pnjMove = true;
            }
        }
    }
    if (win) {
        window.setView(window.getDefaultView());
        window.draw(winText);
        window.draw(retryText);
        window.draw(menuText);
    }
    if (gameOver) {
        window.setView(window.getDefaultView());
        window.draw(gameOverText);
        window.draw(retryText);
        window.draw(menuText);
    }
    if (pause) {
        window.setView(window.getDefaultView());
        window.draw(reprendreText);
        window.draw(optionText);
        window.draw(menuText);
    }
    window.display();
}

void Game::loadTextures() {
    //theMap.loadMap();
    playerTexture.loadFromFile("assets/player.png");
    chaserTexture.loadFromFile("assets/chaser.png");
    patrollingTexture.loadFromFile("assets/patrolling.png");
    bombTexture.loadFromFile("assets/bomb.png");
    keyTexture.loadFromFile("assets/key.png");
    wallTexture.loadFromFile("assets/wall.png");
    breakableWallTexture.loadFromFile("assets/breakableWall.png");
    wallDebrisTexture.loadFromFile("assets/wallDebris.png");
    floorTexture.loadFromFile("assets/floor.png");
    lockTexture.loadFromFile("assets/lock.png");
    pnjTexture.loadFromFile("assets/pnj.png");
    checkpointTexture.loadFromFile("assets/checkpoint.png");
    checkpointOnTexture.loadFromFile("assets/checkpointOn.png");
    explosionTexture.loadFromFile("assets/explosion.png");
    bossTexture.loadFromFile("assets/boss.png");
    projectileTexture.loadFromFile("assets/projectile.png");
    heartTexture.loadFromFile("assets/heart.png");

    baseFont.loadFromFile("assets/Arial.ttf");

    winText.setFont(baseFont);
    winText.setString("WIN");
    winText.setCharacterSize(100);
    winText.setPosition(((float)window.getSize().x - winText.getGlobalBounds().width) / 2,
        ((float)window.getSize().y - winText.getCharacterSize()) / 3);
    winText.setFillColor(sf::Color::Yellow);

    gameOverText.setFont(baseFont);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(100);
    gameOverText.setPosition(((float)window.getSize().x - gameOverText.getGlobalBounds().width) / 2,
        ((float)window.getSize().y - gameOverText.getCharacterSize()) / 3);
    gameOverText.setFillColor(sf::Color::Red);

    retryText.setFont(baseFont);
    retryText.setString("RETRY");
    retryText.setCharacterSize(50);
    retryText.setPosition(((float)window.getSize().x - retryText.getGlobalBounds().width) / 2,
        gameOverText.getPosition().y + gameOverText.getCharacterSize() + (float)window.getSize().y * 0.1f);
    retryText.setFillColor(sf::Color::White);

    menuText.setFont(baseFont);
    menuText.setString("MENU");
    menuText.setCharacterSize(50);
    menuText.setPosition(
        (window.getSize().x - menuText.getGlobalBounds().width) / 2,
        retryText.getPosition().y + retryText.getCharacterSize() + 20
    );
    menuText.setFillColor(sf::Color::White);

    reprendreText.setFont(baseFont);
    reprendreText.setString("REPRENDRE");
    reprendreText.setCharacterSize(75);
    reprendreText.setPosition(((float)window.getSize().x - reprendreText.getGlobalBounds().width) / 2.f, ((float)window.getSize().y - reprendreText.getCharacterSize()) / 2.5f);
    reprendreText.setFillColor(sf::Color::White);

    optionText.setFont(baseFont);
    optionText.setString("OPTIONS");
    optionText.setCharacterSize(50);
    optionText.setPosition(((float)window.getSize().x - optionText.getGlobalBounds().width) / 2.f, menuText.getPosition().y - optionText.getCharacterSize() *1.5f);
    optionText.setFillColor(sf::Color::White);

    player.bombText.setFont(baseFont);
    player.bombText.setCharacterSize(25);
    player.bombText.setFillColor(sf::Color::White);
    player.hpText.setFont(baseFont);
    player.hpText.setCharacterSize(25);
    player.hpText.setFillColor(sf::Color::Red);

    keyIcone.setTexture(keyTexture);
    keyIcone.setScale(0.075f, 0.075f);
    bombIcone.setTexture(bombTexture);
    bombIcone.setScale(0.075f, 0.075f);
    heartIcone.setTexture(heartTexture);
    heartIcone.setScale(0.075f, 0.075f);
    
    wallSprite.setTexture(wallTexture);
    floorSprite.setTexture(floorTexture);
    lockSprite.setTexture(lockTexture);

    dialogue.setFont(baseFont);
    dialogue.setString("Bonjour, aventurier ! \n Faites attention aux dangers \n qui vous attendent.");
    dialogue.setCharacterSize(15);
    dialogue.setFillColor(sf::Color::White);
    dialogue.setPosition(view.getCenter().x - 200, view.getCenter().y + 100);

    swordSlashBuffer.loadFromFile("assets/sword sound.wav");
    explosionBuffer.loadFromFile("assets/explosion sound.wav");

    swordSlashSound.setBuffer(swordSlashBuffer);
    swordSlashSound.setVolume(10);
    explosionSound.setBuffer(explosionBuffer);
    explosionSound.setVolume(10);
}

void Game::reset() {

    deltaTime = Clock.restart().asSeconds();
    theMap.enemies.clear();
    theMap.objects.clear();
    theMap.mapObjects.clear();
    player.checkpointResetPlayer();
    theMap.loadMap(player);

}

void Game::run() {
    musicSound.openFromFile("assets/main music.wav");
    musicSound.setVolume(10);
    musicSound.play();
    musicSound.setLoop(true);
    showMenu();
    loadTextures();
    gameLoop();
}