#include "PHash.h"
#include "time.h"

using namespace std;

bool isprime(int x) {
    for(int i=2; i*i<=x; ++i) {
        if(x%i==0) return false;
    }
    return true;
}

int next_prime(int x) {
	int i;
    for(i=x+1; !isprime(i); ++i);
    return i;
}

int PHash::set_hash(int key) {
    return ((a*key+b) %p) %m;
}

int set_hashlvl_2(hashlvl_2 H, int key) {
    return ((H.a*key) %H.p) %H.m;
}

void PHash::make_hash(vector<STR> v) {
    for(int i=0; i<m; ++i) func[i].m=0;
    for(int i=0; i<v.size(); ++i)
        ++func[set_hash(v[i].key)].m;
    for(int i=0; i<m; ++i) {
        if(func[i].m) {
            func[i].m*=func[i].m;
            func[i].value.resize(func[i].m);
            if(func[i].m==1) {
                func[i].a=0;
                func[i].b=0;
                func[i].p=p;
            } else {
                func[i].b=(rand() % func[i].m);
                func[i].a=(rand() % (func[i].m-1)) + 1;
                func[i].p=p;
            }
        }
    }
    add_elements(v);
}

void PHash::add_elements(vector<STR> v) {
    for(int i=0; i<v.size(); ++i) {
        int column=set_hash(v[i].key);
        int row= set_hashlvl_2(func[column],v[i].key);
        func[column].value[row]=v[i].val;
    }
}

PHash::PHash(vector<STR> v, int maxkey) {
    m=next_prime(v.size());
    func.resize(m);
    p=next_prime(maxkey);
    srand(time(NULL));
    a=(rand() % (m-1)) + 1;
    b=rand() % m;
    make_hash(v);
    add_elements(v);
}

string PHash::Find(int k) {
        int column=set_hash(k);
        int row= set_hashlvl_2(func[column],k);
        return func[column].value[row];
}
