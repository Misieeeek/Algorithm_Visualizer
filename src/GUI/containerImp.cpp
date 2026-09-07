module;

#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>

module GUI.Container;

import GUI.ICanvas;
import Alviz.Math;
import GUI.Widget;

namespace alviz::gui {
void Container::add(const std::shared_ptr<Widget> widget) {
  children_.push_back(widget);
}

void Container::remove(const std::shared_ptr<Widget> widget) {
  std::erase(children_, widget);
}

void Container::update(math::f32 deltaTime) {
  for (auto& child : children_) {
    child->update(deltaTime);
  }
};

void Container::render(ICanvas& canvas) {
  for (auto& child : children_) {
    if (child->visible()) {
      child->render(canvas);
    }
  }
};

void Container::onKey(Key key) {
  if (auto focused = getFocused()) {
    focused->onKey(key);
  }
};

void Container::onText(math::u32 unicode) {
  if (auto focused = getFocused()) {
    focused->onText(unicode);
  }
};

void Container::onMouseMove(Vec2i pos) {
  for (auto& child : children_) {
    child->onMouseMove(pos);
  }
};

void Container::onMouseClick(Vec2i pos) {
  for (auto& child : children_) {
    if (child->contains(pos)) {
      setFocus(child);
      child->onMouseClick(pos);
      return;
    }
  }
};

std::shared_ptr<Widget> Container::getFocused() {
  if (focusIndex_ == kNoFocus) {
    return nullptr;
  }

  return children_[focusIndex_];
}

void Container::setFocus(std::shared_ptr<Widget>& widget) {
  if (focusIndex_ >= kNoFocus) {
    children_[focusIndex_]->setFocused(false);
  }

  auto iter = std::ranges::find(children_, widget);
  if (iter == children_.end()) {
    return;
  }

  focusIndex_ = std::distance(children_.begin(), iter);
  widget->setFocused(true);
}

void Container::nextFocus() {
  if (children_.empty()) {
    return;
  }

  if (focusIndex_ >= kNoFocus) {
    children_[focusIndex_]->setFocused(false);
  }
  focusIndex_ = (focusIndex_ + 1) % children_.size();
  children_[focusIndex_]->setFocused(true);
}
}  // namespace alviz::gui
