#pragma once
namespace image_process {
class Image_position {
public:
  Image_position(const Image_position &) = default;
  Image_position(Image_position &&) = default;
  Image_position &operator=(const Image_position &) = default;
  Image_position &operator=(Image_position &&) = default;
  Image_position(int x, int y) : x_(x), y_(y) {}

  int x() const noexcept { return x_; }
  int y() const noexcept { return y_; }

private:
  int x_{};
  int y_{};
};
} // namespace image_process