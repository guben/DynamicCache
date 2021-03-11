//
// Created by 67598 on 2021/3/10.
//

#include "DynamicCache.h"

#include <utility>

DynamicCache::DynamicCache(long long  capacity):LRUcache(capacity/2),LFUcache(capacity/2),max_capacity(capacity) {

}

DynamicCache::DynamicCache(long long _cap1, long long _cap2):LRUcache(_cap1),LFUcache(_cap2),max_capacity(_cap2+_cap1){

}

Node *DynamicCache::get(string fname) {
    Node *res;
    if((res=LRUcache.get(fname))!= nullptr){
        return res;
    }else if((res=(LFUcache.get(fname)))!= nullptr){
            return res;
    }else
        return nullptr;
}

int DynamicCache::put(string fname, string iotype, long long int fsize) {
    vector<Node*> del;
    if(LRUcache.put(fname,iotype,fsize,del)==0){
        return 0;
    }else{
        for(Node* x:del){
            if(x->freq < LFUcache.get_minfreq())
                continue;
            else{
                LFUcache.put(x->fname,x->iotype,x->size);
                delete x;
            }
        }
    }
    return 0;
}

long long DynamicCache::getsize() {
    return LRUcache.getsize()+LFUcache.getsize();
}

long long DynamicCache::getmaxsize() {
    return max_capacity;
}




