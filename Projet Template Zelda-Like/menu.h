#include "includes.h"

class Menu {
public:
    Menu(float width, float height);
    ~Menu();

    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    void handleMouseHover(sf::RenderWindow& window);
    int handleMouseClick(sf::RenderWindow& window);
    int getSelectedIndex() const;

private:
    int selectedIndex;
    sf::Font font;
    std::vector<sf::Text> menuOptions;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
};