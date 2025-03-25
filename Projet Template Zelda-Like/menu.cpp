#include "Menu.h"

Menu::Menu(float width, float height) {
    if (!font.loadFromFile("assets/arial.ttf")) {
        std::cerr << "Erreur: Impossible de charger la police !" << std::endl;
    }

    if (!backgroundTexture.loadFromFile("assets/menu.png")) {
        std::cerr << "Erreur: Impossible de charger l'image de fond !" << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setScale(width / backgroundSprite.getLocalBounds().width, height / backgroundSprite.getLocalBounds().height);

    std::vector<std::string> options = { "Jouer", "Options", "Quitter" };
    selectedIndex = 0;

    float textSize = 70;
    float spacing = 120;

    for (size_t i = 0; i < options.size(); i++) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setFillColor(i == 0 ? sf::Color::Red : sf::Color::White);
        text.setCharacterSize(textSize);

        float textWidth = text.getLocalBounds().width;
        float xPos = (width - textWidth) / 2;
        float yPos = (height / 2 - (options.size() / 2.0) * spacing) + i * spacing;

        text.setPosition(sf::Vector2f(xPos, yPos));
        menuOptions.push_back(text);
    }
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    for (auto& option : menuOptions) {
        window.draw(option);
    }
}

void Menu::moveUp() {
    if (selectedIndex > 0) {
        menuOptions[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex--;
        menuOptions[selectedIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedIndex < menuOptions.size() - 1) {
        menuOptions[selectedIndex].setFillColor(sf::Color::White);
        selectedIndex++;
        menuOptions[selectedIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedIndex() const {
    return selectedIndex;
}

void Menu::handleMouseHover(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    for (size_t i = 0; i < menuOptions.size(); i++) {
        if (menuOptions[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            menuOptions[selectedIndex].setFillColor(sf::Color::White);
            selectedIndex = i;
            menuOptions[i].setFillColor(sf::Color::Red);
        }
    }
}

int Menu::handleMouseClick(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);

    for (size_t i = 0; i < menuOptions.size(); i++) {
        if (menuOptions[i].getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y))) {
            return i;
        }
    }
    return -1;
}