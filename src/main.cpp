#include <bits/stdc++.h>
using namespace std;

// Persistent append-only log to support cross-run state.
// In-memory: unordered_map<string, set<int>> for sorted values.

static void load_log(unordered_map<string, set<int>> &mp, const string &path){
    ifstream in(path);
    if(!in) return;
    string op, key; int val;
    while(in >> op >> key >> val){
        if(op=="I") mp[key].insert(val);
        else if(op=="D"){
            auto it = mp.find(key);
            if(it!=mp.end()){
                it->second.erase(val);
                if(it->second.empty()) mp.erase(it);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const string log_path = "bpt_store.log";

    unordered_map<string, set<int>> mp;
    mp.reserve(1<<20);
    load_log(mp, log_path);
    ofstream out(log_path, ios::app);

    int n; if(!(cin >> n)) return 0;
    for(int i=0;i<n;++i){
        string cmd; cin >> cmd;
        if(cmd=="insert"){
            string idx; int v; cin >> idx >> v;
            auto &s = mp[idx];
            if(s.insert(v).second){
                out << "I " << idx << ' ' << v << '\n';
            }
        }else if(cmd=="delete"){
            string idx; int v; cin >> idx >> v;
            auto it = mp.find(idx);
            if(it!=mp.end()){
                if(it->second.erase(v)){
                    out << "D " << idx << ' ' << v << '\n';
                    if(it->second.empty()) mp.erase(it);
                }
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
