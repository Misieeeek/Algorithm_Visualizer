#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <SFML/Window/Event.hpp>
#pragma once

#include <SFML/Graphics.hpp>

class Screen {
 public:
  Screen() : m_opend(false), m_main_active(true) {};
  virtual ~Screen() = default;
  virtual void draw(sf::RenderWindow& window) = 0;
  virtual void move_up() = 0;
  virtual void move_down() = 0;
  virtual int pressed() = 0;

  virtual void change_option(int selected);
  virtual void drop_down(int option);
  virtual void typed_on(sf::Event input);
  virtual void move_left();
  virtual void move_right();

 protected:
  bool m_opend;
  bool m_main_active;
  bool m_dropped;
};

class MainWindow {
 public:
  MainWindow();
  ~MainWindow();
  void is_running(sf::RenderWindow& window);
};

#endif
