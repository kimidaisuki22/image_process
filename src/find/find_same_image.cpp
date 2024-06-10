#include "image_process/image_position.h"
#include "image_process/views/pixel_view.h"
#include <cassert>
#include <image_process/find/find_same_image.h>
namespace {
using namespace image_process;
bool check_is_same_image(const Const_pixel_view &src,
                         const Const_pixel_view &sub, int total_channel,
                         int x_offset_in_src, int y_offset_in_src) {
  for (int i = 0; i < sub.height(); i++) {
    for (int j = 0; j < sub.width(); j++) {
      auto src_c = src(x_offset_in_src + j, y_offset_in_src + i);
      auto sub_c = sub(j, i);
      for (int k = 0; k < total_channel; k++) {
        if (src_c[k] != sub_c[k]) {
          return false;
        }
      }
    }
  }
  return true;
}
} // namespace
namespace image_process::find {
std::optional<image_process::Image_position>
find_same_image(const Bitmap_I &main_image, const Bitmap_I &sub_image,
                int total_channel) {
  image_process::Const_pixel_view src{&main_image};
  image_process::Const_pixel_view sub{&sub_image};
  assert(sub_image.width() > 0);
  assert(sub_image.height() > 0);
  if (main_image.channel() < total_channel ||
      sub_image.channel() < total_channel) {
    return {};
  }
  if (src.height() < sub.height()) {
    return {};
  }
  if (src.width() < sub.width()) {
    return {};
  }

  for (int i = 0; i < src.height() - sub.height(); i++) {
    for (int j = 0; j < src.width() - sub.width(); j++) {
      if (check_is_same_image(src, sub, total_channel, j, i)) {
        return Image_position{j, i};
      }
    }
  }
  return {};
}
} // namespace image_process::find