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
    m.insertOrUpdate("Otto Octavius", 8);
    m.insertOrUpdate("Green Goblin", 2002);
    m.insertOrUpdate("Carey", 10);
    m.insertOrUpdate("David", 12);
    
    Map n = Map();
    n.insertOrUpdate("Rey", 8);
    n.insertOrUpdate("Obi Wan", 1);
    n.insertOrUpdate("David", 12);
    n.insertOrUpdate("Boba Fett", 5);
    
    Map c;
//    Map d = c;
//    n = m;
//    m.insert("jango Fett", 61);
//    d.insert("darth sidious", 66);
//
//    m.dump();
//    n.dump();
//    c.dump();
//    d.dump();
    
    merge(m, n, c);
    
    m.dump();
    n.dump();
    c.dump();
    
}
