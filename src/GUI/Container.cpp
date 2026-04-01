#include "GUI/Container.h"

namespace alviz::gui {
void Container::add(const std::shared_ptr<Widget> widget) {
  _children.push_back(widget);
}

void Container::remove(const std::shared_ptr<Widget> widget) {
  std::erase(_children, widget);
}

void Container::update() {
  for (auto& child : _children) {
    child->update();
  }
};

void Container::render(ICanvas& canvas) {
  for (auto& child : _children) {
    if (child->visible()) {
      child->render(canvas);
    }
  }
};

void Container::onKey(Key key) {
  if (auto focused = _getFocused()) {
    focused->onKey(key);
  }
};

void Container::onText(uint32_t unicode) {
  if (auto focused = _getFocused()) {
    focused->onText(unicode);
  }
};

void Container::onMouseMove(float xPos, float yPos) {
  for (auto& child : _children) {
    child->onMouseMove(xPos, yPos);
  }
};

void Container::onMouseClick(float xPos, float yPos) {
  for (auto& child : _children) {
    if (child->contains(xPos, yPos)) {
      _setFocus(child);
      child->onMouseClick(xPos, yPos);
      return;
    }
  }
};

std::shared_ptr<Widget> Container::_getFocused() {
  if (_focusIndex < 0 || _focusIndex >= _children.size()) {
    return nullptr;
  }
  return _children[_focusIndex];
}

void Container::_setFocus(std::shared_ptr<Widget>& widget) {
  if (_focusIndex >= 0) {
    _children[_focusIndex]->setFocused(false);
  }

  auto iter = std::ranges::find(_children, widget);
  if (iter != _children.end()) {
    return;
  }

  _focusIndex = std::distance(_children.begin(), iter);
  widget->setFocused(true);
}

void Container::_nextFocus() {
  if (_children.empty()) {
    return;
  }

  if (_focusIndex >= 0) {
    _children[_focusIndex]->setFocused(false);
  }
  _focusIndex = (_focusIndex + 1) % _children.size();
  _children[_focusIndex]->setFocused(true);
}
}  // namespace alviz::gui
