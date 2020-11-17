//
//  main.cpp
//  salasm
//
//  Created by Егор Гончаров on 17.11.2020.
//  Copyright © 2020 Егор Гончаров. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <set>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

#define pb push_back
//#define FILE
#define FAST

using namespace std;

vector<string> ans;
vector<vector<string>> v;

bool is_digit(string s) {
    for(int i = 0; i < s.size(); ++i)
        if(s[i] < '0' || s[i] > '9')
            return false;
    return true;
}

vector<string> operator * (vector<string> a, vector<string> b) {
    vector<string> ans;
    for(int i = 0; i < a.size(); ++i) {
        for(int j = 0; j < b.size(); ++j) {
            ans.pb(a[i] + ", " + b[j]);
        }
    }
    return ans;
}
bool f = true;

vector<string> split(string s) {
    string tmp = "";
    vector<string> ans;
    set<string> my_set;
    for(int i = 0; i < s.size(); ++i) {
        if(s[i] == ' ') {
            ans.pb(tmp);
            my_set.insert(tmp);
            f &= is_digit(tmp);
            tmp = "";
            continue;
        }
        tmp += s[i];
    }
    ans.pb(tmp);
    my_set.insert(tmp);
    f &= ans.size() == my_set.size();
    return ans;
}

mutex mt;
vector<string> solve(int i, int j) {
    //mt.lock();
    j = j < (int)v.size() ? j : (int)v.size();
    vector<string> local_ans = v[i];
    for(int k = i + 1; k < j; ++k) {
        local_ans = local_ans * v[k];
    }
   // mt.unlock();
    return local_ans;
}

int32_t main() {
    
#ifdef FAST
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
#endif
#ifdef FILE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    
    cout << "Enter N -- count of sets: ";
    int n; cin >> n;
    string s1;
    std::getline(std::cin, s1);
    for(int i = 0; i < n; ++i) {
        cout << "Enter " << i + 1 << " set: ";
        std::getline(std::cin, s1);
        vector<string> s = split(s1);
        if(!f) {
            cout << "Invalid set, you have repetitive digits or you have smt another digit";
            return 1;
        }
        v.pb(s);
    }
    
    
    
    cout << "Enter count of threads: ";
    int cnt_threads; cin >> cnt_threads;
    cnt_threads = cnt_threads > n ? n : cnt_threads;
    if(cnt_threads <= 0) {
        cout << "Invalid count of threads" << endl;
        return 1;
    }
    
    vector<string> v1 = v[0];
    ans = v[0];
    vector<string> v2;
    
    thread t1([&v1, &n]() {v1 = solve(0, n / 2);});
    thread t2([&v2, &n]() {v2 = solve(n / 2, n);});
    t1.join();
    t2.join();
    ans = v1 * v2;
    
    cout << "{ ";
    for(int i = 0; i < ans.size(); ++i) {
        cout << "(" << ans[i] << ")" << ((i == ans.size() - 1 )? " " : ",");
    }
    cout << "} " << endl;
    
}












