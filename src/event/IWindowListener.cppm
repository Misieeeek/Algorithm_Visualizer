module;

export module Alviz.Events:WindowListener;

import Alviz.Math;

export namespace alviz {
enum class WindowEvent { CLOSED, RESIZED, FOCUSLOST, FOCUSGAINED };

class IWindowListener {
 public:
  virtual ~IWindowListener() = default;
  virtual void onWindowClosed() = 0;
  virtual void onWindowResized(FloatRect size) {}
  virtual void onFocusLost() {};
  virtual void onFocusGained() {};
};
}  // namespace alviz
