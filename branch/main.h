#include <iostream>
#include <limits>
#include <random>

#include "buckets/buckets.h"

#include <perfcpp/event_counter.h>

std::string benchmark(bool baseline = false, uint32_t iterations = 10);
bool validate();

void init(std::vector<int> &values);
