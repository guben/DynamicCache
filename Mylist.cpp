//
// Created by 67598 on 2021/3/9.
//

#include "Mylist.h"
Mylist::Mylist(){
    head=new Node;
    tail=new Node;
    allsize=0;
    head->next=tail;
    tail->next=head;
    head->prev=nullptr;
    tail->next=nullptr;
}

void Mylist::push_front(Node* t){
    t->next=head->next;
    t->prev=head;
    head->next->prev=t;
    head->next=t;
    allsize+=t->size;
}
Node* Mylist::pop_back(){
    if(isempty())  return nullptr;
    Node* res=tail->prev;
    tail->prev->prev->next=tail;
    tail->prev=tail->prev->prev;
    allsize-=res->size;
    return res;
}
bool Mylist::isempty() const{
    return head->next == tail;
}

Node* Mylist::erase(Node *t) {
    t->prev->next=t->next;
    t->next->prev=t->prev;
    allsize-=t->size;
    return t;
}
