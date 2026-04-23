module;

export module GUI.Styles;

import GUI.Common;

export namespace alviz::gui::styles {
enum class TextStyle { Regular, Bold, Italic, Underline };

struct LabelStyle {
  Color color{.r = 255, .g = 255, .b = 255, .a = 255};
  uint16_t size{14};
  TextStyle style{TextStyle::Regular};
};

struct ButtonStyle {
  Color normal{.r = 50, .g = 50, .b = 50, .a = 255};
  Color hovered{.r = 80, .g = 80, .b = 80, .a = 255};
  Color focused{.r = 100, .g = 100, .b = 200, .a = 255};
  Color pressed{.r = 30, .g = 30, .b = 30, .a = 255};
  Color text{.r = 255, .g = 255, .b = 255, .a = 255};
  Color border{.r = 150, .g = 150, .b = 150, .a = 255};
  float borderThickness{1.F};
  uint16_t fontSize{14};
  TextStyle style{TextStyle::Regular};
};

inline TextStyle operator|(TextStyle style1, TextStyle style2) {
  return static_cast<TextStyle>(static_cast<uint8_t>(style1) |
                                static_cast<uint8_t>(style2));
}

inline bool operator&(TextStyle style1, TextStyle style2) {
  return static_cast<uint8_t>(style1) & static_cast<uint8_t>(style2);
}
};  // namespace alviz::gui::styles
