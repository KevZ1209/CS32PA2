//
//  main.cpp
//  CS32PA2
//
//  Created by Kevin Zhang on 1/19/22.
//

#include <iostream>
#include "Map.h"

int main() {
    Map m = Map();

    m.erase("carey2");
    m.erase("david");
    
    m.dump();
}
