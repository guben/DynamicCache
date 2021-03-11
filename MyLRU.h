//
// Created by 67598 on 2021/3/9.
//

#ifndef DYNAMICCACHE_MYLRU_H
#define DYNAMICCACHE_MYLRU_H
#include <unordered_map>
#include <vector>
#include "Mylist.h"
using namespace std;
class MyLRU {
public:
    explicit MyLRU(long long _cap);
    void modify_cap(long long _cap);
    Node* get(string fname);//查找LRU缓存中有没有fname的节点Node
    int put(string fname,string iotype,long long fsize, vector<Node*>&del);//将某文件信息写入缓存，如果发生了替换，将剔除的Node写入del中
    long long  getsize();//返回当前LRU已经占了多少空间，即链表中所有node的size累加和
    long long getmaxsize();
    void debug_list();
    void debug_table();
private:
    unordered_map<string,Node*> f_N_table;
    Mylist LRUlist;
    long long max_capacity;
};


#endif //DYNAMICCACHE_MYLRU_H
