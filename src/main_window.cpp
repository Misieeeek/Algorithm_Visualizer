#include "main_window.h"
#include "main_menu.h"
#include "options.h"
#include "visualizer.h"
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>

MainWindow::MainWindow() {
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Algorithm Visualizer",
                          sf::Style::Close | sf::Style::Resize);
  is_running(window);
}

MainWindow::~MainWindow() {}

void MainWindow::is_running(sf::RenderWindow &window) {
  MainMenu main_menu;
  Screen *current_screen = &main_menu;
  Options options(&current_screen, &main_menu);
  Visualizer visualize(&current_screen, &main_menu);

  while (window.isOpen()) {
    sf::Event evnt;
    while (window.pollEvent(evnt)) {
      switch (evnt.type) {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyPressed:
        switch (evnt.key.code) {
        case sf::Keyboard::Up:
          current_screen->move_up();
          break;
        case sf::Keyboard::Down:
          current_screen->move_down();
          break;
        case sf::Keyboard::Enter:
          int selected = current_screen->pressed();
          if (current_screen->getState() == Screen::State::MAINMENU) {
            switch (selected) {
            case 0:
              current_screen->setState(Screen::State::VISUALIZESCREEN);
              current_screen = &visualize;
              break;
            case 1:
              current_screen->setState(Screen::State::OPTIONSSCREEN);
              current_screen = &options;
              break;
              // case 2:
              //  current_state = State::ABOUTSCREEN;
              //   current_screen = &about;
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
