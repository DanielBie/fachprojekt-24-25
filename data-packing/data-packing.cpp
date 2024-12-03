#include "metrics.h"
#include "students.h"

enum BenchmarkType {
    DAYS,
    GRADE,
    MEAN_CREDITS
};

float possibleGrades[11] = {1.0, 1.3, 1.7, 2.0, 2.3, 2.7, 3.0, 3.3, 3.7, 4.0};

std::string run_benchmark(const Student* students, const Student_Baseline* students_baseline, const std::size_t elements, const BenchmarkType benchmark_type, const uint16_t iterations) {
    auto counter_definitions = perf::CounterDefinition{};
    auto event_counter = perf::EventCounter{counter_definitions};

    try {
        event_counter.add({"cycles", "instructions", "cache-misses", "cache-references"});
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    double grade_baseline = 0.0;
    double mean_baseline = 0.0;
    unsigned long total_baseline = 0;
    double grade = 0.0;
    double mean = 0.0;
    unsigned long total = 0;

    try {
        event_counter.start();
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    if (benchmark_type == DAYS) {
        for (uint32_t i = 0; i < iterations; ++i) {
            total_baseline = meanStudentDays_Baseline(students_baseline, elements);
        }
    } else if (benchmark_type == GRADE) {
        for (uint32_t i = 0; i < iterations; ++i) {
            grade_baseline = meanGrade_Baseline(students_baseline, elements);
        }
    } else if (benchmark_type == MEAN_CREDITS) {
        for (uint32_t i = 0; i < iterations; ++i) {
            mean_baseline = meanMeanCreditsPerSemester_Baseline(students_baseline, elements);
        }
    }

    event_counter.stop();

    /// Calculate the result.
    const auto result_baseline = event_counter.result();

    try {
        event_counter.start();
    } catch (std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        exit(1);
    }
    if (benchmark_type == DAYS) {
        for (uint32_t i = 0; i < iterations; ++i) {
            total = meanStudentDays(students, elements);
        }
    } else if (benchmark_type == GRADE) {
        for (uint32_t i = 0; i < iterations; ++i) {
            grade = meanGrade(students, elements);
        }
    } else if (benchmark_type == MEAN_CREDITS) {
        for (uint32_t i = 0; i < iterations; ++i) {
            mean = meanMeanCreditsPerSemester(students, elements);
        }
    }

    event_counter.stop();

    const auto result_optimized = event_counter.result();

    if (benchmark_type == DAYS) {
        if (total_baseline != total) {
            std::cout << "Number of days not equal!" << std::endl;
        }
    } else if (benchmark_type == GRADE) {
        if (total_baseline != total) {
            std::cout << "Number of days not equal!" << std::endl;
        }
    } else if (benchmark_type == MEAN_CREDITS) {
        if (total_baseline != total) {
            std::cout << "Number of days not equal!" << std::endl;
        }
    }

    std::string res = "";
    if (benchmark_type == DAYS) {
        std::string additional = "baseline-days";
        res += result_baseline.to_csv(',', false, additional) + "\n";
        additional = "optimized-days";
        res += result_optimized.to_csv(',', false, additional) + "\n";

    } else if (benchmark_type == GRADE) {
        std::string additional = "baseline-grade";
        res += result_baseline.to_csv(',', false, additional) + "\n";
        additional = "optimized-grade";
        res += result_optimized.to_csv(',', false, additional) + "\n";
    } else if (benchmark_type == MEAN_CREDITS) {
        std::string additional = "baseline-mean-credits";
        res += result_baseline.to_csv(',', false, additional) + "\n";
        additional = "optimized-mean-credits";
        res += result_optimized.to_csv(',', false, additional) + "\n";
    }
    return res;
}

int main() {
    const uint32_t student_size_in_mb = 1000;
    const uint64_t elements = (student_size_in_mb * 1024 * 1024) / sizeof(Student_Baseline);
    const uint64_t iterations = 20;

    Student* students = new Student[elements];
    Student_Baseline* students_baseline = new Student_Baseline[elements];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint32_t> days(1, 30);
    std::uniform_int_distribution<uint32_t> months(1, 12);
    std::uniform_int_distribution<uint32_t> years(2000, 2023);
    std::uniform_int_distribution<uint32_t> passedModules(1, 32);
    std::uniform_int_distribution<uint32_t> grades(0, 10);
    std::uniform_int_distribution<uint32_t> creditPoints(3, 15);

    for (size_t i = 0; i < elements; ++i) {
        uint32_t day = days(gen);
        uint32_t month = months(gen);
        uint32_t year = years(gen);
        uint32_t passed = passedModules(gen);
        double allGrades[passed];
        uint32_t allCreditPoints[passed];
        for (size_t j = 0; j < passed; ++j) {
            allGrades[j] = possibleGrades[grades(gen)];
            allCreditPoints[j] = creditPoints(gen);
        }

        new (&students[i]) Student(day, month, year, passed, allCreditPoints, allGrades);
        new (&students_baseline[i]) Student_Baseline(day, month, year, passed, allCreditPoints, allGrades);
    }

    std::cout << "Size of Baseline Student: \t" << sizeof(Student_Baseline) << " bytes" << std::endl;
    std::cout << "Size of Student: \t\t" << sizeof(Student) << " bytes" << std::endl;


    std::cout << run_benchmark(students, students_baseline, elements, DAYS, iterations) << std::endl;
    std::cout << run_benchmark(students, students_baseline, elements, GRADE, iterations) << std::endl;
    std::cout << run_benchmark(students, students_baseline, elements, MEAN_CREDITS, iterations) << std::endl;

    delete[] students;
    delete[] students_baseline;
}