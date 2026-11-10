#include <algorithm>
#include <filesystem>
#include <fstream>
#include <print>
#include <string>
#include <vector>
#include <sstream>
#include <bit>
#include <bitset>
#include <memory>
#include <ranges>
#include <unordered_map>

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

namespace huffman {
namespace {
struct TreeNode {
    char character;
    int value;
    std::unique_ptr<TreeNode> leftBranch;
    std::unique_ptr<TreeNode> rightBranch;

    explicit TreeNode(const char character = '\0', const int value = 0,
            std::unique_ptr<TreeNode> leftBranch = nullptr, std::unique_ptr<TreeNode> rightBranch = nullptr):
            character(character), value(value), leftBranch(std::move(leftBranch)), rightBranch(std::move(rightBranch)) {}
};
}

using arrayOfCharAndInt = std::vector<std::pair<char, int>>;
using arrayOfTheTreeNodesUniquePointers = std::vector<std::unique_ptr<TreeNode>>;

static void treeLayerGenerator(arrayOfTheTreeNodesUniquePointers &treeNodes) {
    const size_t evenTreeSizeDividedByTwo = treeNodes.size() / 2;

    for (int i = 0; i < evenTreeSizeDividedByTwo; i++) {
        treeNodes.push_back(std::make_unique<TreeNode>('\0', treeNodes[0]->value + treeNodes[1]->value,
                std::move(treeNodes[0]), std::move(treeNodes[1])));

        treeNodes.erase(treeNodes.begin(), treeNodes.begin() + 2);

        std::ranges::stable_sort(treeNodes, [](const auto &a, const auto &b) {return a->value < b->value;});
    }
}

static std::unique_ptr<TreeNode> treeGenerator(const arrayOfCharAndInt &characterOccurrence) {
    const size_t treeSize = characterOccurrence.size();

    arrayOfTheTreeNodesUniquePointers treeNodes;
    for (int i = 0; i < treeSize; i++)
        treeNodes.push_back(std::make_unique<TreeNode>(characterOccurrence[i].first, characterOccurrence[i].second));

    for (int i = 0; i < std::bit_width(treeSize - 1); i++) treeLayerGenerator(treeNodes);

    return std::move(treeNodes[0]);
}

static void codesGenerator(std::unordered_map<char, std::string> &codes, const std::unique_ptr<TreeNode> &treeRoot, const std::string &code = "") {
    if (treeRoot->character != '\0') {
        codes[treeRoot->character] = code;
        return;
    }

    if (treeRoot->leftBranch != nullptr) codesGenerator(codes, treeRoot->leftBranch, code + '0');
    if (treeRoot->rightBranch != nullptr) codesGenerator(codes, treeRoot->rightBranch, code + '1');
}

static std::string huffmanCompression(const std::string &string, arrayOfCharAndInt &firstOccurrence, arrayOfCharAndInt &characterOccurrence,
        std::unordered_map<char, std::string> &codes) {
    if (string.empty()) {
        std::println("Uwaga! Pusta wiadomość!");
        return "";
    }

    std::string codedMessage;

    for (const char character: string) {
        bool found = false;

        for (auto &[key, value]: firstOccurrence) {
            if (key == character) {
                value++;
                found = true;
                break;
            }
        }

        if (!found) firstOccurrence.emplace_back(character, 1);
    }

    characterOccurrence.assign(firstOccurrence.begin(), firstOccurrence.end());
    std::ranges::stable_sort(characterOccurrence, [](const auto &a, const auto &b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    if (characterOccurrence.size() == 1) {
        codes[characterOccurrence[0].first] = '0';
        codedMessage.assign((string.size() + 7) / 8, '\0');
        return codedMessage;
    }

    const std::unique_ptr<TreeNode> treeRoot = treeGenerator(characterOccurrence);

    codesGenerator(codes, treeRoot);

    std::string fullStringCode;
    for (const char character: string) fullStringCode += codes[character];
    const size_t missingZeros = (8 - fullStringCode.size() % 8) % 8;
    for (int i = 0; i < missingZeros; i++) fullStringCode += '0';

    const size_t sizeOfTheFullCode = fullStringCode.size();
    for (int i = 0; i < sizeOfTheFullCode; i += 8) {
        const char compressedCharacter = static_cast<char>(std::stoi(fullStringCode.substr(i, 8), nullptr, 2));
        codedMessage += compressedCharacter;
    }

    return codedMessage;
}

void problem8(const std::string &inputPath, const std::string &outputPath, const std::string &decompressionInputPath) {
    std::ifstream input(inputPath);

    if (!input.is_open()) {
        std::println("Nie udało się wczytać pliku: „{}”", inputPath);
        return;
    }

    std::string string;
    getline(input, string);

    input.close();

    arrayOfCharAndInt firstOccurrence;
    arrayOfCharAndInt characterOccurrence;
    std::unordered_map<char, std::string> codes;
    std::string codedMessage = huffmanCompression(string, firstOccurrence, characterOccurrence, codes);

    std::filesystem::create_directories("output");
    std::ofstream output(outputPath);

    int i = 0;
    for (const auto &[character, value]: firstOccurrence) {
        i++;
        if (i < firstOccurrence.size()) std::print(output, "{} {}, ", character, value);
        else std::println(output, "{} {}", character, value);
    }

    i = 0;
    for (const auto &[character, value]: characterOccurrence) {
        i++;
        if (i < characterOccurrence.size()) std::print(output, "{} {}, ", character, value);
        else std::println(output, "{} {}", character, value);
    }

    i = 0;
    for (const auto &[character, code]: codes) {
        i++;
        if (i < codes.size()) std::print(output, "{}={}, ", code, character);
        else std::println(output, "{}={}", code, character);
    }

    std::println(output, "////////////////////////////////////////////");

    std::ofstream decompressionInput(decompressionInputPath);

    i = 0;
    for (const auto &[character, value]: firstOccurrence) {
        i++;
        if (i < firstOccurrence.size()) {
            std::print(output, "{}-{} ", character, value);
            std::print(decompressionInput, "{}-{} ", character, value);
        }
        else {
            std::println(output, "{}-{}", character, value);
            std::println(decompressionInput, "{}-{}", character, value);
        }
    }

    std::print(output, "{}", codedMessage);
    std::print(decompressionInput, "{}", codedMessage);

    decompressionInput.close();
    output.close();
}

static void huffmanDecompression(arrayOfCharAndInt &characterOccurrence, const std::string &codedMessage, std::string &decodedMessage) {
    if (characterOccurrence.empty()) {
        std::println("Uwaga! Pusta wiadomość!");
        return;
    }

    std::ranges::sort(characterOccurrence, [](const auto &a, const auto &b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    size_t sizeOfDecodedMessage = 0;
    for (const int value: characterOccurrence | std::views::values) sizeOfDecodedMessage += value;


    if (characterOccurrence.size() == 1) {
        decodedMessage.assign(characterOccurrence[0].second, characterOccurrence[0].first);
        return;
    }

    const std::unique_ptr<TreeNode> treeRoot = treeGenerator(characterOccurrence);

    std::unordered_map<char, std::string> codes;
    std::unordered_map<char, int> codesDecimal;
    codesGenerator(codes, treeRoot);

    std::string binaryCode;
    for (const char character: codedMessage) {
        const int decimalCharacter = static_cast<unsigned char>(character);
        binaryCode += std::bitset<8>(decimalCharacter).to_string();
    }

    const TreeNode *pointer = treeRoot.get();
    int i = 0;
    for (const char byte: binaryCode) {
        if (byte == '0') pointer = pointer->leftBranch.get();
        else pointer = pointer->rightBranch.get();

        if (pointer->character != '\0') {
            decodedMessage += pointer->character;
            pointer = treeRoot.get();

            i++;
            if (i == sizeOfDecodedMessage) break;
        }
    }
}

void problem8b(const std::string &inputPath, const std::string &outputPath) {
    std::ifstream input(inputPath);

    if (!input.is_open()) {
        std::println("Nie udało się wczytać pliku: „{}”", inputPath);
        return;
    }

    std::string characterOccurrenceString, codedMessage;
    getline(input, characterOccurrenceString);
    getline(input, codedMessage);

    input.close();

    arrayOfCharAndInt firstOccurrence;
    size_t i = 0;
    while (i + 2 < characterOccurrenceString.size()) {
        const char character = characterOccurrenceString[i];

        const size_t end = characterOccurrenceString.find(' ', i + 2);
        const std::string number = characterOccurrenceString.substr(i + 2, end - (i + 2));

        firstOccurrence.emplace_back(character, static_cast<int>(std::stoul(number)));

        if (end == std::string::npos) break;
        i = end + 1;
    }

    std::string decodedMessage;
    huffmanDecompression(firstOccurrence, codedMessage, decodedMessage);

    std::filesystem::create_directories("output");
    std::ofstream output(outputPath);

    std::print(output, "{}", decodedMessage);

    output.close();
}
}

int main() {
    flower::problem1("input/In0301.txt", "output/Out0301.txt");

    huffman::problem8("input/In0305.txt", "output/Out0305.txt", "input/Huff.txt");
    huffman::problem8b("input/Huff.txt", "output/Huff.txt");

    std::println("Program przeszedł poprawnie przez wszystkie problemy! ^-^");

    return 0;
}