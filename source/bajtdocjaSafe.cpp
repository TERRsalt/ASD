#include <vector>
#include <print>

//exp // `n` to szerokość korytarza, a `m` to liczba prętów //
void bajtdocjaSafe(const int n, const int m, const std::vector<int> &coordinates) {
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

    int startOfFreeShoot = 0, numberOfFreeShots = 0;
    for (int i = 0; i <= n; i++) {
        if (rodLengths[i] != -1) {
            if (i > startOfFreeShoot) {
                std::println("{} {}", startOfFreeShoot, i);
                numberOfFreeShots++;
            }

            startOfFreeShoot = std::max(startOfFreeShoot, rodLengths[i]);
        }
    }

    if (startOfFreeShoot < n) {
        std::println("{} {}", startOfFreeShoot, n);
        numberOfFreeShots++;
    }

    std::println("Liczba bezpiecznych pasm: {}", numberOfFreeShots);
}