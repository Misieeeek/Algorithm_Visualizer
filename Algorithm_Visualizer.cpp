#include "main_menu.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Algorithm Visualizer", sf::Style::Close | sf::Style::Resize);
    MainMenu mainMenu;

    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            switch (evnt.type)
            {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (evnt.key.code)
                {
                case sf::Keyboard::Up:
                    mainMenu.MoveUp();
                    break;
                case sf::Keyboard::Down:
                    mainMenu.MoveDown();
                    break;
                case sf::Keyboard::Enter:
                    int selected = mainMenu.pressed();
                    if (selected == NUMBER_OF_ITEMS-1)
                        window.close();
                    break;
                }
            default:
                break;
            }
        }

        window.clear();
        mainMenu.draw(window);
        window.display();
    }
}
