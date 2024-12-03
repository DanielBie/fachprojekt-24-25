#ifndef STUDENTS_H
#define STUDENTS_H

#include <perfcpp/event_counter.h>

#include <iostream>
#include <random>

class Student {
   public:
    int studentStartDay;    // 1-30
    int creditPoints[32];   // 3-15
    int studentStartMonth;  // 1-12
    double grades[32];      // one of {1.0, 1.3, ...,  3.7, 4.0}
    int studentStartYear;   // 2000-2024
    int passedModules;      // 1-32

    Student() {}

    Student(int startDay, int startMonth, int startYear, int passed, const unsigned int* credits, const double* grades) {
        this->studentStartDay = startDay;
        this->studentStartMonth = startMonth;
        this->studentStartYear = startYear;
        this->passedModules = passed;
        for (size_t i = 0; i < passed; ++i) {
            this->creditPoints[i] = credits[i];
            this->grades[i] = grades[i];
        }
    }

    const int getStudentStartDay() const {
        return studentStartDay;
    }

    const int getStudentStartMonth() const {
        return studentStartMonth;
    }

    const int getStudentStartYear() const {
        return studentStartYear;
    }

    const int getPassedModules() const {
        return passedModules;
    }

    const int getCreditPoint(size_t index) const {
        return creditPoints[index];
    }

    const double getGrade(size_t index) const {
        return grades[index];
    }
};

class Student_Baseline {
   public:
    int studentStartDay;    // 1-30
    int creditPoints[32];   // 3-15
    int studentStartMonth;  // 1-12
    double grades[32];      // one of {1.0, 1.3, ...,  3.7, 4.0}
    int studentStartYear;   // 2000-2024
    int passedModules;      // 1-32

    Student_Baseline() {}

    Student_Baseline(int startDay, int startMonth, int startYear, int passed, const unsigned int* credits, const double* grades) {
        this->studentStartDay = startDay;
        this->studentStartMonth = startMonth;
        this->studentStartYear = startYear;
        this->passedModules = passed;
        for (size_t i = 0; i < passed; ++i) {
            this->creditPoints[i] = credits[i];
            this->grades[i] = grades[i];
        }
    }

    const int getStudentStartDay() const {
        return studentStartDay;
    }

    const int getStudentStartMonth() const {
        return studentStartMonth;
    }

    const int getStudentStartYear() const {
        return studentStartYear;
    }

    const int getPassedModules() const {
        return passedModules;
    }

    const int getCreditPoint(size_t index) const {
        return creditPoints[index];
    }

    const double getGrade(size_t index) const {
        return grades[index];
    }
};

#endif
