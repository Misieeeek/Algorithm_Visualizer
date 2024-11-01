#include "Main_menu.h"

MainMenu::MainMenu() : selected_item_index(0)
{
    if (!open_sans.loadFromFile("font\\OpenSans-Regular.ttf"))
    {
        std::cout << "No font found\n";
    }

    std::string options[] = { "Visualize", "Options", "About", "Exit" };

    for (int i = 0; i < NUMBER_OF_ITEMS; i++)
    {
        main_menu_options[i].setFont(open_sans);
        main_menu_options[i].setFillColor(sf::Color::White);
        main_menu_options[i].setCharacterSize(70);
        main_menu_options[i].setStyle(sf::Text::Bold);
        main_menu_options[i].setPosition(50, 100 * i + 150);
        main_menu_options[i].setString(options[i]);
    }
    main_menu_options[NUMBER_OF_ITEMS-1].setFillColor(sf::Color::Red);
    main_menu_options[0].setFillColor(sf::Color::Green);
    setSelected(0);
}

MainMenu::~MainMenu()
{
}

void MainMenu::MoveUp()
{
    if (selected_item_index - 1 >= 0)
    {
        if (selected_item_index == NUMBER_OF_ITEMS - 1)
            main_menu_options[selected_item_index].setFillColor(sf::Color::Red);
        else
            main_menu_options[selected_item_index].setFillColor(sf::Color::White);
        selected_item_index--;
        main_menu_options[selected_item_index].setFillColor(sf::Color::Green);
        setSelected(selected_item_index);
    }
}

void MainMenu::MoveDown()
{
    if (selected_item_index + 1 < NUMBER_OF_ITEMS)
    {
        main_menu_options[selected_item_index].setFillColor(sf::Color::White);
        selected_item_index++;
        main_menu_options[selected_item_index].setFillColor(sf::Color::Green);
        setSelected(selected_item_index);
    }
}

void MainMenu::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < NUMBER_OF_ITEMS; i++)
        window.draw(main_menu_options[i]);
}