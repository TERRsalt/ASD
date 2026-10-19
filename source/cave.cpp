#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <print>
#include <sstream>

using threeDimensionalVector = std::vector<std::vector<std::vector<char>>>;

//exp // Funkcja `cave` zwraca ilość „zalanych” pól (w finale O) //
static int cave(const int n, const int m, const int d, threeDimensionalVector &caveArray, int &deepestPoint) {
    if (d < 0 || d >= caveArray.size()
            || n < 0 || n >= caveArray[0].size()
            || m < 0 || m >= caveArray[0][0].size()
            || caveArray[d][n][m] == 'x')
        return 0;

    caveArray[d][n][m] = 'x';
    deepestPoint = std::max(deepestPoint, d + 1);

    return 1 + cave(n, m, d - 1, caveArray, deepestPoint) + cave(n, m, d + 1, caveArray, deepestPoint)
            + cave(n - 1, m, d, caveArray, deepestPoint) + cave(n + 1, m, d, caveArray, deepestPoint)
            + cave(n, m - 1, d, caveArray, deepestPoint) + cave(n, m + 1, d, caveArray, deepestPoint);
}

void problem2(const std::string &inputPath, const std::string &outputPath) {
    std::ifstream input(inputPath);

    if (!input.is_open()) {
        std::println("Nie udało się wczytać pliku: „{}”", inputPath);
        return;
    }

    int n, m, d;
    input >> n >> m >> d;

    threeDimensionalVector caveArray(d, std::vector(n, std::vector<char>(m)));
    for (int z = 0; z < d; z++) {for (int y = 0; y < n; y++) {for (int x = 0; x < m; x++) input >> caveArray[z][y][x];}}
    auto caveArrayInDemolition = caveArray;

    input.close();

    int h = 0, o = 0, i = 0;

    for (int currentD = 0; currentD < d; currentD++)
        for (int currentN = 0; currentN < n; currentN++)
            for (int currentM = 0; currentM < m; currentM++)
                if (caveArrayInDemolition[currentD][currentN][currentM] == 'o') {
                    int deepest = 0;
                    int size = cave(currentN, currentM, currentD, caveArrayInDemolition, deepest);

                    o = std::max(o, size);
                    if (currentD == 0) h = std::max(deepest, h);
                    else i++;
                }

    std::ofstream output(outputPath);
    output << h << ' ' << o << ' ' << i << '\n';
    output.close();
}