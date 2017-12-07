double simpson(double a, double b) {
	double c = (a + b) / 2.0;
	return (F(a)+4*F(c)+F(b)) * (b-a) / 6.0;
	// 这里F为自定义函数
}
//given A as the simpson Value for the whole interval [a,b]
double asr(double a, double b, double eps, double A) {
	double c = (a + b) / 2.0;
	double L = simpson(a, c), R = simpson(c, b);
	if  (fabs(L+R-A) <= 15*eps)
		return L + R + (L+R-A)/15.0;
	return asr(a, c, eps/2, L) + asr(c, b, eps/2, R);
}
double asr(double a, double b, double eps)//接口
{ return asr(a, b, eps, simpson(a, b)); }
// int main(): 调用asr(left, right, 1e-5)
// 得到F(x) 在[left, right]上的积分 eps也可改为1e-6