#include <iostream>
#include <cmath>
using namespace std;
int T;
double p1[3][3], p2[3][4];
double ux, uy, uz;
void Solve(){
	int n=3; 
    int i,j,k,r;
    for (int i=0;i<n;i++)
    {
        r=i;
        for (j=i+1;j<n;j++)
        {
            if ( fabs(p2[j][i]) > fabs(p2[r][i]) ) r=j;
        }

            if (r!=i) for (j=0;j<=n;j++)
            {
                double Tmp = p2[r][j];
                p2[r][j] = p2[i][j];
                p2[i][j] = Tmp;

            }

        for (int k=i+1;k<n;k++)
        {
            double f = p2[k][i]/p2[i][i];
            for (int j=i;j<=n;j++)
                p2[k][j]-=f*p2[i][j];
        }
    }

        for (int i=n-1;i>=0;i--)
        {

            for (j=i+1;j<n;j++)
                p2[i][n]-=p2[j][n]*p2[i][j];
            p2[i][n]/=p2[i][i];
        }
    ux = p2[0][3];
    uy = p2[1][3];
    uz = p2[2][3];

}



int main(){
    cin>>T;
    while(T--){
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++)
                cin>>p1[i][j];
        }
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++)
                cin>>p2[i][j];
                
        }
		Solve();

        double A=ux, B=uy, C=uz, D=ux*p2[0][0]+uy*p2[1][0]+uz*p2[2][0];
        double t=(D-A*p1[0][0]-B*p1[0][1]-C*p1[0][2])/(A*(p1[1][0]-p1[0][0])+B*(p1[1][1]-p1[0][1])+C*(p1[1][2]-p1[0][2]));
        if(t>0&&t<1){
            cout<<"YES"<<endl;
            continue;
        }
        t=(D-A*p1[1][0]-B*p1[1][1]-C*p1[1][2])/(A*(p1[2][0]-p1[1][0])+B*(p1[2][1]-p1[1][1])+C*(p1[2][2]-p1[1][2]));
        if(t>0&&t<1){
            cout<<"YES"<<endl;
            continue;
        }
        t=(D-A*p1[2][0]-B*p1[2][1]-C*p1[2][2])/(A*(p1[0][0]-p1[2][0])+B*(p1[0][1]-p1[2][1])+C*(p1[0][2]-p1[2][2]));
        if(t>0&&t<1){
            cout<<"YES"<<endl;
            continue;
        }
        cout<<"NO"<<endl;
    }
}
