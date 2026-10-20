#include <print>
#include <vector>

//todo // Zmienić to, żeby działało przeszukaniem w głąb //
static int graph(const int n, const std::vector<std::vector<int>> &adjacencyList, std::vector<int> &steps) {
    if (adjacencyList.empty()) return -1;

    static std::vector checkedElements(n, false);
    static int searchedElement = 1;

    steps.push_back(searchedElement);
    checkedElements[searchedElement - 1] = true;

    std::vector<int> notCheckedElements;
    for (int element: adjacencyList[searchedElement - 1]) if (!checkedElements[element - 1]) notCheckedElements.push_back(element);
    if (notCheckedElements.empty()) {
        for (int i = 0; i < checkedElements.size(); i++)
            if (!adjacencyList[i].empty() && !checkedElements[i] && checkedElements[adjacencyList[i][0] - 1])
                steps.push_back(i + 1);
        return -1;
    }
    searchedElement = *std::min_element(notCheckedElements.begin(), notCheckedElements.end());

    return graph(n, adjacencyList, steps);
}

static std::vector<std::vector<int>> adjList = {
    {2, 4, 5, 6},
    {1, 3, 4, 8},
    {2, 8},
    {1, 2, 6, 8},
    {1, 6},
    {1, 4, 5, 7, 8},
    {6, 8},
    {2, 3, 4, 6, 7}
};

static std::vector<std::vector<int>> adjListFalse = {
    {2, 4, 5, 6},
    {1, 4, 8},
    {7},
    {1, 2, 6, 8},
    {1, 6},
    {1, 4, 5, 8},
    {3},
    {2, 4, 6}
};

static std::vector<std::vector<int>> adjListAi1 = {
    {2, 3, 4},
    {1},
    {},
    {1}
};
static std::vector<std::vector<int>> adjListAi2 = {{2}, {1}, {4}, {3}};
std::vector<int> stepsss;

void problem6() {
    constexpr int n = 4;
    graph(n, adjListAi1, stepsss);
    if (stepsss.size() != n) std::println("false"); else std::println("true");
    for (int i = 0; i < stepsss.size(); i++) std::print("{} ", stepsss[i]);
}