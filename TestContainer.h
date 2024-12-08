#ifndef TEST_CONTAINER_H
#define TEST_CONTAINER_H

#include <iostream>

template <typename Container>
void print_container(const Container& container) {
    for (auto it = container.begin(); it != container.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl; 
}
template <typename Container>
void test_container(Container& container) {
    // 2. Добавление в контейнер десяти элементов (0, 1 … 9)
    for (int i = 0; i < 10; ++i) {
        container.push_back(i);
    }
    
    // 3. Вывод содержимого контейнера на экран.
    print_container(container);
    
    // 4. Вывод размера контейнера на экран
    std::cout << "Size: " << container.size() << std::endl;
    
    // 5. Удаление третьего (по счёту), пятого и седьмого элементов
    container.erase(2);
    container.erase(3);  // Обратите внимание, что после предыдущего удаления индексы смещаются
    container.erase(4);
    
    // 6. Вывод содержимого контейнера на экран
    print_container(container);
    
    // 7. Добавление элемента 10 в начало контейнера
    container.push_front(10);
    
    // 8. Вывод содержимого контейнера на экран
    print_container(container);
    
    // 9. Добавление элемента 20 в середину контейнера
    container.insert(4, 20);
    
    // 10. Вывод содержимого контейнера на экран
    print_container(container);
    
    // 11. Добавление элемента 30 в конец контейнера
    container.push_back(30);
    
    // 12. Вывод содержимого контейнера на экран
    print_container(container);
}



#endif 
