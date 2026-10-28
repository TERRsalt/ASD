#include <filesystem>
#include <fstream>
#include <vector>
#include <print>
#include <sstream>
#include <string>

static void heapify(const int n, std::vector<int> &array, const int arrayIndex) {
    int largerIndex = arrayIndex;
    const int leftNumberIndex = 2 * arrayIndex + 1;
    const int rightNumberIndex = leftNumberIndex + 1;

    if (leftNumberIndex < n && array[leftNumberIndex] > array[largerIndex]) largerIndex = leftNumberIndex;
    if (rightNumberIndex < n && array[rightNumberIndex] > array[largerIndex]) largerIndex = rightNumberIndex;

    if (arrayIndex != largerIndex) {
        std::swap(array[arrayIndex], array[largerIndex]);
        heapify(n, array, largerIndex);
    }
}

static void heapSort(const int n, std::vector<int> &array) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(n, array, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(array[0], array[i]);
        heapify(i, array, 0);
    }
}

void problem1C(const std::string &inputPath, const std::string &outputPath) {
    std::ifstream input(inputPath);

    if (!input.is_open()) {
        std::println("Nie udało się wczytać pliku: „{}”", inputPath);
        return;
    }

    std::string line;
    getline(input, line);
    const int n = std::stoi(line);

    std::vector<int> array;
    getline(input, line);
    std::istringstream iss(line);
    int number;
    while (iss >> number) array.push_back(number);

    input.close();

    heapSort(n, array);

    std::filesystem::create_directories("output");
    std::ofstream output(outputPath);

    for (int element: array) std::print(output, "{} ", element);

    output.close();
}