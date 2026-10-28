#include <print>

#include "heapSort.hpp"
#include "cave.hpp"
#include "graph.hpp"
#include "intersection.hpp"

int main() {
    problem1C("input/In0201.txt", "output/Out0201.txt");
    problem2("input/In0202.txt", "output/Out0202.txt");
    problem6("input/In0206.txt", "output/Out0206.txt");
    problem8("input/In0208.txt", "output/Out0208.txt");

    std::println("Program przeszedł poprawnie przez wszystkie problemy! ^-^");

    return 0;
}