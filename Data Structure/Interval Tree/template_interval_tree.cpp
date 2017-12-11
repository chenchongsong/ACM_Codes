int n, m; // index 1~n 一共m次操作
int op, qL, qR, v; // 每次update或query前 都必须clarify
// 对于set: v >= 0 !!!
int _sum, _min, _max; // 每次query前都要init

const int maxnode = 1<<17;
const int INF = 0x3f3f3f3f;

// 只要set不要add时 所有"add""addv[]"删去即可 (或视作0)
struct IntervalTree{
	int addv[maxnode*4],setv[maxnode*4];
	int sumv[maxnode*4],minv[maxnode*4],maxv[maxnode*4];

	void maintain(int o, int L, int R){
		int lc = o*2, rc = o*2+1;
		if(L < R){
			sumv[o] = sumv[lc] + sumv[rc];
			maxv[o] = max(maxv[lc], maxv[rc]);
			minv[o] = min(minv[lc], minv[rc]);
		}
		if(setv[o] >= 0){ //only when set included
			minv[o] = maxv[o] = setv[o];
			sumv[o] = setv[o] * (R-L+1);
		}
		if(addv[o]){
			minv[o] += addv[o];
			maxv[o] += addv[o];
			sumv[o] += addv[o] * (R-L+1);
		}
	}
	void pushdown(int o){ //only when set included
		int lc = o*2, rc = o*2+1;
		if(setv[o] >= 0){
			setv[lc] = setv[rc] = setv[o];
			addv[lc] = addv[rc] = 0;
			setv[o] = -1;
		}
		if(addv[o]){
			addv[lc] += addv[o];
			addv[rc] += addv[o];
			addv[o] = 0;
		}
	}
	void update(int o, int L, int R){
		int lc = o*2, rc = o*2+1;
		if(qL <= L && qR >= R){
			if(op == 2) { // set
				setv[o] = v;
				addv[o] = 0;
			} 
			else { //op==1 :Add
				addv[o] += v;
			}
		}
		else{
			pushdown(o); //only when set included
			int M = L + (R-L)/2;
			if(qL <= M) update(lc, L, M);
			else maintain(lc, L, M); //only when set included
			if(qR > M) update(rc, M+1, R);
			else maintain(rc, M+1, R); //only when set included
		}
		maintain(o, L, R);
	}
	void query(int o, int L, int R, int add){ //只需要set时可以删去第四个参数
		if(setv[o] >= 0){ // only when set included
			int v = setv[o] + addv[o] + add;
			_sum += v * (min(R, qR)-max(L, qL)+1);
			_max = max(_max, v);
			_min = min(_min, v);
		}
		else if(qL <= L && qR >= R){ //当前区间完全包含于询问中
			_sum += sumv[o] + add*(R-L+1);
			_max = max(_max, maxv[o]+add);
			_min = min(_min, minv[o]+add);
		}
		else{ // 递归统计 累加参数add
			int lc = o*2, rc = o*2+1;
			int M = L + (R-L)/2;
			if(qL <= M) query(lc, L, M, add+addv[o]);
			if(qR > M) query(rc, M+1, R, add+addv[o]);
		}
	} 
} tree;

int main(){
	// 初始化必不可少
	memset(&tree, 0, sizeof(tree));
	memset(tree.setv,-1,sizeof(tree.setv));
	tree.setv[1] = 0;

	for (int i=1; i<=n; i++) { //赋初始值
		scanf("%d", &v);
		qL = qR = i;
		op = 1;
		tree.update(1, 1, n);
	}
	// update的用法
	cin >> s;
	if (s == "add") {
		scanf("%d%d%d",&qL,&qR,&v);
		op = 1;
		tree.update(1, 1, n);
	}
	if (s == "set") {
		scanf("%d%d%d",&qL,&qR,&v);
		op = 2;
		tree.update(1, 1, n);
	}
	// query的用法
	if (s == "sum") {
		scanf("%d%d",&qL,&qR);
		_sum = 0; _max = -INF; _min = INF;
		tree.query(1, 1, n, 0);
		printf("%d\n", _sum);
	}
}