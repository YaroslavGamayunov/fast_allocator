//
// Created by Ярослав Гамаюнов on 2020-03-15.
//

#ifndef FAST_ALLOCATOR_LIST_H
#define FAST_ALLOCATOR_LIST_H

#include "FastAllocator.h"

template<typename T>
struct Node {
    T value;
    Node *next = nullptr;
    Node *previous = nullptr;

    Node(const T &value) {
        this->value = value;
    }

    Node() {}
};

template<typename T, typename Allocator = FastAllocator<Node<T>>>
class List {
public:
    using ListNode = Node<T>;

    explicit List(const Allocator &allocator = Allocator()) : allocator(allocator), nElements(0) {}

    List(size_t count, const T &value = T(), const Allocator &allocator = Allocator()) {
        this->allocator = allocator;
        nElements = count;

        listFront = (ListNode *) allocator.allocate(count);

        ListNode *curNode = listFront;
        for (int i = 0; i < count; i++) {
            if (i > 0) {
                curNode->previous = curNode - 1;
            }
            if (i + 1 < count) {
                curNode->next = curNode + 1;
            }
            curNode->value = value;
            curNode = curNode->next;
        }
        listBack = listFront + count;
    }

    void push_back(const T &value) {
        nElements++;
        if (listFront == nullptr) {
            initialize(value);
            return;
        }
        ListNode *node = new((ListNode *) allocator.allocate(1)) Node(value);
        listBack->next = node;
        node->previous = listBack;
        listBack = node;
    }

    void push_front(const T &value) {
        nElements++;
        if (listFront == nullptr) {
            initialize(value);
            return;
        }
        ListNode *node = new((ListNode *) allocator.allocate(1)) Node(value);
        listFront->previous = node;
        node->next = listFront;
        listFront = node;
    }

    void pop_back() {
        nElements--;
        ListNode *prevBack = listBack->previous;
        allocator.deallocate(prevBack->next, 1);
        listBack = prevBack;
    }

    void pop_front() {
        nElements--;
        ListNode *nextFront = listFront->next;
        allocator.deallocate(nextFront->previous, 1);
        listFront = nextFront;
    }

    void insert_before(ListNode *node, const T &value) {
        nElements++;
        ListNode *curNode = new((ListNode *) allocator.allocate(1)) Node<T>;
        curNode->previous = node->previous;
        curNode->next = node;
        curNode->previous->next = curNode;
        node->previous = curNode;
    }

    void insert_after(ListNode *node, const T &values) {
        nElements++;
        ListNode *curNode = new((ListNode *) allocator.allocate(1)) ListNode;
        curNode->next = node->next;
        curNode->previous = node;
        curNode->next->previous = curNode;
        node->next = curNode;
    }

    void erase(ListNode *node) {
        nElements--;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        allocator.deallocate(node, 1);
    }

    size_t size() {
        return nElements;
    }

private:
    // initializes 1 element list
    void initialize(const T &value) {
        listFront = new((ListNode *) allocator.allocate(1)) Node(value);
        listBack = listFront;
        nElements = 1;
        listFront->value = value;
    }

    size_t nElements;
    ListNode *listFront = nullptr;
    ListNode *listBack = nullptr;
    Allocator allocator;
};

#endif //FAST_ALLOCATOR_LIST_H
