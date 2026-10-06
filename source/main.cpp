#include <print>
#include <vector>

#include "bajtdocjaSafe.hpp"

int main() {
    const std::vector<int> numbers = {2, 5, 2, 6, 4, 1, 4, 4, 4, 10, 10, 10, 1, 6, 5, 9, 3, 8, 7, 9};
    bajtdocjaSafe(11, 5, numbers);

    return 0;
}