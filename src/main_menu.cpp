#include "main_menu.h"
#include <filesystem>

MainMenu::MainMenu() : selected_item_index(0) {

  std::filesystem::current_path(
      std::filesystem::path(__FILE__).parent_path().parent_path());

  if (!open_sans.loadFromFile("assets/fonts/OpenSans-Regular.ttf")) {
    std::cerr << "Failed to load font" << std::endl;
  }

  std::string options[] = {"Visualize", "Options", "Exit"};

  for (int i = 0; i < NUMBER_OF_ITEMS; i++) {
    main_menu_options[i].setFont(open_sans);
    main_menu_options[i].setFillColor(sf::Color::White);
    main_menu_options[i].setCharacterSize(70);
    main_menu_options[i].setStyle(sf::Text::Bold);
    main_menu_options[i].setPosition(50, 100 * i + 150);
    main_menu_options[i].setString(options[i]);
  }
  main_menu_options[NUMBER_OF_ITEMS - 1].setFillColor(sf::Color::Red);
  main_menu_options[0].setFillColor(sf::Color::Green);
  selected = 0;
}

MainMenu::~MainMenu() {}

void MainMenu::move_up() {
  if (selected_item_index - 1 >= 0) {
    if (selected_item_index == NUMBER_OF_ITEMS - 1)
      main_menu_options[selected_item_index].setFillColor(sf::Color::Red);
    else
      main_menu_options[selected_item_index].setFillColor(sf::Color::White);
    selected_item_index--;
    main_menu_options[selected_item_index].setFillColor(sf::Color::Green);
    selected = selected_item_index;
  }
}

void MainMenu::move_down() {
  if (selected_item_index + 1 < NUMBER_OF_ITEMS) {
    main_menu_options[selected_item_index].setFillColor(sf::Color::White);
    selected_item_index++;
    main_menu_options[selected_item_index].setFillColor(sf::Color::Green);
    selected = selected_item_index;
  }
}

void MainMenu::draw(sf::RenderWindow &window) {
  for (int i = 0; i < NUMBER_OF_ITEMS; i++)
    window.draw(main_menu_options[i]);
}

void MainMenu::change_option(int selected) {}

void MainMenu::drop_down(int option) {}

void MainMenu::handle_input() {}
