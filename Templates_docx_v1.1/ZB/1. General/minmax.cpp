struct State{//状态
	int score;//当前状态的打分, 对大分玩家越有利分越高
	inline bool isFinal();//判断是否为终局的函数
	inline void expand(int player, vector<State>& children);//拓展子节点的函数
};
int alphabeta(State& s, int player, int alpha, int beta){//0是大分玩家, 1是小分玩家
	if(s.isFinal()) return s.score;
	vector<State> children;
	s.expand(player, children);//生成儿子
	for(auto child:children){
		int v=alphabeta(child, player^1, alpha, beta);//对儿子状态打分
		!player?alpha=max(alpha, v):beta=min(beta, v);//选取最有利的情况
		if(beta<=alpha) break;//alpha-beta剪枝
	}
	return !player?alpha:beta;
}
