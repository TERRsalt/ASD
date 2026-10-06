#include "factorial.hpp"

//info // Maksymalnie działa na 13! z powodu ograniczenia int-a //

int binomialCoefficient(const int n, const int k) {
    const int factorialOfN = factorial(n);
    const int factorialOfK = factorial(k);
    const int factorialOfNMinusK = factorial(n - k);

    return factorialOfN / (factorialOfK * factorialOfNMinusK);
}

int binomialCoefficientRecurrence(const int n, const int k) {
    if (k == 0 || k == n) return 1;

    return binomialCoefficientRecurrence(n - 1, k - 1) + binomialCoefficientRecurrence(n - 1, k);
}