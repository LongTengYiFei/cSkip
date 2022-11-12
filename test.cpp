#include <iostream>
#include "skipList.h"
using namespace std;

int main(){
    SkipList<int, string>* sl = new SkipList<int, string>(5);
    sl->Insert(1, "hello");
    sl->Insert(2, "world");
    sl->Insert(4, "Json");
    sl->Insert(5, "mysql");
    cout<<sl->Search(1)<<endl;
    cout<<sl->Search(2)<<endl;
    cout<<sl->Search(3)<<endl;
    cout<<sl->Search(4)<<endl;
    cout<<sl->Search(5)<<endl;

    cout<<"---- ---- ----"<<endl;
    sl->Delete(1);
    sl->Delete(4);
    cout<<sl->Search(1)<<endl;
    cout<<sl->Search(2)<<endl;
    cout<<sl->Search(3)<<endl;
    cout<<sl->Search(4)<<endl;
    cout<<sl->Search(5)<<endl;

    cout<<"---- ---- ----"<<endl;
    sl->Insert(1, "hello");
    sl->Insert(4, "Json");
    sl->Insert(2, "wooooorld");
    sl->Insert(3, "hahah");
    cout<<sl->Search(1)<<endl;
    cout<<sl->Search(2)<<endl;
    cout<<sl->Search(3)<<endl;
    cout<<sl->Search(4)<<endl;
    cout<<sl->Search(5)<<endl;

    return 0;
}