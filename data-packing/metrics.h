#ifndef METRICS_H
#define METRICS_H

#include "students.h"

const int thisDay = 5;
const int thisMonth = 12;
const int thisYear = 2024;

int getStudentDays(const Student* student);

double getGrade(const Student* student);

double meanCreditsPerSemester(const Student* student);

unsigned long meanStudentDays(const Student* students, const size_t elements);

double meanGrade(const Student* students, const size_t elements);

double meanMeanCreditsPerSemester(const Student* students, size_t elements);


int getStudentDays_Baseline(const Student_Baseline* student);

double meanCreditsPerSemester_baseline(const Student_Baseline* student);

double getGrade_Baseline(const Student_Baseline* student);

unsigned long meanStudentDays_Baseline(const Student_Baseline* students, const size_t elements);

double meanGrade_Baseline(const Student_Baseline* students, const size_t elements);

double meanMeanCreditsPerSemester_Baseline(const Student_Baseline* students, size_t elements);

#endif