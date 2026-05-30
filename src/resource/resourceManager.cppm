module;

#include <SFML/Graphics/Font.hpp>

export module Alviz.ResourceManager;

import std;

export namespace alviz {
class ResourceManager {
 public:
  void loadFont(sf::Font& fnt, std::string& filename);
};
}  // namespace alviz
