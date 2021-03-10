//
// Created by 67598 on 2021/3/10.
//

#include "MyLFU.h"
#include <iostream>
using namespace std;
//freqlist封装了mylist操作
freqlist::freqlist(int _freq):freq(_freq),LFUlist(){
}

void freqlist::push_front(Node *t) {
    LFUlist.push_front(t);
}

Node *freqlist::erase(Node *t) {
    return LFUlist.erase(t);
}

Node *freqlist::pop_back() {
    return LFUlist.pop_back();
}

bool freqlist::isempty() const {
    return LFUlist.isempty();
}

//MyLFU初始化，主要是容量初始化
MyLFU::MyLFU(long long _cap):max_capacity(_cap),min_freq(0),cursize(0){

}

//MyLFU的get函数，可以获得该fname对应的node结点指针，不命中将返回空指针
//命中后会修改freq计数，并且将该结点移动到另一个freq的链表
//注意需要判断min_freq是不是空的，如果是空的，更新该值，该值主要用来剔除
Node *MyLFU::get(string fname) {
    auto map_it=fname_N_table.find(fname);
    if(map_it==fname_N_table.end()){//未命中
        return nullptr;
    }else{//命中
        Node* target=map_it->second;
        int freq=target->freq;
        freqlist* pfre=fre_L_table[freq];
        pfre->erase(target);
        if(fre_L_table[min_freq]->isempty())min_freq++;
        target->freq++;
        addNode(target);
        return target;
    }
}

//put将fname对应的node放入缓存中
//如果存在，那么更新该node的freq，并且移动到其他链表中
//如果不存在，那么需要生成新node结点，然后跟新min_freq为1，
int MyLFU::put(string fname, string iotype, long long fsize) {
    auto map_it=fname_N_table.find(fname);
    Node *target;
    if(map_it!=fname_N_table.end()){
        target=fname_N_table[fname];
        int freq=target->freq;
        freqlist* freqp=fre_L_table[freq];
        freqp->erase(target);
        if(fre_L_table[min_freq]->isempty())min_freq++;
        target->freq++;
        addNode(target);
    }else{
        while(fsize+getsize() > getmaxsize()){
            Node *deleted=this->deleteMinNode();
            cursize-=deleted->size;
            fname_N_table.erase(deleted->fname);
            delete deleted;
        }
        target=new Node(fname,iotype,fsize);
        fname_N_table[fname]=target;
        this->addNode(target);
        min_freq=1;
        cursize+=fsize;
    }
    return 0;
}

long long MyLFU::getsize() {
    return cursize;
}

long long MyLFU::getmaxsize() {
    return max_capacity;
}

void MyLFU::addNode(Node *t) {
    int freq=t->freq;
    auto map_it=fre_L_table.find(freq);
    if(map_it==fre_L_table.end())
        fre_L_table[freq]=new freqlist(freq);
    fre_L_table[freq]->push_front(t);
}

Node* MyLFU::deleteMinNode() {
    freqlist* frep=fre_L_table[min_freq];
    Node *res=frep->pop_back();
    while(fre_L_table[min_freq]->isempty()){
        min_freq++;
    }
    return res;
}

void MyLFU::debug_list() {
    for(auto &x:fname_N_table)
        cout<<x.first<<":"<<x.second<<endl;
    for(auto &x:fre_L_table) {
        cout << x.first << ":";
        Node* p=x.second->LFUlist.head->next;
        while(p!= nullptr){
            cout<<p->fname<<" ";
            p=p->next;
        }
        cout<<endl;
    }
}

////测试LFU
//MyLFU LFUcache(300);
//LFUcache.put("1","ACCESS",100);
//cout<<LFUcache.getmaxsize()<<endl
//<<LFUcache.getsize()<<endl;
//LFUcache.put("2","ACCESS",100);
//LFUcache.put("3","ACCESS",50);
//LFUcache.put("4","ACCESS",50);
//
//LFUcache.debug_list();
//
//LFUcache.get("2");
//LFUcache.debug_list();
//LFUcache.put("5","ACCESS",200);
//LFUcache.debug_list();
////    for(auto &x:del){
////        cout<<x->fname<<" "<<x->iotype<<" "<<x->size<<endl;
////    }
//if(LFUcache.get("1")!= nullptr)
//cout<<"error";
