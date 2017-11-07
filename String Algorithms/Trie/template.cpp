#include <cstring>
#include <cstdio>

const int maxnode = 4000010;
const int sigma_size = 26;
struct Trie {   
    int ch[maxnode][sigma_size];
    int sz, val[maxnode];
    void clear(){sz=0;memset(ch[0],0,sizeof(ch[0]));}
    // 一开始只有一个根节点0
    // 点的编号: 0 ~ sz
    int idx(char c){return c-'a';}  
    void insert(char *s, int v) {
        int u = 0, n = strlen(s);  
        for(int i=0;i<n;i++) {  
            int id = idx(s[i]);  
            if(!ch[u][id]) {
                ++sz; 
                memset(ch[sz],0,sizeof(ch[sz]));
                val[sz]=0;
                ch[u][id]=sz;
            }
            u = ch[u][id];  
        }
        val[u] += v;  
    } 
    int search(char *s) {  
        int u = 0, n = strlen(s);  
        for(int i=0;i<n;i++) {  
            int id = idx(s[i]);
            if(ch[u][id]==0)
                return 0;
            u = ch[u][id];
        }
        return val[u];
    }
};
Trie trie;

char s[4000010];
int main() {
    while (true) {
        gets(s);
        if (strlen(s)==0) break;
        trie.insert(s, 1);
    }
    puts("OK--- now query starts --- ");
    while (scanf("%s", s)) {
        printf("%d\n", trie.search(s));
    }
    return 0;
}