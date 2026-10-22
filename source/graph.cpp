#include <filesystem>
#include <fstream>
#include <print>
#include <sstream>
#include <vector>

static bool graph(const int n, const std::vector<std::vector<int>> &adjacencyList, std::vector<int> &steps) {
    if (adjacencyList.empty()) return false;

    static std::vector checkedElements(n, false);
    static int searchedElement = 1;

    steps.push_back(searchedElement);
    checkedElements[searchedElement - 1] = true;

    for (const int element: adjacencyList[searchedElement - 1]) {
        if (!checkedElements[element - 1]) {
            searchedElement = element;
            graph(n, adjacencyList, steps);
        }
    }

    return steps.size() == n;
}

void problem6(const std::string &inputPath, const std::string &outputPath) {
    std::ifstream input(inputPath);

    if (!input.is_open()) {
        std::println("Nie udało się wczytać pliku: „{}”", inputPath);
        return;
    }

    std::string line;
    getline(input, line);
    int n = std::stoi(line);

    std::vector adjacencyList(n, std::vector<int>(0));
    int lineIndex = 0;
    while (getline(input, line) && lineIndex < n) {
        std::istringstream iss(line);
        int number;
        while (iss >> number) adjacencyList[lineIndex].push_back(number);
        lineIndex++;
    }

    input.close();

    std::vector<int> steps;
    bool graphValue = graph(n, adjacencyList, steps);
    if (graphValue && n != steps.size()) graphValue = false;

    std::filesystem::create_directories("output");
    std::ofstream output(outputPath);

    if (graphValue) std::println(output, "Graf spójny");
    else std::println(output, "Graf niespójny");
    for (int step: steps) std::print(output, "{} ", step);

    output.close();
}