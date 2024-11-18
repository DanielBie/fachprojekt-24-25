#include "main.h"

int main() {
    if (!validate()) {
        std::cout << "Optimized result is not the same as baseline result!" << std::endl;
        exit(2);
    }

    std::cout << "counter,value,type" << std::endl;
    std::cout << benchmark(true) << std::endl;
    std::cout << benchmark() << std::endl;
}

std::string benchmark(bool baseline, uint32_t iterations) {
    std::vector<int> values;
    values.reserve(NUM_VALUES);
    init(values);

    auto counter_definitions = perf::CounterDefinition{};

    auto event_counter = perf::EventCounter{counter_definitions};
    try {
        event_counter.add({"instructions", "cycles", "branches", "branch-instructions", "branch-misses"});
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
        if (baseline) {
            auto baseline_result = histogram(values, true);
        } else {
            auto optimized_result = histogram(values, false);
        }
    }

    event_counter.stop();

    /// Calculate the result.
    const auto result = event_counter.result();

    // Print as CSV
    std::string additional = "optimized";
    if (baseline) additional = "baseline";
    return result.to_csv(',', false, additional);
}

bool validate() {
    std::vector<int> values;
    values.reserve(NUM_VALUES);
    init(values);

    auto baseline_result = histogram(values, true);
    auto optimized_result = histogram(values, false);

    for (unsigned int i = 0; i < baseline_result.size(); ++i) {
        if (baseline_result[i] != optimized_result[i]) {
            std::cout << "bucket " << i << " has different results\nbaseline-bucket: " << baseline_result[i] << ", optimized bucket: " << optimized_result[i] << std::endl;
            return false;
        }
    }

    return true;
}

void init(std::vector<int> &values) {
    std::random_device r;
    std::default_random_engine generator(r());
    // generate random integer in the closed interval [0,150]
    // the chance of selecting the default bucket is ~33%
    std::uniform_int_distribution<int> distribution(0, 150);
    for (int i = 0; i < NUM_VALUES; i++) {
        values.push_back(distribution(generator));
    }
}
