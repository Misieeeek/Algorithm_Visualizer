module;

#include <SFML/System/Vector2.hpp>
#include <cstdint>

export module Alviz.Math;

export namespace alviz {
namespace math {
using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using f32 = float;
using f64 = double;
}  // namespace math

struct Vec2f {
  math::f32 x, y;
};

struct Vec2i {
  math::i32 x, y;
  Vec2i fromSFML(const sf::Vector2i& pos) { return Vec2i{pos.x, pos.y}; }
};

struct FloatRect {
  math::f32 x{0.0F}, y{0.0F};
  math::f32 width{0.0F}, height{0.0F};

  bool contains(math::f32 pos_x, math::f32 pos_y) const {
    return pos_x >= x && pos_x <= x + width && pos_y >= y &&
           pos_y <= y + height;
  };
};

enum class Key { Up, Down, Left, Right, Enter, Esc };

}  // namespace alviz
