#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <SFML/Window/Event.hpp>
#pragma once

#include <SFML/Graphics.hpp>

class Screen {
protected:
  bool opend;
  bool main_active;
  bool dropped;

public:
  Screen() : opend(false), main_active(true) {};
  virtual void draw(sf::RenderWindow &window) = 0;
  virtual void move_up() = 0;
  virtual void move_down() = 0;
  virtual void move_left() = 0;
  virtual void move_right() = 0;
  virtual int pressed() = 0;
  virtual void change_option(int selected) = 0;
  virtual ~Screen() = default;

  virtual void drop_down(int option) = 0;
  virtual void typed_on(sf::Event input) = 0;
};

class MainWindow {
public:
  MainWindow();
  ~MainWindow();
  void is_running(sf::RenderWindow &window);
};

#endif
