#include "main_window.h"
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstddef>
#include <exception>
#include "main_menu.h"
#include "options.h"
#include "visualizer.h"

MainWindow::MainWindow() {
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Algorithm Visualizer",
                          sf::Style::Close | sf::Style::Resize);
  is_running(window);
}

MainWindow::~MainWindow() {}

void MainWindow::is_running(sf::RenderWindow& window) {
  MainMenu main_menu;
  Screen* current_screen = &main_menu;
  Options options(&current_screen, &main_menu);
  Visualizer visualize(&current_screen, &main_menu, &window);

  int selected;

  while (window.isOpen()) {
    sf::Event evnt;
    while (window.pollEvent(evnt)) {
      switch (evnt.type) {
        case sf::Event::Closed:
          window.close();
          break;
        case sf::Event::TextEntered:
          current_screen->typed_on(evnt);
        case sf::Event::KeyPressed:
          switch (evnt.key.code) {
            case sf::Keyboard::Up:
              current_screen->move_up();
              break;
            case sf::Keyboard::Down:
              current_screen->move_down();
              break;
            case sf::Keyboard::Left:
              current_screen->move_left();
              break;
            case sf::Keyboard::Right:
              current_screen->move_right();
              break;
            case sf::Keyboard::Enter:
              selected = current_screen->pressed();
              if (current_screen == &main_menu) {
                switch (selected) {
                  case 0:
                    current_screen = &visualize;
                    break;
                  case 1:
                    current_screen = &options;
                    break;
                  case 2:
                    window.close();
                    break;
                }
              }
              current_screen->change_option(selected);
              break;
          }
          break;
      }
    }
    window.clear();
    current_screen->draw(window);
    window.display();
  }
}

void Screen::change_option(int selected) {}
void Screen::drop_down(int option) {}
void Screen::typed_on(sf::Event input) {}
void Screen::move_left() {}
void Screen::move_right() {}
void Screen::move_up() {}
void Screen::move_down() {}

void Screen::set_open_sans() {
  std::filesystem::current_path(
      std::filesystem::path(__FILE__).parent_path().parent_path());

  if (!m_open_sans.loadFromFile("assets/fonts/OpenSans-Regular.ttf")) {
    std::cerr << "Failed to load font" << std::endl;
  }
}

//IF STATEMENT CLOUD BE OUTSIDE OF LOOP, BUT IT THEN LACKS READABILITY
void Screen::set_sf_text_style(std::span<sf::Text> arr_list,
                               std::span<std::string> arr_text, int char_size,
                               int x_offset, int y_offset, bool x_multiplier,
                               bool y_multiplier, int x_text_multiplier,
                               int y_text_multiplier) {

  int count = 0;
  for (auto& x : arr_list) {
    x.setFont(m_open_sans);
    x.setFillColor(sf::Color::White);
    x.setCharacterSize(char_size);
    x.setStyle(sf::Text::Bold);
    if (x_multiplier && y_multiplier)
      x.setPosition(x_text_multiplier * count + x_offset,
                    y_text_multiplier * count + y_offset);
    else if (x_multiplier && !y_multiplier)
      x.setPosition(x_text_multiplier * count + x_offset, y_offset);
    else if (!x_multiplier && y_multiplier)
      x.setPosition(x_offset, y_text_multiplier * count + y_offset);
    else
      x.setPosition(x_offset, y_offset);
    x.setString(arr_text[count]);
    count++;
  }
}

void Screen::set_sf_text_style(std::span<sf::Text> arr_list,
                               std::span<std::string> arr_text, int char_size,
                               int x_offset, int y_offset, bool x_multiplier,
                               bool y_multiplier, int x_text_multiplier,
                               int y_text_multiplier, int begin_from,
                               int end_at) {
  int count = 0;
  for (int i = begin_from; i < end_at; i++) {
    arr_list[i].setFont(m_open_sans);
    arr_list[i].setFillColor(sf::Color::White);
    arr_list[i].setCharacterSize(char_size);
    arr_list[i].setStyle(sf::Text::Bold);
    if (x_multiplier && y_multiplier)
      arr_list[i].setPosition(x_text_multiplier * count + x_offset,
                              y_text_multiplier * count + y_offset);
    else if (x_multiplier && !y_multiplier)
      arr_list[i].setPosition(x_text_multiplier * count + x_offset, y_offset);
    else if (!x_multiplier && y_multiplier)
      arr_list[i].setPosition(x_offset, y_text_multiplier * count + y_offset);
    else
      arr_list[i].setPosition(x_offset, y_offset);
    arr_list[i].setString(arr_text[i]);
    count++;
  }
}
