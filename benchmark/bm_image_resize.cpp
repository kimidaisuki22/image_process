#include "image_process/bitmaps/bitmap_flat.h"
#include <benchmark/benchmark.h>


static void BM_Bitmap_create(benchmark::State &state) {
  int size = state.range();
  for (auto _ : state) {
    image_process::Bitmap_flat bitmap{size, size, 4};
  }
}
// Register the function as a benchmark
BENCHMARK(BM_Bitmap_create)->Range(1, 1024 * 16);
