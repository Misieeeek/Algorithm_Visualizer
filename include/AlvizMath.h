
namespace alviz {
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
}  // namespace alviz
