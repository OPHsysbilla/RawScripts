#include <iostream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;




class LRU
{
public:
    int* LRUcnt;
    int Capacity;
    vector<string>key;
    vector<string>value;
    int Size;
    LRU(){
        Capacity = 0;
        Size = 0;
    }
    LRU(int c){
        Capacity = c;
        LRUcnt = new int[Capacity];
        memset(LRUcnt,0,sizeof(int)*Capacity);
        for(int i=0;i< Capacity ;i++){
            key.push_back("null");
            value.push_back("null");
        }
        Size = 0;
    }
    void updateLRUcntAt(int index){
            int n = getSize();
            int capcityy = getCapacity();
            for(int i=0;i<n;i++){
                LRUcnt[i]++;
            }
            LRUcnt[index]=0;
    }
    ~LRU(){
        delete [] LRUcnt;
    }
    void put(string k ,string v){
        addOne(k,v);
    }
    void addOne(string k ,string v){
        int index = indexOfkey(k);
        bool change_flag = false;
        if(index==-1 && Size < Capacity){//not full,not found
            index = leastUsedIndex();
            key[index]=k;
            Size++;
            change_flag = true;
        }else if(index==-1 && Size == Capacity){// full,not found
            index = leastUsedIndex();
            key[index]=k;
            change_flag = true;
        }else if(index!=-1 && Size == Capacity// full, found
                 || index!=-1 && Size < Capacity){ // not full, found
            change_flag = true;
        }
        if(change_flag){
           value[index]=v;
            updateLRUcntAt(index);
        }
    }

    int indexOfkey(string k ){
        int n = getSize();
        for(int i=0;i<n;i++){
            if( key[i]==k ){
                for(int o=0;o<key.size();o++){
                    LRUcnt[o]++;
                }
                LRUcnt[i]=0;
                return i;
            }
        }
        return -1;
    }
    string get(string k ){
        int index = indexOfkey(k);
        if(index!=-1)
            return value[index];
        else
            return "";
    }
    int leastUsedIndex(){
        int capcityy = getCapacity();
        int n = getSize();
        //if not full yet, indicates next elem to put
        if(n < capcityy)
            return n;
        int index = 0,Max = 0;
        for(int i=0; i<n; i++){
            if(LRUcnt[i]>Max){
                Max = LRUcnt[i];
                index = i;
            }
        }
        return index;
    }
    int getSize() const{
        return Size;
    }
    int getCapacity() const{
        return Capacity;
    }

};


int main()
{
    int m,n;
    scanf("%d %d\n",&m,&n);
    LRU Lru = LRU(m);
    while(n--){
        string instr;
        string k,v ;

        cin>>instr>>k;

        if( "get" == instr){
            string res = Lru.get(k);
            if(!res.empty())
                cout <<res<<endl;
            else
                printf("NULL\n");
        }else if("put" == instr){
             cin>>v;
             Lru.put(k,v);
        }

    }

}
