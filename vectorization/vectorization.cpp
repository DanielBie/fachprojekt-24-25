#include <immintrin.h>
#include <perfcpp/event_counter.h>

#include <iostream>
#include <random>
#include <tuple>

enum BenchmarkType {
    SCALAR,
    VECTORIZED_SSE,
    VECTORIZED_OPITMIZED
};

int scalarSumWithMask(const uint32_t *indBonus, const int32_t *recBonus, size_t size) {
    uint64_t sum = 0;
    return sum;
}

int sseSumWithMask(const uint32_t *indBonus, const int32_t *recBonus, std::size_t size) {
    uint64_t sum = 0;
    return sum;
}

int optimizedSumWithMask(const uint32_t *indBonus, const int32_t *recBonus, size_t size) {
    uint64_t sum = 0;
    return sum;
}

void compare_results(const uint32_t *indBonus, const int32_t *recBonus, const std::size_t elements) {
    // Print as CSV
    int scalarResult = scalarSumWithMask(indBonus, recBonus, elements);
    int sseResult = sseSumWithMask(indBonus, recBonus, elements);
    int optResult = optimizedSumWithMask(indBonus, recBonus, elements);

    std::vector<std::tuple<std::string, int>> results;
    if (scalarResult != 0) {
        results.push_back(std::make_tuple("scalar", scalarResult));
    }

    if (sseResult != 0) {
        results.push_back(std::make_tuple("sse", sseResult));
    }

    if (optResult != 0) {
        results.push_back(std::make_tuple("optimized", optResult));
    }

    if (results.size() > 1) {
        bool all_equal = true;
        for (size_t i = 1; i < results.size(); ++i) {
            if (std::get<1>(results[i]) != std::get<1>(results[0])) {
                all_equal = false;
                break;
            }
        }

        if (all_equal) {
            std::cout << "All implemented results equal!" << std::endl;
        } else {
            std::cout << "Results are different!" << std::endl;
            for (const auto &result : results) {
                std::cout << std::get<0>(result) << ": " << std::get<1>(result) << std::endl;
            }
        }
    } else if (results.size() == 1) {
        std::cout << "Only one result implemented!" << std::endl;
    } else {
        std::cout << "No results implemented!" << std::endl;
    }

}

std::string run_benchmark(const uint32_t *indBonus, const int32_t *recBonus, const std::size_t elements, const BenchmarkType benchmark_type, const uint16_t iterations) {
    auto counter_definitions = perf::CounterDefinition{};
    auto event_counter = perf::EventCounter{counter_definitions};

    try {
        event_counter.add({"cycles", "instructions", "cache-misses"});
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
    }

    try {
        event_counter.start();
    } catch (std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    auto sum = 0;
    if (benchmark_type == SCALAR) {
        for (uint32_t i = 0; i < iterations; ++i) {
            sum = scalarSumWithMask(indBonus, recBonus, elements);
        }
    } else if (benchmark_type == VECTORIZED_SSE) {
        for (uint32_t i = 0; i < iterations; ++i) {
            sum = sseSumWithMask(indBonus, recBonus, elements);
        }
    } else if (benchmark_type == VECTORIZED_OPITMIZED) {
        for (uint32_t i = 0; i < iterations; ++i) {
            sum = optimizedSumWithMask(indBonus, recBonus, elements);
        }
    }

    event_counter.stop();

    /// Calculate the result.
    const auto result = event_counter.result();

    // Print as CSV
    std::string additional = "scalar " + std::to_string(sum);
    if (benchmark_type == VECTORIZED_SSE) {
        additional = "vectorized_sse " + std::to_string(sum);
    } else if (benchmark_type == VECTORIZED_OPITMIZED) {
        additional = "vectorized_optimized " + std::to_string(sum);
    }
    return result.to_csv(',', false, additional);
}

int main() {
    const uint32_t indBonus_size_in_mb = 1000;
    const uint64_t elements = (indBonus_size_in_mb * 1024 * 1024) / sizeof(uint32_t);
    const uint64_t iterations = 20;

    uint32_t *indBonus = new uint32_t[elements];
    int32_t *recBonus = new int32_t[elements];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> dataDist(0, 5000);
    std::uniform_int_distribution<int> maskDist(0, 1);

    for (size_t i = 0; i < elements; ++i) {
        indBonus[i] = dataDist(gen);
        recBonus[i] = maskDist(gen) ? -1 : 0;
    }

    compare_results(indBonus, recBonus, elements);

    // Führe die unterschiedlichen Benchmarkkonfigurationen aus
    std::cout << run_benchmark(indBonus, recBonus, elements, SCALAR, iterations) << std::endl;
    std::cout << run_benchmark(indBonus, recBonus, elements, VECTORIZED_SSE, iterations) << std::endl;
    std::cout << run_benchmark(indBonus, recBonus, elements, VECTORIZED_OPITMIZED, iterations) << std::endl;

    // Gebe den reservierten Speicher wieder frei
    delete[] indBonus;
    delete[] recBonus;
}