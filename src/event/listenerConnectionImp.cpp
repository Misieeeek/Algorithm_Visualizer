module Alviz.Events;

import std;

namespace alviz {
ListenerConnection::ListenerConnection(const std::function<void()> action)
    : disconnectAction_(std::move(action)) {}

ListenerConnection::~ListenerConnection() {
  if (disconnectAction_) {
    disconnectAction_();
  }
}

ListenerConnection::ListenerConnection(ListenerConnection&& other) noexcept
    : disconnectAction_(std::move(other.disconnectAction_)) {
  other.disconnectAction_ = nullptr;
}

ListenerConnection& ListenerConnection::operator=(
    ListenerConnection&& other) noexcept {
  if (this != &other) {
    if (disconnectAction_) {
      disconnectAction_();
    }
    disconnectAction_ = std::move(other.disconnectAction_);
    other.disconnectAction_ = nullptr;
  }
  return *this;
}
}  // namespace alviz
