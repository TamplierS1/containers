#include <iostream>
#include "containers.h"

using namespace Containers;

int main()
{
    Vector<int> vec;
    vec.push_back(1);
    vec.push_back(100);
    vec.push_back(5);
    std::cout << vec[2] << '\n';
    vec.pop_back();
    std::cout << vec[1] << '\n';
    vec.push_back(7);
    std::cout << vec[2];

    return 0;
}