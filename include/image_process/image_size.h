#pragma once

namespace image_process {
struct Image_size {
  Image_size() = default;
  Image_size(int w, int h) : width_(w), height_(h) {}

  int width() const noexcept { return width_; }
  int height() const noexcept { return height_; };

  int width_{};
  int height_{};
};

} // namespace image_process