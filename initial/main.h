#include <iostream>
#include "matrix/matrix.h"

#include <perfcpp/event_counter.h>

std::string benchmark(bool baseline = false, uint32_t iterations = 10);
bool validate();