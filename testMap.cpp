//
//  main.cpp
//  CS32PA2
//
//  Created by Kevin Zhang on 1/19/22.
//

#include <iostream>
#include "Map.h"
#include <cassert>
int main() {
//    Map m = Map();
//
//    m.insertOrUpdate("Carey", 10);
//    m.insertOrUpdate("David", 12);
//    m.insertOrUpdate("Green Goblin", 2002);
//    m.insertOrUpdate("Otto Octavius", 8);
//
//    Map n = Map();
//    n.insertOrUpdate("Rey", 8);
//    n.insertOrUpdate("Obi Wan", 1);
//    n.insertOrUpdate("David", 120);
//    n.insertOrUpdate("Boba Fett", 5);
//
//    Map c;
//    Map d = c;
//    n = m;
//    m.insert("jango Fett", 61);
//    d.insert("darth sidious", 66);
//
//    m.dump();
//    n.dump();
//    c.dump();
//    d.dump();
//
//    reassign(n, c);
//
//    c.dump();
//
    // default constructor
    Map m;
    Map n;
    Map empty_map;
    Map empty_map2;
    
    // EMPTY MAP
    assert(m.size() == 0);      // test size
    assert(m.empty());          // test empty
    assert(!m.erase("Ricky"));  // nothing to erase
    assert(!m.update("Ricky", 10)); // nothing to update
    assert(merge(empty_map, empty_map, empty_map)); // merge empty maps
    assert(empty_map.size() == 0);
    reassign(empty_map, n); // reassign with empty maps
    assert(merge(empty_map, empty_map2, n)); // merge empty maps
    assert(n.size() == 0); // n should stay the same after reassign and merge
    
    
    // ONE ELEMENT MAP
    assert(m.insert("Ricky", 10)); // insert new Node
    assert(m.size() == 1);  // check if new size is correct
    assert(!m.empty()); // check if no longer empty
    assert(m.update("Ricky", 100)); // update new node's value
    KeyType k = "default";
    ValueType v;
    assert(m.get("Ricky", v)); // test get function
    assert(v == 100); // test if value was updated
    assert(!m.get(1, k, v)); // test if i is out of range for get()
    assert(!m.get(-1, k, v)); // test if i is out of range for get()
    assert(v == 100 && k == "default"); // make sure k and v weren't changed by get
    
    
    // TYPICAL MAP
    assert(m.insertOrUpdate("Vicky", 2)); // add new element
    assert(m.contains("Vicky"));
    assert(m.size() == 2);
    assert(m.insertOrUpdate("Mickie", 5)); // add new element
    assert(m.contains("Mickie"));
    assert(m.size() == 3);
    assert(m.insertOrUpdate("Nikki", 6)); // add new element
    assert(m.contains("Nikki"));
    assert(m.size() == 4);
    assert(m.insertOrUpdate("Wiki", 8)); // add new element
    assert(m.contains("Wiki"));
    assert(m.size() == 5);
    assert(m.insertOrUpdate("Vicky", 20)); // update element
    
    assert(m.erase("Ricky")); // erase the first element
    assert(!m.contains("Ricky"));
    assert(m.size() == 4);
    assert(m.erase("Nikki")); // erase the last element
    assert(!m.contains("Nikki"));
    assert(m.size() == 3);
    assert(m.erase("Mickie")); // erase middle element
    assert(!m.contains("Mickie"));
    assert(m.size() == 2);
    
    // m should have Wiki, 8; Vicky, 20;
    
    // SWAP
    n.insertOrUpdate("Joe", 12);
    n.insertOrUpdate("Monroe", 14);
    n.insertOrUpdate("Ego", 16);
    m.swap(n);  // swap test
    assert(m.contains("Joe") && m.contains("Monroe") && m.contains("Ego")); // swap test
    assert(n.contains("Wiki") && n.contains("Vicky")); // swap test
    assert(m.size() == 3 && n.size() == 2); // check sizes
    
    m.insert("Rousseau", 17);
    assert(m.contains("Rousseau") & !n.contains("Rousseau")); // changing one shouldn't change the other
    empty_map2.swap(empty_map); // swap empty maps
    assert(empty_map2.size() == 0 && empty_map.size() == 0);
    
    // m should now include Joe, 12; Monroe, 14; Ego, 16; Rousseau, 17;
    // n should now include Vicky, 20; Wiki, 8;
    
    
    // Test Copy Constructor
    Map new_map = m;
    assert(new_map.contains("Rousseau") && new_map.contains("Ego") && new_map.contains("Monroe") && new_map.contains("Joe")); // m's values copied over to new_map
    assert(m.size() == new_map.size()); // check size
    
    // Test Assignment Operator
    new_map = n;
    assert(new_map.contains("Wiki") && new_map.contains("Vicky"));
    assert(n.size() == new_map.size());
    
    // ALIASING TESTS
    reassign(m, m);
    // check if each key has different value than before
    m.get(0, k, v);
    assert(v != 16);
    m.get(1, k, v);
    assert(v != 12);
    m.get(2, k, v);
    assert(v != 14);
    m.get(3, k, v);
    assert(v != 17);
    // m should now include Joe, 14; Monroe, 17; Ego, 12; Rousseau, 16;
    
    merge(m, m, m); // should do nothing
    assert(m.contains("Rousseau") && m.contains("Ego") && m.contains("Monroe") && m.contains("Joe")); // m should stay the same as before
    m.swap(m); // should do nothing
    assert(m.contains("Rousseau") && m.contains("Ego") && m.contains("Monroe") && m.contains("Joe")); // m should stay the same as before
    merge(m, n, m);
    // m should now include Joe, 14; Monroe, 17; Ego, 12; Rousseau, 16; Vicky, 20; Wiki, 8;
    assert(m.contains("Joe") && m.contains("Monroe") && m.contains("Ego") && m.contains("Rousseau") && m.contains("Vicky") && m.contains("Wiki"));
    
    cerr << "All tests passed!" << endl;
    

}
