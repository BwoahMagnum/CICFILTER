//
//  main.cpp
//  CICFILTER
//
//  Created by 李彦锋 on 2020/11/23.
//

#include <iostream>
#include "CICFILTER.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    CIC_FILTER(CIC_Interpolation, 1, 1, 3, 1);
    // ~CIC_FILTER();
    return 0;
}
