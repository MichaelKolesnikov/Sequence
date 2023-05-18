#pragma once

#include <ctime>
#include "ArraySequence.h"

template<class T>
class PermutationGenerator {
private:
    ArraySequence<T> sequence;
public:
    PermutationGenerator(ArraySequence<T>& arr) : sequence(arr) {
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
    }

    ArraySequence<T>* generate_permutation() {
        ArraySequence<T>* permutation = new ArraySequence<T>(sequence);

        for (int i = permutation->get_length() - 1; i > 0; --i) {
            int j = rand() % (i + 1);

            T temp = permutation->get(i);
            permutation->operator[](i) = permutation->get(j);
            permutation->operator[](j) = temp;
        }

        return permutation;
    }
};

