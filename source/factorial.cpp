#include <print>

int factorial(const int n) {
    if (n < 0) {
        std::println("Silnia z liczby nie może być ujemna!");
        return -1;
    }

    int returnNumber = 1;
    for (int i = 1; i <= n; i++) returnNumber *= i;
    return returnNumber;
}