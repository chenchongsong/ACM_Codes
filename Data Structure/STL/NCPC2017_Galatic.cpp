#include <cstdio>
#include <map>
#include <set>
#include <iostream>
#define maxn 200005
using namespace std;

int num[maxn], p[maxn];

struct State {
    int id, num, p; // team index
    bool operator < (const State& rhs) const {
        return num < rhs.num || (num==rhs.num && p > rhs.p)
        || (num==rhs.num && p==rhs.p && id > rhs.id); // important!!!
    }
};
multiset<State> s;

bool better_than(int t1, int t2) { // whether t1 better than t2
    if (num[t1] != num[t2])
        return num[t1] > num[t2];
    return p[t1] < p[t2];
}

bool equal(int t1, int t2) {
    return num[t1]==num[t2] && p[t1]==p[t2];
}

int main() {
    int n, m;
    cin >> n >> m;

    for (int op=1; op <= m; op++) {
        int team, tmpp;
        cin >> team >> tmpp;

        auto it = s.find((State){team, num[team], p[team]});
        if (it != s.end())
            s.erase(it);

        num[team]++;
        p[team] += tmpp;

        if (team != 1) {
            if (better_than(team, 1))
                s.insert((State){team, num[team], p[team]});
            cout << s.size()+1 << endl;
            continue;
        }

        // team1 solved a question
        int set_front = s.begin()->id;
        while (!s.empty() && (better_than(1, set_front) || equal(1, set_front))) {
            s.erase(s.begin());
            set_front = s.begin()->id;
        }
        cout << s.size()+1 << endl;
    }
    return 0;
}