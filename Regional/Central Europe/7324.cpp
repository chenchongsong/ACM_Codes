#include <cstdio>
#include <cstring>
#define Mod 100
using namespace std;

char s[10010];
int N;
int Cnt[10010];
long long Ans;
int t[10010], num[10010]; //t: hashtable


void Clear()
{
	memset(s,0,sizeof(s));
	memset(Cnt, 0,sizeof(Cnt));
	memset(num,0,sizeof(num));
	N = Ans = 0;
}



void line1(int i)
{
	if (i==1) {printf("....x"); return;}
	if (i==4) {printf("x...x"); return;}
	if (i=='+') {printf("....."); return;}
	//if (num[i]==1)
		printf("xxxxx");
}

void line2(int i)
{
	if (i==1||i==2||i==3||i==7) {printf("....x"); return;}
	if (i==4||i==8||i==9||i==0) {printf("x...x"); return;}
	if (i=='+') {printf("..x.."); return;}
	//if (num[i]==1)
		printf("x....");
}

void line4(int i)
{
	if (i==1||i==7) {printf("....x"); return;}
	if (i==0) {printf("x...x"); return;}
	printf("xxxxx");
}

void line5(int i)
{
	if (i==2) {printf("x...."); return;}
	if (i==6||i==8||i==0) {printf("x...x"); return;}
	if (i=='+') {printf("..x.."); return;}
	//if (num[i]==1)
		printf("....x");
}

void line7(int i)
{
	if (i==1||i==4||i==7) {printf("....x"); return;}
	//if (i==4) {printf("x...x"); return;}
	if (i=='+') {printf("....."); return;}
	//if (num[i]==1)
		printf("xxxxx");
}



void PRINT()
{
	int tmp = 0;
	while (Ans)
	{
		
		num[++tmp] = (int) (Ans%10LL) ;
		Ans /=10LL;
		//printf("Ans== %d\n", Ans);
	}

	for (int line =1;line<=7;line++)
		for (int i=tmp;i>=1;i--)
		{
			if (line==1) line1(num[i]);
			if (line==2) line2(num[i]);
			if (line==3) line2(num[i]);
			if (line==4) line4(num[i]);
			if (line==5) line5(num[i]);
			if (line==6) line5(num[i]);
			if (line==7) line7(num[i]);	


			if (i!=1) printf(".");
			else puts("");
		}
}


int main()
{
	//scanf("%d", &N);
	t[33] = 1;
	t[8] = 2;
	t[13] = 3;
	t[69] = 4;
	t[73] = 5;
	t[1] = 6;
	t[93] = 7;
	t[52] = '+';
	t[45] = 8;
	t[17] = 9;
	t[9] = 0;



	while (scanf("%s", s)!= EOF)
	{
		N = (strlen(s)+1) / 6;
		
		for (int Line = 1;Line <= 6;Line ++)
		{
			for (int i=1;i<=N;i++)
			{
				for (int j=0;j<=4;j++)
				{
					Cnt[i] = (Cnt[i] * 2) % Mod + (s[(i-1)*6 + j] == 'x');
					//Cnt[i] = (Cnt[i] + (s[i-1]=='x')
				}
			}
			scanf("%s", s);
		}
	int pos = 0;
	long long v1 = 0, v2 = 0;
	for (int i=1;i<=N;i++)
		{
			//printf("%d---%d\n", i, Cnt[i]);
			num[i] = t[Cnt[i]];
			if (num[i] == '+') pos = i;
		}
	for (int i=1;i<pos;i++)
	{
		v1 = v1*10LL + (long long)num[i];
	}
	for (int i=pos+1;i<=N;i++)
		v2 = v2*10LL + (long long)num[i];
	Ans = v1+v2;
	//printf("%lld\n", v1+v2);
	PRINT();


	Clear();

	}
	return 0;

}