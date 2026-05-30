module;

module GUI.Label;

import std;
import GUI.ICanvas;
import Alviz.Math;
import GUI.Styles;
import GUI.Widget;

namespace alviz::gui {
void Label::render(ICanvas& canvas) {
  canvas.drawText(text_, {getBounds().x, getBounds().y}, style_.color,
                  style_.size, style_.style);
}

void Label::setText(std::string text) { text_ = std::move(text); }

const std::string& Label::getText() const { return text_; }

void Label::setStyle(styles::LabelStyle style) { style_ = std::move(style); }
}  // namespace alviz::gui
