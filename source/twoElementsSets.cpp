#include <fstream>
#include <vector>
#include <print>
#include <format>

static void twoElementsSets(const int n, const int k, const std::vector<int> &numbers, std::vector<std::string> &output, int &numberOfSets) {
    std::vector<bool> presentVector(k + 1, false);
    for (int number: numbers) presentVector[number] = true;

    std::vector<int> sortedNumbers;
    for (int i = 1; i <= k; i++)
        if (presentVector[i]) sortedNumbers.push_back(i);

    int smallestNumberIndex = 0, biggestNumberIndex = n - 1;
    while (smallestNumberIndex < biggestNumberIndex) {
        int smallestNumber = sortedNumbers[smallestNumberIndex], biggestNumber = sortedNumbers[biggestNumberIndex];

        if (smallestNumber + biggestNumber <= k) {
            output.push_back(std::format("{} {}", smallestNumber, biggestNumber));

            smallestNumberIndex++;
            biggestNumberIndex--;
            numberOfSets++;
        }

        else {
            output.push_back(std::format("{}", biggestNumber));

            biggestNumberIndex--;
            numberOfSets++;
        }
    }

    if (smallestNumberIndex == biggestNumberIndex) {
        output.push_back(std::format("{}", sortedNumbers[biggestNumberIndex]));
        numberOfSets++;
    }
}

void problem2(const std::string &inputPath, const std::string &outputPath) {
    std::ifstream input(inputPath);

    if (!input.is_open()) {
        std::println("Nie udało się wczytać pliku: „{}”", inputPath);
        return;
    }

    std::string firstLine;
    getline(input, firstLine);
    auto space = firstLine.find(' ');
    int n = std::stoi(firstLine.substr(0, space));
    int k = std::stoi(firstLine.substr(space + 1));

    std::string line;
    std::vector<int> numbers;
    int howManyNumbers = n;
    while (getline(input, line) && howManyNumbers != 0) {
        numbers.push_back(std::stoi(line));
        howManyNumbers--;
    }

    input.close();

    int numberOfSets = 0;
    std::vector<std::string> outputData;
    twoElementsSets(n, k, numbers, outputData, numberOfSets);

    std::ofstream output(outputPath);

    auto outputDataSize = outputData.size();
    for (int i = 0; i < outputDataSize; i++) std::println(output, "{}", outputData[i]);
    std::println(output, "{}", numberOfSets);

    output.close();
}