#include "huffman.hpp"

#include <algorithm>
#include <bit>
#include <filesystem>
#include <fstream>
#include <print>
#include <string>
#include <map>
#include <memory>
#include <unordered_map>
#include <vector>

namespace huffman {
namespace {
struct TreeNode {
    char character;
    unsigned value;
    std::unique_ptr<TreeNode> leftBranch;
    std::unique_ptr<TreeNode> rightBranch;

    explicit TreeNode(const char character = '\0', const unsigned value = 0,
    std::unique_ptr<TreeNode> leftBranch = nullptr, std::unique_ptr<TreeNode> rightBranch = nullptr):
    character(character), value(value), leftBranch(std::move(leftBranch)), rightBranch(std::move(rightBranch)) {}
};
}

using arrayOfCharAndUnsigned = std::vector<std::pair<char, unsigned>>;
using arrayOfTheTreeNodesUniquePointers = std::vector<std::unique_ptr<struct TreeNode>>;

static void treeLayerGenerator(arrayOfTheTreeNodesUniquePointers &treeNodes, arrayOfTheTreeNodesUniquePointers &newTreeNodes) {
    const unsigned treeSize = treeNodes.size();
    const unsigned evenTreeSizeDividedByTwo = treeSize / 2;

    newTreeNodes.reserve(evenTreeSizeDividedByTwo + 1);

    for (unsigned i = 0; i < evenTreeSizeDividedByTwo; i++)
        newTreeNodes.push_back(std::make_unique<TreeNode>('\0', treeNodes[i * 2]->value + treeNodes[i * 2 + 1]->value,
                std::move(treeNodes[i * 2]), std::move(treeNodes[i * 2 + 1])));

    if (treeSize % 2 != 0) newTreeNodes.push_back(std::move(treeNodes[treeSize - 1]));

    treeNodes.clear();
}

static std::unique_ptr<TreeNode> treeGenerator(const arrayOfCharAndUnsigned &characterOccurrence) {
    const unsigned treeSize = characterOccurrence.size();

    arrayOfTheTreeNodesUniquePointers treeNodes;
    treeNodes.reserve(treeSize);
    for (unsigned i = 0; i < treeSize; i++)
        treeNodes.push_back(std::make_unique<TreeNode>(characterOccurrence[i].first, characterOccurrence[i].second));

    const unsigned numberOfBytesNeededToWriteANumber = std::bit_width(treeSize - 1);
    unsigned numberOfLayers = 0;

    arrayOfTheTreeNodesUniquePointers newTreeNodes;
    bool isTheLayerEven = true;
    while (numberOfLayers != numberOfBytesNeededToWriteANumber) {
        if (isTheLayerEven) treeLayerGenerator(treeNodes, newTreeNodes);
        else treeLayerGenerator(newTreeNodes, treeNodes);

        isTheLayerEven = !isTheLayerEven;
        numberOfLayers++;
    }

    if (isTheLayerEven) return std::move(treeNodes[0]);
    return std::move(newTreeNodes[0]);
}

static void codesGenerator(std::unordered_map<char, std::string> &codes, const std::unique_ptr<TreeNode> &treeRoot, const std::string &code = "") {
    if (treeRoot->character != '\0') {
        codes[treeRoot->character] = code;
        return;
    }

    if (treeRoot->leftBranch != nullptr) codesGenerator(codes, treeRoot->leftBranch, code + '0');
    if (treeRoot->rightBranch != nullptr) codesGenerator(codes, treeRoot->rightBranch, code + '1');
}

static void huffmanCompression(const std::string &string, std::string &compressedString) {
    std::map<char, unsigned> characterMap;
    for (char character: string) {
        if (!characterMap.contains(character)) characterMap[character] = 1;
        else characterMap[character] += 1;
    }

    arrayOfCharAndUnsigned characterOccurrence(characterMap.begin(), characterMap.end());
    std::ranges::sort(characterOccurrence, [](const auto &a, const auto &b) {
        if (a.second != b.second) return a.second < b.second;
        return false;
    });

    const std::unique_ptr<TreeNode> treeRoot = treeGenerator(characterOccurrence);

    std::unordered_map<char, std::string> codes;
    codesGenerator(codes, treeRoot);

    std::string fullStringCode;
    for (char character: string) fullStringCode += codes[character];
    const unsigned missingZeros = 8 - fullStringCode.size() % 8;
    for (unsigned i = 0; i < missingZeros; i++) fullStringCode += '0';

    const unsigned sizeOfTheFullCode = fullStringCode.size();
    for (unsigned i = 0; i < sizeOfTheFullCode; i += 8) {
        const char compressedCharacter = static_cast<char>(std::stoi(fullStringCode.substr(i, 8), nullptr, 2));
        compressedString += compressedCharacter;
    }
}

void problem8(const std::string &inputPath, const std::string &outputPath) {
    std::ifstream input(inputPath);

    if (!input.is_open()) {
        std::println("Nie udało się wczytać pliku: „{}”", inputPath);
        return;
    }

    std::string string, compressedString;
    getline(input, string);

    input.close();

    huffmanCompression(string, compressedString);

    std::filesystem::create_directories("output");
    std::ofstream output(outputPath);

    std::println(output, "{}", compressedString);

    output.close();
}
}