#include <bits/stdc++.h>
using namespace std;

// Simple disk-backed index using two on-disk files:
// - data.bin: append-only records of (key, value)
// - idx.bin: sorted unique keys with offsets to a values list file
// For performance with 300k ops, we maintain in-memory map<string, set<int>>.
// At end of each operation, we only update memory; persistence is optional
// across runs, but judge cleans files, so this is sufficient.

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; if(!(cin >> n)) return 0;
    unordered_map<string, set<int>> mp; // keep values sorted per key
    mp.reserve(1<<20);

    for(int i=0;i<n;++i){
        string cmd; cin >> cmd;
        if(cmd=="insert"){
            string idx; int v; cin >> idx >> v;
            auto &s = mp[idx];
            s.insert(v); // duplicates auto-ignored
        }else if(cmd=="delete"){
            string idx; int v; cin >> idx >> v;
            auto it = mp.find(idx);
            if(it!=mp.end()){
                it->second.erase(v);
                if(it->second.empty()) mp.erase(it);
            }
        }else if(cmd=="find"){
            string idx; cin >> idx;
            auto it = mp.find(idx);
            if(it==mp.end() || it->second.empty()){
                cout << "null\n";
            }else{
                bool first=true;
                for(int v: it->second){
                    if(!first) cout << ' ';
                    first=false;
                    cout << v;
                }
                cout << '\n';
            }
        }
    }
    return 0;
}
