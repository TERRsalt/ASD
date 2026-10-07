#include <print>

long long factorial(const int n, int &numberOfOperations) {
    if (n < 0) {
        std::println("Silnia z liczby nie może być ujemna!");
        return -1;
    }

    long long returnNumber = 1;
    for (int i = 2; i <= n; i++) {
        returnNumber *= i;
        numberOfOperations++;
    }
    return returnNumber;
}