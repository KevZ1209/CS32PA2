//
//  Map.cpp
//  HW1KevinZ
//
//  Created by Kevin Zhang on 1/14/22.
//

#include "Map.h"



Map::Map() {
    // size is zero
    m_size = 0;
    
    // head and tail don't exist
    head = nullptr;
    tail = nullptr;
}

// Destructor
Map::~Map() {
    Node *p = head;
    while (p != nullptr) {
        // create a temporary pointer to store pointer to next Node
        Node *n = p->next;
        
        // delete Node that p points to
        delete p;
        
        // p points to next Node
        p = n;
    }
}

// Copy Constructor
Map::Map(const Map& other) {
    head = nullptr;
    tail = nullptr;
    m_size = 0;
    
    for (Node *p = other.head; p != nullptr; p = p->next) {
        insert(p->key, p->value);
    }
}

// Assignment Operator
Map& Map::operator=(const Map& rhs) {
    // only assign if objects are different to save resources
    if (this != &rhs) {
        Map temp(rhs); // copy-and-swap method
        swap(temp);
    }
    return *this;
}

bool Map::empty() const {
    return m_size==0;
}

int Map::size() const {
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value) {
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full).
    
    // Loop through the map to see if there are matching keys. If so, return false
    Node* p = head;
    while (p != nullptr) {
        if (p->key == key) {
            return false;
        }
        p = p->next;
    }
    
    // Create pointer to new node and insert new key and value
    Node* n = new Node;
    n->key = key;
    n->value = value;
    
    n->next = nullptr;
    
    // prev pointer points to current tail, nullptr if empty
    // set head to new node if map is empty
    if (m_size == 0) {
        n->prev = nullptr;
        head = n;
    }
    else {
        // current tail's next should point to the new Node
        n->prev = tail;
        tail->next = n;
    }
    
    // tail should now point to new node
    tail = n;
    
    // increase the size
    m_size++;
    
    return true;
    
}

bool Map::update(const KeyType& key, const ValueType& value) {
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value that it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.

    Node* p = head;
    while (p != nullptr) {
        if (p->key == key) {
            p->value = value;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
  // If key is equal to a key currently in the map, then make that key no
  // longer map to the value that it currently maps to, but instead map to
  // the value of the second parameter; return true in this case.
  // If key is not equal to any key currently in the map and if the
  // key/value pair can be added to the map, then do so and return true.
  // Otherwise, make no change to the map and return false (indicating
  // that the key is not already in the map and the map has a fixed
  // capacity and is full).

    if (insert(key, value)) {
        return true;
    }
    else if (update(key, value)) {
        return true;
    }
    return false;
}

bool Map::erase(const KeyType& key) {
  // If key is equal to a key currently in the map, remove the key/value
  // pair with that key from the map and return true.  Otherwise, make
  // no change to the map and return false.
    Node* p = head;
    while (p != nullptr) {
        // if key is equal to key in map
        if (p->key == key) {
            // set previous pointer's next to current p's next Node (if there is a previous)
            if (p->prev != nullptr) {
                p->prev->next = p->next;
            }
            else {
                // p is currently equal to the head pointer
                // set head pointer to second Node
                head = p->next;
            }
            // set next pointer's prev pointer to current p's prev (if there is a next)
            if (p->next != nullptr) {
                p->next->prev = p->prev;
            }
            else {
                // p is currently equal to the tail pointer
                // set tail pointer to second-to-last Node
                tail = p->prev;
            }
            delete p;
            m_size--;
            return true;
        }
        p = p->next;
    }
    return false;
}


bool Map::contains(const KeyType& key) const {
    // Return true if key is equal to a key currently in the map, otherwise
    // false.
    Node* p = head;
    while (p != nullptr) {
        if (p->key == key) {
            return true;
        }
        p = p->next;
    }
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
    // If key is equal to a key currently in the map, set value to the
    // value in the map which that key maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.
    Node* p = head;
    while (p != nullptr) {
        if (p->key == key) {
            value = p->value;
            return true;
        }
        p = p->next;
    }
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of the key/value pair in the map whose key is strictly
    // greater than exactly i keys in the map and return true.  Otherwise,
    // leave the key and value parameters unchanged and return false.
    
    // if invalid i
    if (i < 0 || i >= m_size) {
        return false;
    }
    
    // loop through map
    for (Node *p = head; p != nullptr; p = p->next) {
        int count_below = 0;
        // for each element in Map, determine how many keys it is greater than
        for (Node *q = head; q != nullptr; q = q->next) {
            if (p->key > q->key) {
                count_below++;
            }
        }
        // if the number of keys in the map less than p is equal to i, set values and return true
        if (count_below == i) {
            key = p->key;
            value = p->value;
            return true;
        }
    }
    return false;
}


void Map::swap(Map& other) {
  // Exchange the contents of this map with the other one.
    
    // switch the sizes
    int temp_size = other.m_size;
    other.m_size = m_size;
    m_size = temp_size;

    // switch head pointers
    Node *temp = head;
    head = other.head;
    other.head = temp;
    
    // switch tail pointers
    temp = tail;
    tail = other.tail;
    other.tail = temp;
}

void Map::dump() const {
    cerr << "Forward Propagation:" << endl;
    for (Node *p = head; p != nullptr; p = p->next) {
        cerr << p->key;
        cerr << ", ";
        cerr << p->value;
        cerr << "; ";
    }
    cerr << endl;
    cerr << endl;
    
    cerr << "Backward Propagation:" << endl;
    for (Node *p = tail; p != nullptr; p = p->prev) {
        cerr << p->key;
        cerr << ", ";
        cerr << p->value;
        cerr << "; ";
    }
    cerr << endl;
    cerr << endl;
    cerr << "Size: " << m_size << endl;
    cerr << endl;
    cerr << endl;
}

