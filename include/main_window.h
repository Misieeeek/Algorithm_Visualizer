#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <memory>
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <array>
#include <atomic>
#include <charconv>
#include <filesystem>
#include <functional>
#include <iostream>
#include <map>
#include <mutex>
#include <random>
#include <span>
#include <sstream>
#include <string>
#include <utility>
#include <variant>
#include <vector>

class Screen {
 public:
  Screen() : m_opend(false), m_main_active(true) { set_open_sans(); }
  virtual ~Screen() = default;
  virtual void draw(sf::RenderWindow& window) = 0;
  virtual int pressed() = 0;

  virtual void change_option(int selected);
  virtual void drop_down(int option);
  virtual void typed_on(sf::Event input);
  virtual void move_left();
  virtual void move_right();
  virtual void move_up();
  virtual void move_down();

  virtual void set_open_sans();
  virtual void set_sf_text_style(std::span<sf::Text> arr_list,
                                 std::span<std::string> arr_text, int char_size,
                                 int x_offset, int y_offset, bool x_multiplier,
                                 bool y_multiplier, int x_text_multiplier = 0,
                                 int y_text_multiplier = 0);

  virtual void set_sf_text_style(std::span<sf::Text> arr_list,
                                 std::span<std::string> arr_text, int char_size,
                                 int x_offset, int y_offset, bool x_multiplier,
                                 bool y_multiplier, int x_text_multiplier,
                                 int y_text_multiplier, int begin_from,
                                 int end_at);

 protected:
  bool m_opend;
  bool m_main_active;
  bool m_dropped;
  sf::Font m_open_sans;
};

class MainWindow {
 public:
  MainWindow();
  ~MainWindow();
  void is_running(sf::RenderWindow& window);
};

#endif
