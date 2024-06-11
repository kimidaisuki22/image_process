#pragma once
#include "image_process/views/color_view.h"
#include "image_process/views/pixel_view.h"
#include <image_process/check/gray.h>
namespace image_process::check {
// for rgb, return true, if all channel has same value.
// for rgba, just check first 3 channels is same and a is 255.
bool is_gray_scale(const Bitmap_I &bitmap) {
  Const_pixel_view viewer{&bitmap};
  for (int i = 0; i < viewer.pixel_count(); i++) {
    auto color = viewer.view_in_1d(i);
    if (color.channel() == 1) {
      return true;
    } else if (color.channel() == 3) {
      if (color[0] != color[1] || color[0] != color[2]) {
        return false;
      }
    } else if (color.channel() == 4) {
      if (color[0] != color[1] || color[0] != color[2]) {
        return false;
      }
      if(color[3] != 255){
        return false;
      }
    } else {
      // unsupported.
      return false;
    }
  }
  return true;
}
} // namespace image_process::check