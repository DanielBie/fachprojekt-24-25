#include "buckets.h"

static std::size_t mapToBucket(std::size_t v) {
    //   size of a bucket
    if (v < 13)
        return 0;  //   13
    else if (v < 29)
        return 1;  //   16
    else if (v < 41)
        return 2;  //   12
    else if (v < 53)
        return 3;  //   12
    else if (v < 71)
        return 4;  //   18
    else if (v < 83)
        return 5;  //   12
    else if (v < 100)
        return 6;  //   17
    return DEFAULT_BUCKET;
}

std::array<std::size_t, NUM_BUCKETS> histogram(const std::vector<int> &values, bool baseline) {
    std::array<std::size_t, NUM_BUCKETS> retBuckets{0};
    if (baseline) {
        for (auto v : values) {
            retBuckets[baseline_mapToBucket(v)]++;
        }
    } else {
        for (auto v : values) {
            retBuckets[mapToBucket(v)]++;
        }
    }
    return retBuckets;
}

static std::size_t baseline_mapToBucket(std::size_t v) {
    //   size of a bucket
    if (v < 13)
        return 0;  //   13
    else if (v < 29)
        return 1;  //   16
    else if (v < 41)
        return 2;  //   12
    else if (v < 53)
        return 3;  //   12
    else if (v < 71)
        return 4;  //   18
    else if (v < 83)
        return 5;  //   12
    else if (v < 100)
        return 6;  //   17
    return DEFAULT_BUCKET;
}
