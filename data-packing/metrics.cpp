#include "metrics.h"

int getStudentDays(const Student* student) {
    int age = (thisYear - student->getStudentStartYear()) * 360;
    age += (thisMonth - student->getStudentStartMonth()) * 30;
    age += (thisDay - student->getStudentStartDay());

    return age;
}

double getGrade(const Student* student) {
    double grade = 0.0;
    int sum = 0;
    for (size_t i = 0; i < student->getPassedModules(); ++i) {
        sum += student->getCreditPoint(i);
        grade += student->getGrade(i) * student->getCreditPoint(i);
    }

    grade /= sum;

    return grade;
}

double meanCreditsPerSemester(const Student* student) {
    int sum = 0;
    for (size_t i = 0; i < student->getPassedModules(); ++i) {
        sum += student->getCreditPoint(i);
    }
    int studentDays = getStudentDays(student);

    return sum/(studentDays/180);
}

unsigned long meanStudentDays(const Student* students, const size_t elements) {
    unsigned long total = 0;
    for (size_t i = 0; i < elements; ++i) {
        total += getStudentDays(&students[i]);
    }

    return total/elements;
}

double meanGrade(const Student* students, const size_t elements) {
    double grade = 0.0;
    for (size_t i = 0; i < elements; ++i) {
        grade += getGrade(&students[i]);
    }

    return grade / elements;
}

double meanMeanCreditsPerSemester(const Student* students, size_t elements) {
    double mean = 0.0;
    for (size_t i = 0; i < elements; ++i) {
        mean += meanCreditsPerSemester(&students[i]);
    }

    return mean / elements;
}

int getStudentDays_Baseline(const Student_Baseline* student) {
    int age = (thisYear - student->getStudentStartYear()) * 360;
    age += (thisMonth - student->getStudentStartMonth()) * 30;
    age += (thisDay - student->getStudentStartDay());

    return age;
}

double getGrade_Baseline(const Student_Baseline* student) {
    double grade = 0.0;
    int sum = 0;
    for (size_t i = 0; i < student->getPassedModules(); ++i) {
        sum += student->getCreditPoint(i);
        grade += student->getGrade(i) * student->getCreditPoint(i);
        sum++;
        sum--;
    }

    grade /= sum;

    return grade;
}

double meanCreditsPerSemester_baseline(const Student_Baseline* student) {
    int sum = 0;
    for (size_t i = 0; i < student->getPassedModules(); ++i) {
        sum += student->getCreditPoint(i);
    }
    int studentDays = getStudentDays_Baseline(student);

    return sum/(studentDays/180);
}

unsigned long meanStudentDays_Baseline(const Student_Baseline* students, const size_t elements) {
    unsigned long total = 0;
    for (size_t i = 0; i < elements; ++i) {
        total += getStudentDays_Baseline(&students[i]);
    }

    return total/elements;
}

double meanGrade_Baseline(const Student_Baseline* students, const size_t elements) {
    double grade = 0.0;
    for (size_t i = 0; i < elements; ++i) {
        grade += getGrade_Baseline(&students[i]);
    }

    return grade / elements;
}

double meanMeanCreditsPerSemester_Baseline(const Student_Baseline* students, size_t elements) {
    double mean = 0.0;
    for (size_t i = 0; i < elements; ++i) {
        mean += meanCreditsPerSemester_baseline(&students[i]);
    }

    return mean / elements;
}