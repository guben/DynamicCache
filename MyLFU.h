//
// Created by 67598 on 2021/3/10.
//

#ifndef DYNAMICCACHE_MYLFU_H
#define DYNAMICCACHE_MYLFU_H
#include <unordered_map>
#include "Mylist.h"
using namespace std;
class freqlist{
public:
    explicit freqlist(int _freq);
    void push_front(Node* t) ;
    Node* erase(Node* t);
    Node* pop_back();
    bool isempty() const;

    int freq;
    Mylist LFUlist;
};
class MyLFU {
public:
    MyLFU(long long _cap);
    Node* get(string fname);//查找LRU缓存中有没有fname的节点Node
    int put(string fname,string iotype,long long fsize);//将某文件信息写入缓存，可能需要剔除操作
    long long getsize();//比较复杂了，LFU需要遍历整个映射表才能得到size，除非提前算好,每次put都需要更新，剔除和新加的都要算cursize！
    long long getmaxsize();
    void addNode(Node* t);//添加一个node指针到缓存中
    Node* deleteMinNode();
    void debug_list();
private:
    unordered_map<string,Node*> fname_N_table;
    unordered_map<int,freqlist*> fre_L_table;
    int min_freq;
    long long cursize;
    long long max_capacity;
};


#endif //DYNAMICCACHE_MYLFU_H
