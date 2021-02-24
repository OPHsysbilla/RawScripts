#include<cstdio>
#include <iostream>
#include <string>
#include <fstream>
using namespace std; 

bool startsWith(string s, string sub){
        return s.find(sub)==0;
}

bool endsWith(string s,string sub){
        return s.rfind(sub)==(s.length()-sub.length());
} 

int main()
{
    string a, inFileName;
    ifstream fin;
    ofstream fout;

    cin>> inFileName;
    fout.open("XExpose.txt");
    fin.open(inFileName);

    streambuf * backup = cout.rdbuf();
    streambuf * backupIn =  cin.rdbuf();
    
    // 重定向文件为标准输入
    cout.rdbuf(fout.rdbuf());
    cin.rdbuf(fin.rdbuf());

    // //cin>>str;    /*有空格就会停止*/
    // getline(cin, str);    /*直到换行符处才停止*/
    string preffix = "private";
	while(getline(cin, a))
    {
        // for(int i=0;i<len;i++)
        // { 
        //     for(i=0;i<len;i++)
        //     {
        //         if(a.){

        //         }
        //         cout<<a[i];
        //     }
        //     cout<<endl;
        //     break;
        // }

        int pos = a.find(preffix);
        if(pos >= 0
            && startsWith(a.substr(pos), preffix)){
            cout<<"\t@Expose"<<endl;
        }
        cout<<a<<endl;
        a.clear();
    }
    cout.rdbuf(backup);
    fout.close();
    cin.rdbuf(backupIn);
    fin.close();
}


