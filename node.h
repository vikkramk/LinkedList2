#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>
#include "Student.h"

class Node{
 public:
  Node* getNext();//returns the next Node
  Student* getStudent();//gets the studentptr
  void setNext(Node* current);//sets next
  Node(Student* student);//constuctor
  ~Node();//deconstructor
 private:
  Node* next = NULL;
  Student* studentPtr;
};

#endif
