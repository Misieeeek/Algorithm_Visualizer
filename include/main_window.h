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
  virtual void setState(State newState) { current_state = newState; }
  virtual State getState() const { return current_state; }
};

class MainWindow {
public:
  MainWindow();
  ~MainWindow();
  void is_running(sf::RenderWindow &window);
};

#endif
