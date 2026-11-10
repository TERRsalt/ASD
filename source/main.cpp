#include <print>

#include "huffman.hpp"

int main() {
    huffman::problem8("input/In0305.txt", "output/Out0305.txt", "input/Huff.txt");
    huffman::problem8b("input/Huff.txt", "output/Huff.txt");

    std::println("Program przeszedł poprawnie przez wszystkie problemy! ^-^");

    return 0;
}