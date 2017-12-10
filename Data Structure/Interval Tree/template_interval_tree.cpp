int n, m; // index 1~n 一共m次操作
int op, qL, qR, v; // 每次update或query前 都必须clarify
int _sum, _min, _max; // 每次query前都要init

const int maxnode = 1<<17;
const int INF = 0x3f3f3f3f;

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
		if(setv[o] >= 0){
			minv[o] = maxv[o] = setv[o];
			sumv[o] = setv[o] * (R-L+1);
		}
		if(addv[o]){
			minv[o] += addv[o];
			maxv[o] += addv[o];
			sumv[o] += addv[o] * (R-L+1);
		}
	}
	void pushdown(int o){
		int lc = o*2, rc = o*2+1;
		if(setv[o] >= 0){
			setv[lc] = setv[rc] = setv[o];
			addv[lc] = addv[rc] = 0;
			setv[o] = -1;
		}
		if(addv[o]){
			addv[lc] += addv[o]; /// wrong answer
			addv[rc] += addv[o]; /// wrong answer
			addv[o] = 0;
		}
	}
	void update(int o, int L, int R){
		int lc = o*2, rc = o*2+1;
		if(qL <= L && qR >= R){
			if(op == 2) { // set
				setv[o] = v;
				addv[o] = 0;
			} // op == 1 : Add
			else{
				addv[o] += v;
			}
		}
		else{
			pushdown(o);
			int M = L + (R-L)/2;
			if(qL <= M) update(lc, L, M);
			else maintain(lc, L, M);
			if(qR > M) update(rc, M+1, R);
			else maintain(rc, M+1, R);
		}
		maintain(o, L, R);
	}
	void query(int o, int L, int R, int add){
		if(setv[o] >= 0){
			int v = setv[o] + addv[o] + add;
			_sum += v * (min(R, qR)-max(L, qL)+1);
			_max = max(_max, v);
			_min = min(_min, v);
		}
		else if(qL <= L && qR >= R){
			_sum += sumv[o] + add*(R-L+1);
			_max = max(_max, maxv[o]+add);
			_min = min(_min, minv[o]+add);
		}
		else{
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