#include "image_process/bitmaps/bitmap_flat.h"
#include "image_process/check/gray.h"
#include "image_process/views/pixel_view.h"
#include <benchmark/benchmark.h>

static void BM_gray_check_rgba(benchmark::State &state) {
  int size = state.range();
  image_process::Bitmap_flat bitmap{size, size, 4};
  image_process::Pixel_view view{&bitmap};
  for (int i = 0; i < view.pixel_count(); i++) {
    view.view_in_1d(i)[3] = 255;
  }
  int count{};
  for (auto _ : state) {
    if (!image_process::check::is_gray_scale(bitmap)) {
      state.SkipWithError("Wrong result");
    }
    count++;
  }
  state.SetBytesProcessed(count * bitmap.size_bytes());
}
// Register the function as a benchmark
BENCHMARK(BM_gray_check_rgba)
    ->Range(1, 1024 * 16)
    ->RangeMultiplier(2)
    ->Unit(benchmark::TimeUnit::kMillisecond);

static void BM_gray_check_rgb(benchmark::State &state) {
  int size = state.range();
  image_process::Bitmap_flat bitmap{size, size, 3};
  int count{};
  for (auto _ : state) {
    if (!image_process::check::is_gray_scale(bitmap)) {
      state.SkipWithError("Wrong result");
    }
    count++;
  }
  state.SetBytesProcessed(count * bitmap.size_bytes());
}
// Register the function as a benchmark
BENCHMARK(BM_gray_check_rgb)
    ->Range(1, 1024 * 16)
    ->RangeMultiplier(2)
    ->Unit(benchmark::TimeUnit::kMillisecond);
