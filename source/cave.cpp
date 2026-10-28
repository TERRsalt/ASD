#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <filesystem>
#include <print>
#include <sstream>

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