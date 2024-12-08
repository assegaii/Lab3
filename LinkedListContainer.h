#ifndef LINKED_LIST_CONTAINER_H
#define LINKED_LIST_CONTAINER_H

#include <iostream>
#include <stdexcept>

template <typename T>
struct ListNode {
    T value;
    ListNode* next;
    ListNode* prev;

    ListNode(const T& value) : value(value), next(nullptr), prev(nullptr) {}
};

template <typename T>
class LinkedListContainer {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    size_t current_size;

public:
    LinkedListContainer() : head(nullptr), tail(nullptr), current_size(0) {}

    ~LinkedListContainer() {
        while (head) {
            auto tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    LinkedListContainer(const LinkedListContainer&) = delete;
    LinkedListContainer& operator=(const LinkedListContainer&) = delete;

    LinkedListContainer(LinkedListContainer&& other) noexcept
        : head(other.head), tail(other.tail), current_size(other.current_size) {
        other.head = other.tail = nullptr;
        other.current_size = 0;
    }

    LinkedListContainer& operator=(LinkedListContainer&& other) noexcept {
        if (this != &other) {
            while (head) {
                auto tmp = head;
                head = head->next;
                delete tmp;
            }
            head = other.head;
            tail = other.tail;
            current_size = other.current_size;
            other.head = other.tail = nullptr;
            other.current_size = 0;
        }
        return *this;
    }

    void push_back(const T& value) {
        auto new_node = new ListNode<T>(value);
        if (!tail) {
            head = tail = new_node;
        } else {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
        ++current_size;
    }

    void push_front(const T& value) {
        // Создаем новый узел
        auto new_node = new ListNode<T>(value);
        
        // Если список пустой, новый узел будет как head и tail
        if (!head) {
            head = tail = new_node;
        } else {
            // Новый узел будет перед текущим head
            new_node->next = head;
            head->prev = new_node;
            head = new_node;
        }
        
        ++current_size;
    }

    void insert(size_t index, const T& value) {
        if (index > current_size) {
            throw std::out_of_range("Index out of range");
        }
        auto new_node = new ListNode<T>(value);
        if (index == 0) {
            new_node->next = head;
            if (head) head->prev = new_node;
            head = new_node;
            if (!tail) tail = head;
        } else {
            auto current = head;
            for (size_t i = 0; i < index - 1; ++i) {
                current = current->next;
            }
            new_node->next = current->next;
            if (current->next) current->next->prev = new_node;
            current->next = new_node;
            new_node->prev = current;
            if (!new_node->next) tail = new_node;
        }
        ++current_size;
    }

    void erase(size_t index) {
        if (index >= current_size) {
            throw std::out_of_range("Index out of range");
        }
        auto current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        if (current->prev) current->prev->next = current->next;
        if (current->next) current->next->prev = current->prev;
        if (current == head) head = current->next;
        if (current == tail) tail = current->prev;
        delete current;
        --current_size;
    }

    size_t size() const {
        return current_size;
    }

    class Iterator {
    private:
        ListNode<T>* node;
    public:
        Iterator(ListNode<T>* node) : node(node) {}
        T& operator*() { return node->value; }
        Iterator& operator++() { node = node->next; return *this; }
        bool operator!=(const Iterator& other) const { return node != other.node; }
    };

    
    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }
};

#endif 
