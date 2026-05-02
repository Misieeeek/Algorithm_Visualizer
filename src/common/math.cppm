module;

export module Alviz.Math;

import std;

export namespace alviz {
struct Vec2 {
  float x, y;
};

struct FloatRect {
  float x, y;
  float width, height;

  bool contains(float pos_x, float pos_y) const {
    return pos_x >= x && pos_x <= x + width && pos_y >= y &&
           pos_y <= y + height;
  };
};

enum class Key { Up, Down, Left, Right, Enter, Esc };

namespace math {
using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using f32 = std::float_t;
using f64 = std::double_t;
}  // namespace math

}  // namespace alviz
