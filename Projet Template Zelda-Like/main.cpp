#include "game.h"

int main() {
    srand(time(NULL));

    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    Game game(modes); 
    game.run();

    return 0;
}