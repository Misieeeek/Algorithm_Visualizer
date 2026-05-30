module;

#include <SFML/Graphics/Font.hpp>

module Alviz.ResourceManager;

import std;

namespace alviz {
void ResourceManager::loadFont(sf::Font& fnt, std::string& filename) {
  std::filesystem::current_path(std::filesystem::path(__FILE__)
                                    .parent_path()
                                    .parent_path()
                                    .parent_path());

  if (!fnt.openFromFile(std::format("assets/fonts/{}", filename))) {
    std::cerr << "Failed to load font" << std::endl;
  }
}
}  // namespace alviz
