#include <fstream>
#include <vector>
#include <print>
#include <format>
#include <sstream>

//exp // `n` to szerokość korytarza, a `m` to liczba prętów //
static void bajtdocjaSafe(const int n, const int m, const std::vector<int> &coordinates, std::vector<std::string> &output, int &numberOfFreeShots) {
    std::vector<int> y1Coordinates, y2Coordinates;
    for (int i = 1; i < m * 4; i += 4) y1Coordinates.push_back(coordinates[i]);
    for (int i = 3; i < m * 4; i += 4) y2Coordinates.push_back(coordinates[i]);

    for (int i = 0; i < m; i++) {
        if (y1Coordinates[i] > y2Coordinates[i]) {
            int temporary = y1Coordinates[i];
            y1Coordinates[i] = y2Coordinates[i];
            y2Coordinates[i] = temporary;
        }
    }

    //exp // To sprawdza czy na tym indeksie się zaczyna się pręt i jeśli się zaczyna wypisuje gdzie się kończy, inaczej -1 //
    std::vector<int> rodLengths(n + 1, -1);
    for (int i = 0; i < m; i++) rodLengths[y1Coordinates[i]] = std::max(rodLengths[y1Coordinates[i]], y2Coordinates[i]);

    int startOfFreeShoot = 0;
    for (int i = 0; i <= n; i++) {
        if (rodLengths[i] != -1) {
            if (i > startOfFreeShoot) {
                output.push_back(std::format("{} {}", startOfFreeShoot, i));
                numberOfFreeShots++;
            }

            startOfFreeShoot = std::max(startOfFreeShoot, rodLengths[i]);
        }
    }

    if (startOfFreeShoot < n) {
        output.push_back(std::format("{} {}", startOfFreeShoot, n));
        numberOfFreeShots++;
    }
}

void problem4(const std::string &inputPath, const std::string &outputPath) {
    std::ifstream input(inputPath);

    if (!input.is_open()) {
        std::println("Nie udało się wczytać pliku: „{}”", inputPath);
        return;
    }

    std::string firstLine;
    getline(input, firstLine);
    auto space = firstLine.find(' ');
    int n = std::stoi(firstLine.substr(0, space));
    int m = std::stoi(firstLine.substr(space + 1));

    std::string line;
    std::vector<int> coordinates;
    int howManyLines = m;
    while (getline(input, line) && howManyLines != 0) {
        std::istringstream iss(line);
        int x1, y1, x2, y2;
        iss >> x1 >> y1 >> x2 >> y2;
        coordinates.push_back(x1);
        coordinates.push_back(y1);
        coordinates.push_back(x2);
        coordinates.push_back(y2);
        howManyLines--;
    }

    input.close();

    int numberOfFreeShots = 0;
    std::vector<std::string> outputData;
    bajtdocjaSafe(n, m, coordinates, outputData, numberOfFreeShots);

    std::ofstream output(outputPath);

    auto outputDataSize = outputData.size();
    for (int i = 0; i < outputDataSize; i++) std::println(output, "{}", outputData[i]);
    std::println(output, "liczba bezpiecznych pasm: {}", numberOfFreeShots);

    output.close();
}