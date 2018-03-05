#include <vector>
#include <iostream>
#include "PHash.h"

using namespace std;

int main()
{
    cout<<"Enter number"<<endl;
    int n;
	cin >> n;
    vector<STR> v;
    int max=0;
    cout<<"key and string:"<<endl;
    for(int i=0; i<n; ++i) {
        string value;
        int key;
        cin>>key>>value;
        if(key>max) max=key;
        STR d(key,value);
        v.push_back(d);
    }
    PHash table(v,max);
    for(int i=0; i<n; ++i) {
        int key;
        cin>>key;
        cout<<table.Find(key)<<endl;
    }
    return 0;
}
