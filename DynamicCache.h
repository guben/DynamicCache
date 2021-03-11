//
// Created by 67598 on 2021/3/10.
//

#ifndef DYNAMICCACHE_DYNAMICCACHE_H
#define DYNAMICCACHE_DYNAMICCACHE_H
#include "MyLFU.h"
#include "MyLRU.h"
#include "Mylist.h"

class DynamicCache {
public:
    explicit DynamicCache(long long capacity);
    DynamicCache(long long _cap1,long long _cap2);
    Node* get(string fname);//查找LRU缓存或者LFU缓存中有没有fname的节点Node
    int put(string fname,string iotype,long long fsize);//将某文件信息写入LRU缓存，可能需要剔除操作，然后剔除的数据判断是否可以写入LFU缓存
    long long getsize();//获取总缓存大小
    long long getmaxsize();
private:
    MyLRU LRUcache;
    MyLFU LFUcache;
    long long max_capacity;
};


#endif //DYNAMICCACHE_DYNAMICCACHE_H
