#include "LinkedListContainer.h"
#include "SequentialContainer.h"
#include "TestContainer.h"
#include <iostream>

int main() {
    // Последовательный контейнер
    SequentialContainer<int> seq;
    // Списковый контейнер
    LinkedListContainer<int> lnk;

    std::cout << "Последовательный контейнер" << std::endl;
    test_container(seq);
    std::cout << "Списковый контейнер" << std::endl;
    test_container(lnk);

    // std::cin.get();
    
    return 0;
}
