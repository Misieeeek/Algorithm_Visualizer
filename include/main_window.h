#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <SFML/Graphics.hpp>

class Screen {
public:
  enum class State { MAINMENU, VISUALIZESCREEN, OPTIONSSCREEN };

protected:
  State current_state;

public:
  Screen() : current_state(State::MAINMENU) {};
  virtual void draw(sf::RenderWindow &window) = 0;
  virtual void move_up() = 0;
  virtual void move_down() = 0;
  virtual int pressed() = 0;
  virtual void change_option(int selected) = 0;
  virtual ~Screen() = default;
  virtual void set_state(State new_state) { current_state = new_state; }
  virtual State get_state() const { return current_state; }

  virtual void drop_down(int option) = 0;
};

class MainWindow {
public:
  MainWindow();
  ~MainWindow();
  void is_running(sf::RenderWindow &window);
};

#endif
