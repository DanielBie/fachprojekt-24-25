#include "matrix.h"

#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <string_view>

// Multiply two square matrices
void multiply(Matrix &result, const Matrix &a, const Matrix &b) {
    zero(result);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// This is used as a baseline, DO NOT CHANGE THIS
void baseline_multiply(Matrix &result, const Matrix &a, const Matrix &b) {
    zero(result);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

// Make zero matrix
void zero(Matrix &result) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
        }
    }
}

// Make identity matrix
void identity(Matrix &result) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            result[i][j] = 0;
        }
        result[i][i] = 1;
    }
}

void init(Matrix &matrix) {
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(-0.95f, 0.95f);

    for (int i = 0; i < N; i++) {
        float sum = 0;
        for (int j = 0; j < N; j++) {
            float value = distribution(generator);
            sum += value * value;
            matrix[i][j] = value;
        }

        // Normalize rows
        if (sum >= std::numeric_limits<float>::min()) {
            float scale = 1.0f / std::sqrt(sum);
            for (int j = 0; j < N; j++) {
                matrix[i][j] *= scale;
            }
        }
    }
}

void copy(Matrix &source, Matrix &target) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            target[i][j] = source[i][j];
        }
    }
}

bool operator==(const Matrix& a, const Matrix& b){
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(a[i][j] != b[i][j]){ 
                return false;
            }
        }
    }
    return true;
}
