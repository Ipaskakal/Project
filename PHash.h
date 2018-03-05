#include <vector>
#include <string>

using namespace std;

struct STR {
	int key;
	string val;
	STR(int k, string v) : key(k), val(v) {}
	STR() : key(0), val(0) {}
};

struct hashlvl_2 {
    int m,p,a,b;
    vector<string> value;
};

class PHash {

private:
    int a,b,m,p;
    vector<hashlvl_2> func;
    void make_hash(vector<STR> v);
    void add_elements(vector<STR> v);
    int set_hash(int key);

public:
    PHash(vector<STR> v,int maxkey);
    string Find(int key);
};
