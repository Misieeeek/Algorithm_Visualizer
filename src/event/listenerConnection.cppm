export module Alviz.Events:ListenerConnection;

import std;

export namespace alviz {
class ListenerConnection {
 private:
  std::function<void()> disconnectAction_;

 public:
  explicit ListenerConnection(const std::function<void()> action);
  ~ListenerConnection();

  ListenerConnection(const ListenerConnection& other) = delete;
  ListenerConnection& operator=(const ListenerConnection& other) = delete;
  ListenerConnection(ListenerConnection&& other) noexcept;
  ListenerConnection& operator=(ListenerConnection&& other) noexcept;
};
}  // namespace alviz
