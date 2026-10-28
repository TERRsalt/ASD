#include <filesystem>
#include <fstream>
#include <vector>
#include <print>
#include <sstream>
#include <string>
#include <algorithm>

//info // Problem 1c //

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

//info // Problem 2 //

using threeDimensionalCharVector = std::vector<std::vector<std::vector<char>>>;

//exp // Funkcja `cave` zwraca ilość „zalanych” pól (w finale O) //
static int caveFloodFill(const int n, const int m, const int d, threeDimensionalCharVector &caveArray, int &deepestPoint) {
    if (d < 0 || d >= caveArray.size()
            || n < 0 || n >= caveArray[0].size()
            || m < 0 || m >= caveArray[0][0].size()
            || caveArray[d][n][m] == 'x')
        return 0;

    caveArray[d][n][m] = 'x';
    deepestPoint = std::max(deepestPoint, d + 1);

    return 1 + caveFloodFill(n, m, d - 1, caveArray, deepestPoint) + caveFloodFill(n, m, d + 1, caveArray, deepestPoint)
            + caveFloodFill(n - 1, m, d, caveArray, deepestPoint) + caveFloodFill(n + 1, m, d, caveArray, deepestPoint)
            + caveFloodFill(n, m - 1, d, caveArray, deepestPoint) + caveFloodFill(n, m + 1, d, caveArray, deepestPoint);
}

static void cave(const threeDimensionalCharVector &caveArray, const int n, const int m, const int d, int &h, int &o, int &i) {
    auto caveArrayInDemolition = caveArray;

    for (int currentD = 0; currentD < d; currentD++)
        for (int currentN = 0; currentN < n; currentN++)
            for (int currentM = 0; currentM < m; currentM++)
                if (caveArrayInDemolition[currentD][currentN][currentM] == 'o') {
                    int deepest = 0;
                    int size = caveFloodFill(currentN, currentM, currentD, caveArrayInDemolition, deepest);

                    o = std::max(o, size);
                    if (currentD == 0) h = std::max(deepest, h);
                    else i++;
                }
}

void problem2(const std::string &inputPath, const std::string &outputPath) {
    std::ifstream input(inputPath);

    if (!input.is_open()) {
        std::println("Nie udało się wczytać pliku: „{}”", inputPath);
        return;
    }

    int n, m, d;
    input >> n >> m >> d;

    threeDimensionalCharVector caveArray(d, std::vector(n, std::vector<char>(m)));
    for (int z = 0; z < d; z++) {for (int y = 0; y < n; y++) {for (int x = 0; x < m; x++) input >> caveArray[z][y][x];}}

    input.close();

    int h = 0, o = 0, i = 0;
    cave(caveArray, n, m, d, h, o, i);

    std::filesystem::create_directories("output");
    std::ofstream output(outputPath);
    std::println(output, "{} {} {}", h, o, i);
    output.close();
}

//info // Problem 6 //

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

//info // Problem 8 //

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

//info // `int main()` //

int main() {
    problem1C("input/In0201.txt", "output/Out0201.txt");
    problem2("input/In0202.txt", "output/Out0202.txt");
    problem6("input/In0206.txt", "output/Out0206.txt");
    problem8("input/In0208.txt", "output/Out0208.txt");

    std::println("Program przeszedł poprawnie przez wszystkie problemy! ^-^");

    return 0;
}