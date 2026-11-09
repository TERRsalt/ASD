#include <print>
#include <string>
#include <map>
#include <vector>

using arrayOfCharAndUnsignedInt = std::vector<std::pair<char, unsigned int>>;

struct TreeNode {
    char character{};
    unsigned int value{};
    TreeNode *leftBranch = nullptr;
    TreeNode *rightBranch = nullptr;

    TreeNode(const char character, const unsigned int value): character(character), value(value) {}
    TreeNode(const char character, const unsigned int value, TreeNode *leftBranch, TreeNode *rightBranch):
            character(character), value(value), leftBranch(leftBranch), rightBranch(rightBranch) {}
};

static void constructATree(const arrayOfCharAndUnsignedInt &wordOccurrence) {
    const unsigned int wordOccurrenceSize = wordOccurrence.size();
    const unsigned int evenWordOccurrenceSize = wordOccurrenceSize / 2;

    const unsigned int numberOfBytesNeededToWriteANumber = std::bit_width(wordOccurrenceSize - 1);

    std::vector<TreeNode> treeNodes;
    treeNodes.reserve(wordOccurrenceSize);
    for (int i = 0; i < wordOccurrenceSize; i++) treeNodes.emplace_back(wordOccurrence[i].first, wordOccurrence[i].second);

    std::vector<TreeNode> newTreeNodes;
    newTreeNodes.reserve(evenWordOccurrenceSize);
    for (int i = 0; i < evenWordOccurrenceSize; i++)
        newTreeNodes.emplace_back('\0', treeNodes[i * 2].value + treeNodes[i * 2 + 1].value,
                &treeNodes[i * 2], &treeNodes[i * 2 + 1]);
    if (wordOccurrenceSize % 2 == 0) newTreeNodes.emplace_back(treeNodes[wordOccurrenceSize - 1].character, treeNodes[wordOccurrenceSize - 1].value);
    treeNodes = {};

    //todo // Dokończ tą funkcję. Przeszedłeś przez 2 warstwy i teraz będzie to po prostu pętla. (...) //
    //todo // (...) Sprawdź ile warstw będzie to miało i przez tyle przejdź, do zbudowania pełnego drzewa. //
}

static void huffmanCompression(const std::string &word) {
    std::map<char, unsigned int> wordMap = {};
    for (char character: word) {
        if (!wordMap.contains(character)) wordMap[character] = 1;
        else wordMap[character] += 1;
    }

    arrayOfCharAndUnsignedInt wordOccurrence(wordMap.begin(), wordMap.end());
    std::sort(wordOccurrence.begin(), wordOccurrence.end(), [](const auto &a, const auto &b) {
        if (a.second != b.second) return a.second < b.second;
        return false;
    });

    const unsigned int wordOccurrenceSize = wordOccurrence.size();
    unsigned int wordDivider = wordOccurrenceSize / 2;

    // for (int i = 0; i < wordOccurrenceSize; i++) std::println("{} -> {}", wordOccurrence[i].first, wordOccurrence[i].second);
    // std::println("{}, {}", wordOccurrenceSize, wordDivider);
    // std::println("{} -> {}", wordOccurrence[wordDivider].first, wordOccurrence[wordDivider].second);
}

void problem8(const std::string &inputPath, const std::string &outputPath) {
    const std::string word = "ALA_MA_KOTA";

    huffmanCompression(word);
}