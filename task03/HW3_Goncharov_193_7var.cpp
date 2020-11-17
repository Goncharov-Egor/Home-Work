#include <iostream>
#include <set>
#include <string>
#include <vector>

#define pb push_back
#define FILE
#define FAST

using namespace std;

bool is_digit(string s) {
	for(int i = 0; i < s.size(); ++i)
		if(s[i] <= '0' || s[i] >= '9')
			return false;
	return true;
}

vector<string> operator * (vector<string> a, vector<string> b) {

}

vector<string> split(string s) {
	string tmp = "";
	vector<string> ans;
	for(int i = 0; i < s.size(); ++i) {
		if(s[i] == " ") {
			ans.pb(tmp);
			tmp = "";
			continue;
		} 
		tmp += s[i];
	}
	return ans;
}


int main() {
#ifdef FAST
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
#ifdef FILE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout); 
#endif
    int n; cin >> n;
    vector<vector<string>> v;
    for(int i = 0; i < n; ++i) {
    	vector<string> s = split(getline(cin, s))
    	v.pb(s);
    }
    for(int i = 0; i < v.size(); ++i) {
    	for(int j = 0; j < v[i].size(); ++j) {
    		cout << v[i][j] << " ":
    	}
    	cout << endl;
    }
}











