namespace alviz::gui {
struct Color {
  uint8_t r, g, b, a;
};

struct ButtonStyle {
  Color normal = {.r = 50, .g = 50, .b = 50, .a = 255};
  Color hovered = {.r = 80, .g = 80, .b = 80, .a = 255};
  Color focused = {.r = 100, .g = 100, .b = 200, .a = 255};
  Color pressed = {.r = 30, .g = 30, .b = 30, .a = 255};
  Color text = {.r = 255, .g = 255, .b = 255, .a = 255};
  Color border = {.r = 150, .g = 150, .b = 150, .a = 255};
  float borderThickness = 1.F;
  unsigned int fontSize = 14;
};

};  // namespace alviz::gui
