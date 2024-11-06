#include <array>
#include <cstdint>

// Assume this constant never changes
constexpr int N = 400;

// Square matrix 400 x 400
using Matrix = std::array<std::array<float, N>, N>;

void multiply(Matrix &result, const Matrix &a, const Matrix &b);
void baseline_multiply(Matrix &result, const Matrix &a, const Matrix &b);

void zero(Matrix &result);
void identity(Matrix &result);

void init(Matrix &matrix);
void copy(Matrix &source, Matrix &target);
bool operator==(const Matrix& a, const Matrix& b);
