#ifndef MAINMENU_H
#define MAINMENU_H
#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "main_window.h"

#define NUMBER_OF_ITEMS 4

class MainMenu : public Screen
{
private:
	int selected_item_index;
	sf::Text main_menu_options[NUMBER_OF_ITEMS];
	sf::Font open_sans;
	int selected;
public:
	MainMenu();
	~MainMenu();

	void draw(sf::RenderWindow& window) override;
	void move_up() override;
	void move_down() override;
	int pressed() override { return selected; }
	void change_option(int selected) override;
};

#endif
