#include <print>

#include "flower.hpp"
#include "huffman.hpp"

int main() {
    flower::problem1("input/In0301.txt", "output/Out0301.txt");

    huffman::problem8("input/In0305.txt", "output/Out0305.txt", "input/Huff.txt");
    huffman::problem8b("input/Huff.txt", "output/Huff.txt");

    std::println("Program przeszedł poprawnie przez wszystkie problemy! ^-^");

    return 0;
}