#include <iostream>
#include "matrix/matrix.h"

#include <perfcpp/event_counter.h>

std::string benchmark(Matrix& a, const Matrix& b, const Matrix& c, bool baseline = false, uint32_t iterations = 10);