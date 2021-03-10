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

//    //测试mylist
//    Mylist test;
//    Node* p1=new Node("caonima0","ACCESS",1024000);
//    Node* p2=new Node("caonima1","ACCESS",1024000);
//    test.push_front(p1);
//    test.push_front(p2);
//    for(Node* p=test.head->next;p!=test.tail;p=p->next)
//        cout<<p->fname<<" "<<p->iotype<<" "<<p->size<<endl;
//    cout<<endl;
//    test.erase(p2);
//    cout<<p2->fname<<p2->iotype<<p2->size<<endl;
//    for(Node* p=test.head->next;p!=test.tail;p=p->next)
//        cout<<p->fname<<" "<<p->iotype<<" "<<p->size<<endl;
//    cout<<test.allsize<<endl;
//    Node* a=test.pop_back();
//    cout<<a->fname<<a->iotype<<a->size<<endl;
//    cout<<endl;
//    for(Node* p=test.head->next;p!=test.tail;p=p->next)
//        cout<<p->fname<<" "<<p->iotype<<" "<<p->size<<endl;
//
//    test.push_front(p1);
//    test.push_front(p2);
//    for(Node* p=test.head->next;p!=test.tail;p=p->next)
//        cout<<p->fname<<" "<<p->iotype<<" "<<p->size<<endl;
//    cout<<test.allsize;
