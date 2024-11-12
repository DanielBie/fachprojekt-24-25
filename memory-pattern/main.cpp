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
    Grayscale image;
    if (image.load("../input.pbm", kMaxImageDimension)) {
        decltype(Grayscale::data) imageResult(new uint8_t[image.size]);
        decltype(Grayscale::data) temp(new uint8_t[image.size]);
        if (!imageResult || !temp) {
            std::cerr << "Benchmark Failed. Out of memory" << std::endl;
            return "error";
        }

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
            blur(imageResult.get(), image.data.get(), image.width, image.height, temp.get(), baseline);
        }

        event_counter.stop();

        /// Calculate the result.
        const auto result = event_counter.result();

        // Print as CSV
        std::string additional = "optimized";
        if (baseline) additional = "baseline";
        return result.to_csv(',', false, additional);

    }
}

bool validate() {
    Grayscale image;
    if (image.load("../input.pbm", kMaxImageDimension)) {
        Grayscale image2;
        if (image2.load("../output-golden.pgm", kMaxImageDimension)) {
            // Copied & pasted
            {
                decltype(Grayscale::data) result(new uint8_t[image.size]);
                decltype(Grayscale::data) temp(new uint8_t[image.size]);
                if (!result || !temp) {
                    std::cerr << "Validation Failed. Out of memory" << std::endl;
                    return false;
                }

                blur(result.get(), image.data.get(), image.width, image.height, temp.get());
                std::swap(image.data, result);
            }

            if ((image.width != image2.width) || (image.height != image2.height)) {
                std::cerr << "Validation Failed. Wrong image dimensions " << image.width << 'x' << image.height << std::endl;
                return false;
            }

            auto p1 = image.data.get();
            auto p2 = image2.data.get();
            if (std::memcmp(p1, p2, image.size) == 0) {
                std::cout << "Validation Successful" << std::endl;
                return true;
            }

            std::cerr << "Validation Failed. Distinct images" << std::endl;
            int downcount = 10;
            for (size_t i = 0; i < image.size; i++) {
                if (p1[i] != p2[i]) {
                    std::cerr << "Result[" << i << "] = " << static_cast<int>(p1[i])
                              << ". Expected[" << i << "] = " << static_cast<int>(p2[i])
                              << std::endl;
                    if (--downcount <= 0)
                        break;
                }
            }
            return false;
        }
    }
    return false;
}
