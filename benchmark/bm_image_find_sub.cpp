#include "image_process/exporters/exporter_stb.h"
#include "image_process/find/find_same_image.h"
#include "image_process/image_position.h"
#include "image_process/loader.h"
#include <array>
#include <benchmark/benchmark.h>
#include <fstream>
#include <image_process/draw/rect_border.h>
#include <image_process/draw/rect_fill.h>
#include <optional>
#include <string>

static void BM_image_sub_find(benchmark::State &state) {
  auto loader = image_process::get_default_loader();
  auto src = loader->load_file("a.png").value();
  auto sub = loader->load_file("b.png").value();
  std::optional<image_process::Image_position> pos;
  for (auto _ : state) {
    pos = image_process::find::find_same_image(*src, *sub, 3);
  }
  if (pos) {
    std::array<uint8_t, 4> green_buffer{0, 255, 0, 255};
    image_process::Color_view green{green_buffer.data(), sub->channel()};
    image_process::draw::rect_border(*src, green, pos->x(), pos->y(),
                                     sub->width(), sub->height());

    image_process::Exporter_stb_png exporter;
    auto image = exporter.export_to_buffer(*src);

    std::ofstream file{"find_sub_result.png", std::ios::binary};
    file.write(reinterpret_cast<const char *>(image->data()), image->size());
    state.SetLabel("[" + std::to_string(pos->x()) + ", " +
                   std::to_string(pos->y()) + "]");
  } else {
    state.SetLabel("image not found");
  }
}
// Register the function as a benchmark
BENCHMARK(BM_image_sub_find)->Unit(benchmark::TimeUnit::kMillisecond);
