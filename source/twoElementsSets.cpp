#include <vector>
#include <print>

void twoElementsSets(const int n, const int k, const std::vector<int> &numbers) {
    std::vector<bool> presentVector(k + 1, false);
    for (int number: numbers) presentVector[number] = true;

    std::vector<int> sortedNumbers;
    for (int i = 1; i <= k; i++)
        if (presentVector[i]) sortedNumbers.push_back(i);

    int smallestNumberIndex = 0, biggestNumberIndex = n - 1, numberOfSets = 0;
    while (smallestNumberIndex < biggestNumberIndex) {
        int smallestNumber = sortedNumbers[smallestNumberIndex], biggestNumber = sortedNumbers[biggestNumberIndex];

        if (smallestNumber + biggestNumber <= k) {
            std::println("{} {}", smallestNumber, biggestNumber);

            smallestNumberIndex++;
            biggestNumberIndex--;
            numberOfSets++;
        }

        else {
            std::println("{}", biggestNumber);

            biggestNumberIndex--;
            numberOfSets++;
        }
    }

    if (smallestNumberIndex == biggestNumberIndex) {
        std::println("{}", sortedNumbers[biggestNumberIndex]);
        numberOfSets++;
    }

    std::println("{}", numberOfSets);
}