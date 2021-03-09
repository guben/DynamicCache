//
// Created by 67598 on 2021/3/9.
//

#ifndef DYNAMICCACHE_MYLRU_H
#define DYNAMICCACHE_MYLRU_H
#include <unordered_map>
#include "Mylist.h"
using namespace std;
class MyLRU {
public:
    explicit MyLRU(int cap);
    Node* get(string &fname);//查找LRU缓存中有没有fname的节点Node
    void put(string &fname,Node* del);//将某文件信息写入缓存，如果发生了替换，将剔除的Node写入del中
    int getsize();//返回当前LRU已经占了多少空间，即链表中所有node的size累加和
private:
    unordered_map<string,Node*> f_N_table;
    Mylist LRUlist;
    int max_capacity;
};


#endif //DYNAMICCACHE_MYLRU_H
