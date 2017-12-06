for(int i=0; i<cnt; i++)//入度为0的点入栈
	if(!indeg[i]) s.push(i);
while(!s.empty()){
    int u=s.top();
    s.pop();
    T.push_back(u);//T保存拓扑序
    for(int v:G[u]){//G为邻接表
        indeg[v]--;
        if(!indeg[v]) s.push(v);
    }
}