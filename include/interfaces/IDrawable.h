#ifdef IDRAWABLE_H
#define IDRAWABLE_H

#pragma once

#include <SFML/Graphics.hpp>

class IDrawable {
 public:
  virtual ~IDrawable() = default;
  virtual void draw(sf::RenderWindow& window) = 0;
}

#endif
