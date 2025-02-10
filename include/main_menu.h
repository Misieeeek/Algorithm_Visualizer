#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#define NUMBER_OF_ITEMS 4

class MainMenu
{
private:
	int selected_item_index;
	sf::Text main_menu_options[NUMBER_OF_ITEMS];
	sf::Font open_sans;
	int selected;
public:
	MainMenu();
	~MainMenu();

	void draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();
	void setSelected(int n) { selected = n; }
	int pressed() { return selected; }
};

#endif
