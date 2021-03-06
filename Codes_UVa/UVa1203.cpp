#include <cstdio>
#include <queue>
using namespace std;

struct Item {
    int qNum, Period, Time;
    
    bool operator < (const Item& b) const {
        return Time > b.Time || (Time==b.Time && qNum>b.qNum);
    } // larger Time -> small priority -> poped later
};

int main() {
    priority_queue<Item> Queue;
    char s[10];
    
    while (scanf("%s", s) && s[0] !='#') {
        Item it;
        scanf("%d%d", &it.qNum, &it.Period);
        it.Time = it.Period;
        Queue.push(it);
    }
    
    int k;
    scanf("%d", &k);
    while (k--) {
        Item r = Queue.top();
        Queue.pop();
        printf("%d\n", r.qNum);
        r.Time += r.Period;
        Queue.push(r);
    }
    return 0;
}