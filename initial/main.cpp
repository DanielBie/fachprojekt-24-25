#include "main.h"


int main() {
    std::unique_ptr<Matrix> a(new Matrix());
    zero(*a);

    std::unique_ptr<Matrix> b(new Matrix());
    init(*b);

    std::unique_ptr<Matrix> c(new Matrix());
    init(*c);

    
    std::cout << "counter,value,type" << std::endl;
    std::cout << benchmark(*a, *b, *c, true) << std::endl;
    std::cout << benchmark(*a, *b, *c) << std::endl;
}

std::string benchmark(Matrix& a, const Matrix& b, const Matrix& c, bool baseline, uint32_t iterations){
    auto counter_definitions = perf::CounterDefinition{};

    auto event_counter = perf::EventCounter{counter_definitions};
    try {
        event_counter.add({"instructions", "cycles", "cache-misses", "cache-references", "L1-dcache-loads", "L1-dcache-load-misses", "dTLB-loads", "dTLB-load-misses"});
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        event_counter.start();
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }

    for (uint32_t i = 0; i < iterations; ++i) {
        if(baseline){
            baseline_multiply(a, b, c);
        } else {
            multiply(a, b, c);
        }
    }

    event_counter.stop();

    /// Calculate the result.
    const auto result = event_counter.result();

    // Print as CSV
    std::string additional = "optimized";
    if(baseline) additional = "baseline";
    return result.to_csv(',', false, additional);
}
