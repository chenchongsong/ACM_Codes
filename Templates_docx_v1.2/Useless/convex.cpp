const double eps=1e-10;
const double PI=acos(-1);
struct Point{  double x, y;
    Point(double x=0, double y=0):x(x), y(y){}
} p[maxn], ch[maxn];
typedef Point Vector;
Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (Vector A, Vector B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }
Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }
int dcmp(double x) {
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}
bool operator == (const Point& a, const Point& b)
{ return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0; }
bool operator < (const Point& a, const Point& b)
{ return a.x < b.x || (a.x == b.x && a.y < b.y); }
double cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
double torad(double deg) { return deg / 180 * PI; }
double PolygonArea(Point* p, int n){
    double area=0;
    for(int i=1; i<n-1; i++)
        area+=cross(p[i]-p[0], p[i+1]-p[0]);
    return area/2;
}
int convexhull(Point* p, int n, Point* ch) {
    sort(p, p+n);
    int m = 0;
    for(int i = 0; i < n; i++) {
        while(m > 1 && cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2; i >= 0; i--) {
        while(m > k && cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
        ch[m++] = p[i];
    }
    if(n > 1) m--;
    return m;
}
Vector Rotate(Vector A, double rad){ // 这里rad是逆时针旋转的角度
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}
// int main()
Point o(tmpx, tmpy);
p[point_cnt++]=o; ... ...
int m=convexhull(p, point_cnt, ch);
double convex_area=PolygonArea(ch, m);
// Rotate vector(10,10) clockwise by 90 degree
// new_o = o + Rotate(Vector(10.0,10.0),-torad(90.0));