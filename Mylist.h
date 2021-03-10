//
// Created by 67598 on 2021/3/9.
//

#ifndef DYNAMICCACHE_MYLIST_H
#define DYNAMICCACHE_MYLIST_H
#include <string>
using namespace std;
struct Node{
    string fname;//key
    string iotype;
    int size;
    int freq;
    Node* prev;
    Node* next;
    Node(){fname=" ";}
    Node(string _fname,string _iotype,long long _size):fname(_fname),iotype(_iotype),size(_size){}
};
class Mylist {
public:
    Node* head;
    Node* tail;
    long long allsize;

    Mylist();
    void push_front(Node* t) ;
    Node* erase(Node* t);
    Node* pop_back();
    bool isempty() const;
};


#endif //DYNAMICCACHE_MYLIST_H
