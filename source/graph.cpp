#include <print>
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

void problem6() {
    constexpr int n = 8;
    const std::vector<std::vector<int>> adjacencyList = {
        {2, 4, 5, 6},
        {1, 3, 4, 8},
        {2, 8},
        {1, 2, 6, 8},
        {1, 6},
        {1, 4, 5, 7, 8},
        {6, 8},
        {2, 3, 4, 6, 7}
    };
    std::vector<int> steps;
    bool graphValue = graph(n, adjacencyList, steps);
    if (graphValue && n != steps.size()) graphValue = false;

    std::println("{}", graphValue);
    for (int step: steps) std::print("{} ", step);
}