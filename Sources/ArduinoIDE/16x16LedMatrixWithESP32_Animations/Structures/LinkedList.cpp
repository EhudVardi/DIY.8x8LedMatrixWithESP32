#include "LinkedList.h"

void LinkedList::clear() {
    ListNode* temp = head;
    while (temp) {
        ListNode* next = temp->next;
        delete temp;
        temp = next;
    }
    head = nullptr;
}    
void LinkedList::append(Direction dir, int length) {
    ListNode* newNode = new ListNode(dir, length);
    if (!head) {
        head = newNode;
    } else {
        ListNode* temp = head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
//void LinkedList::display() {
//    ListNode* temp = head;
//    while (temp) {
//        std::cout << "Direction: " << directionToString(temp->dir)
//                  << ", Length: " << temp->length << std::endl;
//        temp = temp->next;
//    }
//}