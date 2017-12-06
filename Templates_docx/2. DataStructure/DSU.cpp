int p[maxn], Rank[maxn];//p记录祖先, Rank记录秩
void init(int n){
	for(int i=1; i<=n; i++)
		p[i]=i, Rank[i]=0;
}
int Find(int x){//路径压缩找祖先
	return p[x]==x?x:p[x]=Find(p[x]);
}
void Union(int x, int y){
	int xr=Find(x), yr=Find(y);
	if(xr==yr) return;//如果祖先相同直接退出
	if(Rank[xr]>Rank[yr]) p[yr]=xr;//启发式合并
	else{
		p[xr]=yr;
		if(Rank[xr]==Rank[yr]) Rank[yr]++;
	}
}