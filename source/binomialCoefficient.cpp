#include <fstream>
#include <string>
#include <print>
#include <filesystem>

#include "factorial.hpp"

static long long binomialCoefficient(const int n, const int k, int &numberOfOperations) {
    const long long factorialOfN = factorial(n, numberOfOperations);
    const long long factorialOfK = factorial(k, numberOfOperations);
    const long long factorialOfNMinusK = factorial(n - k, numberOfOperations);

    numberOfOperations++;
    return factorialOfN / (factorialOfK * factorialOfNMinusK);
}

static long long binomialCoefficientRecurrence(const int n, const int k, int &numberOfOperations) {
    if (k == 0 || k == n) return 1;

    return binomialCoefficientRecurrence(n - 1, k - 1, numberOfOperations) + binomialCoefficientRecurrence(n - 1, k, numberOfOperations);
}

void problem1(const std::string &inputPath, const std::string &outputPath) {
    std::ifstream input(inputPath);

    if (!input.is_open()) {
        std::println("Nie udało się wczytać pliku: „{}”", inputPath);
        return;
    }

    std::string line;
    getline(input, line);

    input.close();

    auto space = line.find(' ');
    int n = std::stoi(line.substr(0, space));
    int k = std::stoi(line.substr(space + 1));

    int numberOfOperationsInTheTaskOneOne = 0, numberOfOperationsInTheTaskOneThree = 0;
    auto taskOneOne = binomialCoefficient(n, k, numberOfOperationsInTheTaskOneOne);
    auto taskOneThree = binomialCoefficientRecurrence(n, k, numberOfOperationsInTheTaskOneThree);

    std::filesystem::create_directories("output");
    std::ofstream output(outputPath);

    std::println(output, "n={} k={}", n, k);
    std::println(output, "SN1 = {}, licz = {}", taskOneOne, numberOfOperationsInTheTaskOneOne);
    std::println(output, "SN3 = {}, licz = {}", taskOneThree, numberOfOperationsInTheTaskOneThree);

    output.close();
}