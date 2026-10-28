#include <algorithm>
#include <filesystem>
#include <vector>
#include <print>
#include <string>
#include <fstream>
#include <sstream>

static bool binarySearch(const std::vector<int> &set, int beginningOfTheSet, int endOfTheSet, const int searchedNumber) {
    const int n = endOfTheSet - beginningOfTheSet + 1;

    if (n <= 0) return false;
    if (n == 1) return searchedNumber == set[beginningOfTheSet];

    const int middleOfTheSet = beginningOfTheSet + n / 2;
    if (searchedNumber < set[middleOfTheSet]) endOfTheSet = middleOfTheSet - 1;
    else beginningOfTheSet = middleOfTheSet;

    return binarySearch(set, beginningOfTheSet, endOfTheSet, searchedNumber);
}

static void intersection(const int n, const std::vector<int> &set1, const std::vector<int> &set2, std::vector<int> &intersectedNumbers) {
    for (const int searchedNumber: set1) {
        if (binarySearch(set2, 0, n - 1, searchedNumber)) intersectedNumbers.push_back(searchedNumber);
    }

    std::ranges::sort(intersectedNumbers); //exp // `ranges::sort` ma w najgorszym przypadku złożoność czasową n*log(n) //
    //exp // `unique` + `erase` ma złożoność czasową n //
    const auto [firstNotUniqueNumber, lastNotUniqueNumber] = std::ranges::unique(intersectedNumbers);
    intersectedNumbers.erase(firstNotUniqueNumber, lastNotUniqueNumber);
}

void problem8(const std::string &inputPath, const std::string &outputPath) {
    std::ifstream input(inputPath);

    if (!input.is_open()) {
        std::println("Nie udało się wczytać pliku: „{}”", inputPath);
        return;
    }

    std::string line;
    getline(input, line);
    int n = std::stoi(line);

    std::vector<int> set1, set2;
    int lineIndex = 0;
    while (lineIndex < 2 && getline(input, line)) {
        std::istringstream iss(line);

        int number;
        while (iss >> number) {
            if (lineIndex == 0) set1.push_back(number);
            else set2.push_back(number);
        }

        lineIndex++;
    }

    input.close();

    std::vector<int> intersectedNumbers;
    intersection(n, set1, set2, intersectedNumbers);
    const auto numberOfIntersectedNumbers = intersectedNumbers.size();

    std::filesystem::create_directories("output");
    std::ofstream output(outputPath);

    for (int number: intersectedNumbers) std::print(output, "{} ", number);
    std::println(output, "\n{}", numberOfIntersectedNumbers);

    output.close();
}