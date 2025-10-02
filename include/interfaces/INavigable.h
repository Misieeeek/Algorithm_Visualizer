#ifndef INAVIGABLE_H
#define INAVIGABLE_H

#pragma once

class INavigable {
 public:
  virtual ~INavigable() = default;

  virtual void move_up() = 0;
  virtual void move_down() = 0;
  virtual void move_left() = 0;
  virtual void move_right() = 0;

  virtual int get_selected_index() const = 0;
};

#endif
