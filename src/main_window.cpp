#include "main_window.h"
#include "main_menu.h"
#include "options.h"

MainWindow::MainWindow() {
  current_state = State::MAINMENU;
  sf::RenderWindow window(sf::VideoMode(1280, 720), "Algorithm Visualizer",
                          sf::Style::Close | sf::Style::Resize);
  is_running(window);
}

MainWindow::~MainWindow() {}

void MainWindow::is_running(sf::RenderWindow &window) {
  MainMenu mainMenu;
  Options options;
  // Visualizer visualize;
  // Aboutscreen about;

  Screen *current_screen = &mainMenu;

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
          if (current_state == State::MAINMENU) {
            switch (selected) {
            case 0:
              current_state = State::VISUALIZESCREEN;
              // current_screen = &visualize;
              break;
            case 1:
              current_state = State::OPTIONSSCREEN;
              current_screen = &options;
              break;
            case 2:
              current_state = State::ABOUTSCREEN;
              // current_screen = &about;
              break;
            case 3:
              window.close();
              break;
            }
          } else
            current_screen->change_option(selected);
          break;
        }
        break;
      }
    }
    window.clear();
    current_screen->draw(window);
    /*switch (current_state)
    {
    case State::MAINMENU:
        current_screen->draw(window);
        break;
    case State::VISUALIZESCREEN:
        current_screen->draw(window);
        break;
    case State::OPTIONSSCREEN:
        current_screen->draw(window);
        break;
    case State::ABOUTSCREEN:
        //
        break;
    case State::EXIT:
        window.close();
        break;
    }*/
    window.display();
  }
}
