#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Direction.h"

struct ListNode {
  Direction dir;
  int length;
  ListNode* next;
  ListNode(Direction d, int len)
    : dir(d), length(len), next(nullptr) {}  // Constructor
};

class LinkedList {
private:
  ListNode* head;
public:
  LinkedList()
    : head(nullptr) {}  // Constructor
  ~LinkedList() {
    clear();
  }                                        // Destructor to clean up the list
  void clear();                            // Clear the entire list
  void append(Direction dir, int length);  // Add a new node to the end of the list
  ListNode* getHead() const;               // Get the head node of the list
  ListNode* getTail() const;               // Get the tail node of the list
  void trimHead();                         // Removes current head and make the next as the new head
                                           //void display(); // Display the list
};

#endif
