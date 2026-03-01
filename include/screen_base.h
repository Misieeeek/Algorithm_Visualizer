#ifndef SCREEN_BASE_H
#define SCREEN_BASE_H
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include "interfaces/IDrawable.h"
#include "interfaces/IInteractable.h"
#include "interfaces/INavigable.h"

class Screen_Base : public IDrawable, public IInteractable, public INavigable {
 public:
  virtual ~Screen_Base() = default;
  void activate();
  void deactivate();
  bool is_active() const;
  int get_selected_index() const override;
  void draw(sf::RenderWindow& window) override = 0;
  void handle_key_press(sf::Keyboard::Key key) override = 0;
  void handle_text_input(sf::Event::TextEvent& text) override = 0;
  void handle_mouse_click(const sf::Vector2i& position) override = 0;

  void move_up() override = 0;
  void move_down() override = 0;
  void move_left() override = 0;
  void move_right() override = 0;

 protected:
  const sf::Font& get_font() const;
  int get_selected_index_internal() const;
  void set_selected_index(int index);
  bool is_active_internal() const;
  virtual void initialize_components() = 0;
  virtual void update_selection() = 0;
  virtual void handle_selection() = 0;
  virtual void on_activate();
  virtual void on_deactiveate();

 private:
  sf::Font m_font;
  bool m_is_active;
  int m_selectedIndex = 0;

  bool load_font();
};
#endif
