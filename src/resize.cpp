#include "image_process/bitmaps/bitmap_flat.h"
// #include "spdlog/spdlog.h"
#include <image_process/resize.h>
#include <memory>

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>

namespace image_process {
std::optional<std::unique_ptr<Bitmap_I>>
scale_down_to_height(Bitmap_I &bitmap, int target_height) {
  if (bitmap.height() <= target_height) {
    return {};
  }

  auto height = bitmap.height();
  auto width = bitmap.width();
  auto channel = bitmap.channel();

  auto radio = target_height * 1.0 / height;
  int output_width = radio * width, output_height = height * radio;
  Bitmap_flat bitmap_out{output_width, output_height, channel};

  auto ok = stbir_resize_uint8(bitmap.data(), width, height, width * channel,
                               bitmap_out.data(), output_width, output_height,
                               bitmap_out.stride(), channel);
  if (!ok) {
    //  SPDLOG_ERROR("resize image failed.");
    return {};
  }
  return std::make_unique<Bitmap_flat>(std::move(bitmap_out));
}
std::optional<std::unique_ptr<Bitmap_I>> scale_up_to_height(Bitmap_I &bitmap,
                                                            int target_height) {
  if (bitmap.height() >= target_height) {
    return {};
  }

  auto height = bitmap.height();
  auto width = bitmap.width();
  auto channel = bitmap.channel();

  auto radio = target_height * 1.0 / height;
  int output_width = radio * width, output_height = height * radio;
  Bitmap_flat bitmap_out{output_width, output_height, channel};

  auto ok = stbir_resize_uint8(bitmap.data(), width, height, width * channel,
                               bitmap_out.data(), output_width, output_height,
                               bitmap_out.stride(), channel);
  if (!ok) {
    //  SPDLOG_ERROR("resize image failed.");
    return {};
  }
  return std::make_unique<Bitmap_flat>(std::move(bitmap_out));
}
std::optional<std::unique_ptr<Bitmap_I>>
resize_to(Bitmap_I &bitmap, int target_width, int target_height) {
  auto height = bitmap.height();
  auto width = bitmap.width();
  auto channel = bitmap.channel();

  Bitmap_flat bitmap_out{target_width, target_height, channel};

  auto ok = stbir_resize_uint8(bitmap.data(), width, height, width * channel,
                               bitmap_out.data(), target_width, target_height,
                               bitmap_out.stride(), channel);
  if (!ok) {
    //  SPDLOG_ERROR("resize image failed.");
    return {};
  }
  return std::make_unique<Bitmap_flat>(std::move(bitmap_out));
}
} // namespace image_process