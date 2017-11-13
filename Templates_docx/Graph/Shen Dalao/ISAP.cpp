int source;         // 源点 s
int sink;           // 汇点 t
int p[max_nodes];   // 可增广路上的上一条弧的编号
int num[max_nodes]; // 和 t 的最短距离等于 i 的节点数量
int cur[max_nodes]; // 当前弧下标
int d[max_nodes];   // 残量网络中节点 i 到汇点 t 的最短距离
bool visited[max_nodes];

struct Edge
{
    int from;
    int to;
    int cap;
    int flow;

    Edge(int a, int b, int c,int d):from(a), to(b), cap(c),flow(d) {}
};

int num_nodes; //节点数
int num_edges; //边数
vector<Edge> edges;
vector<int> G[max_nodes]; // 每个节点出发的边编号 正向边

// 预处理, 反向 BFS 构造 d 数组
void bfs()
{
    memset(visited, 0, sizeof(visited));
    queue<int> Q;
    Q.push(sink);
    visited[sink] = 1;
    d[sink] = 0;       		//距离为0
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (iterator_t ix = G[u].begin(); ix != G[u].end(); ++ix) {
            Edge &e = edges[(*ix)^1];        //因为从汇点开始 用反向边
            if (!visited[e.to]) {
                visited[e.to] = true;
                d[e.to] = d[u] + 1;
                Q.push(e.to);
            }
        }
    }
    return；
}

// 找到一条增广路 增广
int augment()
{
    int u = sink, rsd = 0x3f3f3f3f;
    // 从汇点到源点通过 p 追踪增广路径, rsd 为一路上最小的残量
    while (u != source) 
    {
        Edge &e = edges[p[u]];
        rsd = min(rsd, e.cap - e.flow);
        u = edges[p[u]].from;
    }
    u = sink;
    // 从汇点到源点更新流量
    while (u != source) {
        edges[p[u]].flow += rsd;    //正向边+流量 反向边-流量
        edges[p[u]^1].flow -= rsd;
        u = edges[p[u]].from;
    }
    return rsd;
}

int max_flow()
{
    int flow = 0;
    bfs();
    memset(num, 0, sizeof(num));
    for (int i = 0; i < num_nodes; i++) 
    	num[d[i]]++;  					//和t距离为i的节点
    int u = source; 					//当前节点
    memset(cur, 0, sizeof(cur));
    while (d[source] < num_nodes) 		//s到t的距离不能超过点数
    	{
        if (u == sink) 
        {
            flow += augment();
            u = source;
        }
        bool advanced = false;
        for (int i = cur[u]; i < G[u].size(); i++)  
        //当前弧优化 从第cur个点开始做 因为前cur-1个点都已经用干净了
        { 
            Edge& e = edges[G[u][i]];  //正边
            if (e.cap > e.flow && d[u] == d[e.to] + 1) 
            //边上有残量  并且是一条 允许弧
            {
                advanced = true;
                p[e.to] = G[u][i];   //下一个点的 上一条弧
                cur[u] = i;          //更新u点的当前弧到u的第i个点
                u = e.to;
                break;
            }
        }
        if (!advanced)  			
        { 
        	// 当前(过时的)剩余网络下 u不能允许弧连接到t了
        	// retreat 更新分层图
        	// remark: u的邻接边不一定都是允许弧
        	// 所以更新到u邻接边的距离+1是新的剩余网络中的允许弧
            int m = num_nodes-1; //默认u的距离是最大值(从剩余网络中排除)
            for (iterator_t ix = G[u].begin(); ix != G[u].end(); ++ix)
                if (edges[*ix].cap > edges[*ix].flow) 
                    m = min(m, d[edges[*ix].to]);
            if (--num[d[u]] == 0)   // gap 优化
            	break;				// 如果和t距离d[u]的所有点都没了 s和t一定断开了 直接退出 			  
            d[u] = m+1
            num[d[u]]++;
            cur[u] = 0;
            if (u != source)
                u = edges[p[u]].from;  //retreat to 到u的前一个点
        }
    }
    return flow;
}