module;

#include <gtest/gtest.h>

export module Alviz.Test.GUIRoot;

import Alviz.EventManager;
import GUI.Root;

class GUIRootTest : public testing::Test {
 protected:
  alviz::EventManager evntManager_;
};

TEST_F(GUIRootTest, CorrectConstructor) {
  EXPECT_EQ(evntManager_.mouseListenersCount(), 0);
  EXPECT_EQ(evntManager_.keyboardListenersCount(), 0);
  {
    alviz::gui::GUIRoot root(evntManager_);

    EXPECT_EQ(evntManager_.mouseListenersCount(), 1);
    EXPECT_EQ(evntManager_.keyboardListenersCount(), 1);
  }
  EXPECT_EQ(evntManager_.mouseListenersCount(), 0);
  EXPECT_EQ(evntManager_.keyboardListenersCount(), 0);
}
