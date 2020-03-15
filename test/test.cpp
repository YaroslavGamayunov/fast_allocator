//
// Created by Ярослав Гамаюнов on 2020-03-13.
//

#include <memory>
#include <list>
#include <vector>
#include <iostream>
#include "../src/FixedAllocator.h"
#include "../include/List.h"

int main() {
    List<int> v1;

    FixedAllocator<3> a(2);
    std::vector<int> cmds;
    for (int i = 0; i < 3e7; i++) {
        cmds.push_back(rand() % 2);
    }

    double time = clock();

    for (int cmd : cmds) {
        if (cmd == 0 && v1.size() > 0) {
            v1.pop_back();
        } else {
            v1.push_back(cmd);
        }
    }

    std::cout << "fast list speed " << (clock() - time) / CLOCKS_PER_SEC << "\n";


    time = clock();
    std::list<int, std::allocator<int>> v2;
    for (int cmd : cmds) {
        if (cmd == 0 && v2.size()) {
            v2.pop_back();
        } else {
            v2.push_back(cmd);
        }
    }

    std::cout << "std list speed " << (clock() - time) / CLOCKS_PER_SEC << "\n";
}