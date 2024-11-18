#include <array>
#include <vector>

constexpr std::size_t NUM_BUCKETS = 8;
constexpr std::size_t DEFAULT_BUCKET = NUM_BUCKETS - 1;
constexpr std::size_t NUM_VALUES = 1024 * 1024;

std::array<std::size_t, NUM_BUCKETS> histogram(const std::vector<int> &values, bool baseline = false);

static std::size_t mapToBucket(std::size_t v);
static std::size_t baseline_mapToBucket(std::size_t v);