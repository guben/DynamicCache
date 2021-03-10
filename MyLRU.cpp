//
// Created by 67598 on 2021/3/9.
//

#include "MyLRU.h"
#include <iostream>
using namespace std;
MyLRU::MyLRU(long long cap):max_capacity(cap),LRUlist(),f_N_table(){

}

Node *MyLRU::get(string fname) { //LRUcache的get，先查映射表，没有找到返回空；找到后将其置于链表首，并返回
    auto fn_it=f_N_table.find(fname);
    if(fn_it==f_N_table.end())
        return nullptr;
    else{
        Node* target=fn_it->second;
        target->freq++;
        LRUlist.erase(target);
        LRUlist.push_front(target);
        return target;
    }
}

int MyLRU::put(string fname,string iotype,long long fsize, vector<Node*>&del) {
    auto fn_it=f_N_table.find(fname);
    if(fn_it!=f_N_table.end()){        //这段是将缓存项写入，如果已经存在，那么就和get一样的操作，并且del为空，返回0，表明没有置换
        Node* target=fn_it->second;
        target->freq++;
        LRUlist.erase(target);
        LRUlist.push_front(target);
        return 0;
    }else{
        long long nowsize=getsize()+fsize;
        int count=0;
        while(nowsize>getmaxsize()){   //没有找到，而且需要发生置换,从LRU的末尾开始删除项，直到size满足要求
            Node* deleted=LRUlist.pop_back();
            f_N_table.erase(deleted->fname);
            del.push_back(deleted);
            nowsize-=deleted->size;
            count++;
        }
        Node *new_node = new Node(fname,iotype,fsize);
        f_N_table[fname]=new_node;
        LRUlist.push_front(new_node);
        return count;
    }
}

long long MyLRU::getsize() {
    return LRUlist.allsize;
}

long long MyLRU::getmaxsize() {
    return max_capacity;
}

void MyLRU::debug_list() {
    for(Node*p=LRUlist.head->next;p!=LRUlist.tail;p=p->next)
        cout<<p->fname<<" "<<p->iotype<<" "<<p->size<<"--->";
    cout<<endl;
}

void MyLRU::debug_table() {
    for(auto &x:f_N_table)
        cout<<x.first<<" "<<x.second->iotype<<" "<<x.second->size<<"--->";
    cout<<endl;
}

//    //测试MyLRU
//    MyLRU LRUcache(300);
//    vector<Node*> del;
//    LRUcache.put("1","ACCESS",100,del);
//    cout<<LRUcache.getmaxsize()<<endl
//        <<LRUcache.getsize()<<endl;
//    LRUcache.put("2","ACCESS",100,del);
//    LRUcache.put("3","ACCESS",50,del);
//    LRUcache.put("4","ACCESS",50,del);
//    LRUcache.debug_list();
//    LRUcache.get("2");
//    LRUcache.debug_list();
//    LRUcache.put("5","ACCESS",200,del);
//    LRUcache.debug_list();
//    cout<<"del:"<<endl;
//    for(auto &x:del){
//        cout<<x->fname<<" "<<x->iotype<<" "<<x->size<<endl;
//    }
//    if(LRUcache.get("1")!= nullptr)
//        cout<<"error";
//    LRUcache.debug_table();