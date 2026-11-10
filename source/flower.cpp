#include "flower.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <print>
#include <string>
#include <vector>
#include <sstream>

namespace flower {
static std::vector<std::vector<int>> crossbreedingTableGenerator(const std::vector<char> &geneX, const std::vector<char> &geneY) {
    const size_t sizeOfGeneX = geneX.size() + 1;
    const size_t sizeOfGeneY = geneY.size() + 1;

    std::vector crossbreedingTable(sizeOfGeneY, std::vector(sizeOfGeneX, 0));

    for (int y = 1; y < sizeOfGeneY; y++) {
        for (int x = 1; x < sizeOfGeneX; x++) {
            if (geneY[y - 1] == geneX[x - 1]) crossbreedingTable[y][x] = crossbreedingTable[y - 1][x - 1] + 1;

            else {
                if (crossbreedingTable[y - 1][x] > crossbreedingTable[y][x - 1]) crossbreedingTable[y][x] = crossbreedingTable[y - 1][x];
                else crossbreedingTable[y][x] = crossbreedingTable[y][x - 1];
            }
        }
    }

    return crossbreedingTable;
}

static std::string crossbreeding(const std::vector<char> &geneX, const std::vector<char> &geneY) {
    const std::vector<std::vector<int>> crossbreedingTable = crossbreedingTableGenerator(geneX, geneY);

    std::string exampleGene;
    size_t y = geneY.size(), x = geneX.size();
    do {
        if (geneY[y - 1] == geneX[x - 1]) {
            exampleGene += geneY[y - 1];
            y--;
            x--;
        }

        else {
            if (crossbreedingTable[y - 1][x] >= crossbreedingTable[y][x - 1]) y--;
            else x--;
        }
    } while (y != 0 && x != 0);

    std::ranges::reverse(exampleGene);
    return exampleGene;
}

static std::vector<std::string> crossbreedingAllFlowers(const int n, const std::vector<std::vector<char>> &genes) {
    std::vector<std::string> crossbredFlowers;

    if (n == 0 || genes.size() != n * 2) {
        std::println("Błędne dane wejściowe!");
        return crossbredFlowers;
    }

    for (int i = 0; i < n; i++) {
        const auto &geneX = genes[i * 2];
        const auto &geneY = genes[i * 2 + 1];
        crossbredFlowers.emplace_back(crossbreeding(geneX, geneY));
    }

    return crossbredFlowers;
}

void problem1(const std::string &inputPath, const std::string &outputPath) {
    std::ifstream input(inputPath);

    if (!input.is_open()) {
        std::println("Nie udało się wczytać pliku: „{}”", inputPath);
        return;
    }

    std::string line;
    getline(input, line);
    const int n = std::stoi(line);

    std::vector<std::vector<char>> genes;
    int i = 0;
    while (i < n * 2 && getline(input, line)) {
        std::istringstream iss(line);
        char character;
        genes.emplace_back();
        while (iss >> character) genes[i].push_back(character);
        i++;
    }

    input.close();

    std::filesystem::create_directories("output");
    std::ofstream output(outputPath);

    for (const std::string &flower: crossbreedingAllFlowers(n, genes)) {
        std::print(output, "{} ", flower.size());
        std::println(output, "{}", flower);
    }

    output.close();
}
}