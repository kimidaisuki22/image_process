#include "image_process/bitmaps/bitmap_flat.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <cstdlib>
#include <cstring>
#include <map>
#include <unordered_map>
#include <vector>

static void BM_Bitmap_create(benchmark::State &state) {
  for (auto _ : state) {
    image_process::Bitmap_flat bitmap{1024, 1024, 4};
  }
}
// Register the function as a benchmark
BENCHMARK(BM_Bitmap_create);
