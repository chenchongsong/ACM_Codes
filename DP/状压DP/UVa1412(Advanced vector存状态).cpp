#include <cstdio>  
#include <cstring>  
#include <vector>  
#include <map>  
using namespace std;  
  
const double INF = 1e30;  
const int maxn = 8;  
const int maxm = 100 + 5;  
const int maxstate = 15000;
//由隔板法 maxstate < 2^16
  
int m, n, s[maxn], k[maxn], kk;  
double c, price[maxn][maxm];  
char name[maxn][10];  
  
double d[maxm][maxstate];  
int opt[maxm][maxstate], pre[maxm][maxstate];
  
int buy_next[maxstate][maxn], sell_next[maxstate][maxn];  
vector <vector<int> > states;  
map <vector<int>, int> ID;  //vector<int> --> int
  
void dfs(int stock, vector<int>& lots, int totlot)
//lots前面加& 表示pass by reference 可以修改
{  
    if(stock == n)
    {
        ID[lots] = states.size();
        states.push_back(lots);
    }
    else for(int i = 0; i <= k[stock] && totlot + i <= kk; i++)
    // 枚举编号为stock股票的持有数（为i） 总股票持有数不得超过kk
    {
        lots[stock] = i;
        dfs(stock+1, lots, totlot + i);
    }
}
  
void init()
{  
    vector<int> lots(n); //大小为n的vector
    states.clear();
    ID.clear();
    dfs(0, lots, 0);
    for(int s = 0; s < states.size(); s++)
    {
        int totlot = 0;
        for(int i = 0; i < n; i++) totlot += states[s][i];
        for(int i = 0; i < n; i++)
        {
            buy_next[s][i] = sell_next[s][i] = -1;
            // buy_next记 编号为s的原状态 买入一手i后 得到的新状态的编号
            if(states[s][i] < k[i] && totlot < kk) //buy
            {
                vector<int> newstate = states[s];
                newstate[i]++;
                buy_next[s][i] = ID[newstate];
            }
            if(states[s][i] > 0) //sell
            {
                vector<int> newstate = states[s];
                newstate[i]--;
                sell_next[s][i] = ID[newstate];
            }
        }
    }
}
  
void update(int day, int s, int s2, double v, int o)
{  
    if(v > d[day+1][s2]) //向后一天转移
    {
        d[day+1][s2] = v;
        opt[day+1][s2] = o;
        pre[day+1][s2] = s;
    }
}
 
double dp()
{
    for(int day = 0; day <= m; day++)
        for(int s = 0; s < states.size(); s++)
            d[day][s] = -INF;

    d[0][0] = c;
    for(int day = 0; day < m; day++)
        for(int s = 0; s < states.size(); s++)
        {  
            double v = d[day][s];
            if(v < -1) continue; //当前状态不成立

            update(day, s, s, v, 0); // HOLD 什么事情不都做 
            for(int i = 0; i < n; i++)
            {  
                if(buy_next[s][i] >= 0 && v >= price[i][day] - 1e-3)
                update(day, s, buy_next[s][i], v - price[i][day], i+1); // BUY  
                if(sell_next[s][i] >= 0)  
                update(day, s, sell_next[s][i], v + price[i][day], -i-1); // SELL  
            }  
        }  
    return d[m][0];  
}  
  
void print_ans(int day, int s)
{  
    if(day == 0) return;
    print_ans(day-1, pre[day][s]);
    if(opt[day][s] == 0)
        printf("HOLD\n");  
    else
        if(opt[day][s] > 0)
            printf("BUY %s\n", name[opt[day][s]-1]);
        else
            printf("SELL %s\n", name[-opt[day][s]-1]);
}  
  
int main()
{  
    int kase = 0;
    while(scanf("%lf%d%d%d", &c, &m, &n, &kk) == 4)
    {
        if(kase++ > 0) printf("\n");
        for (int i = 0; i < n; i++)
        {
            scanf("%s%d%d", name[i], &s[i], &k[i]);
            for (int j = 0; j < m; j++)
            {
                scanf("%lf", &price[i][j]);
                price[i][j] *= s[i];
            }  
        }  
        init();  
        double ans = dp();  
        printf("%.2lf\n", ans);  
        print_ans(m, 0);  
    }  
    return 0;  
}  