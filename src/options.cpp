#include "options.h"

Options::Options() : selected_options_index(0)
{
    /*if (!open_sans.loadFromFile("font\\OpenSans-Regular.ttf"))
    {
        std::cout << "No font found\n";
    }*/

    std::string options[] = { "Speed", "Window", "Back" };

    for (int i = 0; i < NUMBER_OF_OPTIONS; i++)
    {
        options_options[i].setFont(open_sans);
        options_options[i].setFillColor(sf::Color::White);
        options_options[i].setCharacterSize(70);
        options_options[i].setStyle(sf::Text::Bold);
        options_options[i].setPosition(50, 100 * i + 150);
        options_options[i].setString(options[i]);
    }
    options_options[NUMBER_OF_OPTIONS - 1].setFillColor(sf::Color::Red);
    options_options[0].setFillColor(sf::Color::Green);
    selected_option = 0;
}

Options::~Options()
{
}

void Options::move_up()
{
    if (selected_options_index - 1 >= 0)
    {
        if (selected_options_index == NUMBER_OF_OPTIONS - 1)
            options_options[selected_options_index].setFillColor(sf::Color::Red);
        else
            options_options[selected_options_index].setFillColor(sf::Color::White);
        selected_options_index--;
        options_options[selected_options_index].setFillColor(sf::Color::Green);
        selected_option = selected_options_index;
    }
}

void Options::move_down()
{
    if (selected_options_index + 1 < NUMBER_OF_OPTIONS)
    {
        options_options[selected_options_index].setFillColor(sf::Color::White);
        selected_options_index++;
        options_options[selected_options_index].setFillColor(sf::Color::Green);
        selected_option = selected_options_index;
    }
}

void Options::draw(sf::RenderWindow& window)
{
    for (int i = 0; i < NUMBER_OF_OPTIONS; i++)
        window.draw(options_options[i]);
}

void Options::change_option(int selected)
{
    switch (selected)
    {
    case 0:
        std::cout << "Speed" << "\n";
        break;
    case 1:
        std::cout << "Window" << "\n";
        break;
    case 2:

        break;
    }
}

