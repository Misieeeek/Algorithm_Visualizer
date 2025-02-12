#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#pragma once

#include <SFML/Graphics.hpp>

class Screen {
public:
  virtual void draw(sf::RenderWindow &window) = 0;
  virtual void move_up() = 0;
  virtual void move_down() = 0;
  virtual int pressed() = 0;
  virtual void change_option(int selected) = 0;
  virtual ~Screen() = default;
};

class MainWindow {
public:
  MainWindow();
  ~MainWindow();
  enum class State { MAINMENU, VISUALIZESCREEN, OPTIONSSCREEN, ABOUTSCREEN };
  void is_running(sf::RenderWindow &window);
  void original_current_state() { current_state = State::MAINMENU; }

private:
  State current_state;
};

#endif
