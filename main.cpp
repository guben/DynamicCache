#include <iostream>
#include "Mylist.h"
#include "MyLRU.h"
#include <climits>
#include <fstream>
#include <cstring>
#include "MyLFU.h"
using namespace std;
int main() {

//使用trace测试缓存算法，简单看一下，给定50G*n的空间，trace的命中率情况和写入次数情况
    fstream intrace(R"(C:\Users\67598\Desktop\Demo\DynamicCache\trace.log)");
    ofstream out(R"(C:\Users\67598\Desktop\Demo\DynamicCache\out.txt)");
    MyLFU LFUcache(53687091200*2);
    string line;
    int total_req=0;
    int total_hit=0;
    int totalnew=0;
    char buf[100];
    unordered_map<string,int> exsit;
    while(!intrace.eof()){ //读取每行的trace
        intrace.getline(buf,100,'\n');
        char *p=strtok(buf," ");
        int count=0;
        string fname;
        string iotype;
        long long fsize;
        while(p!= nullptr){
            count++;
            switch (count) {
                case 2:
                    fname=p;
                    break;
                case 3:
                    iotype=p;
                    break;
                case 4:
                    fsize=atoi(p);
                    break;

            }
            p=strtok(nullptr," ");
        }
//        out<<fname<<" "<<iotype<<" "<<fsize<<endl;
        //统计一下读了多少不同的文件，总计2372/4000
        exsit[fname]++;
        if(exsit[fname]==1){
            totalnew++;
            // total_size+=fsize;测试看，总共读的文件大小总量占多少，结果是230G左右
        }
        total_req++;
        vector<Node*> del;
        int hit=0;
        //这里是仿真的主要操作
        if(LFUcache.get(fname)== nullptr){//未命中
            if(LFUcache.put(fname,iotype,fsize)!=0){//放入缓存，且发生剔除

            }else{

            }
        }else{//缓存命中
            hit=1;
            total_hit++;
        }
        out<<fname<<" "<<iotype<<" "<<"hit:"<<hit<<endl;
        out<<LFUcache.getsize()<<" "<<LFUcache.getmaxsize()<<endl;
    }
    cout<<total_hit<<":"<<total_req<<"。 hit rate: "<< static_cast<double >(total_hit)/total_req<<endl;
    cout<<totalnew<<endl;
    intrace.close();
    out.close();

    return 0;
}
