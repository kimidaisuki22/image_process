#include <image_process/bitmaps/bitmap_flat.h>
image_process::Bitmap_flat::Bitmap_flat(int width, int height, int channel)
    : size_(width, height), channel_(channel) {
  storage_.resize(width * height * channel);
}
uint8_t *image_process::Bitmap_flat::data() { return storage_.data(); }
const uint8_t *image_process::Bitmap_flat::data() const {
  return storage_.data();
}
int image_process::Bitmap_flat::width() const { return size_.width(); }
int image_process::Bitmap_flat::height() const { return size_.height(); }
int image_process::Bitmap_flat::channel() const { return channel_; }
size_t image_process::Bitmap_flat::size_bytes() const {
  return storage_.size();
}
int image_process::Bitmap_flat::stride() const { return width() * channel(); }
