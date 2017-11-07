// #include <bits/stdc++.h>
#include <string>
#include <cstdio>
#include <iostream>
using namespace std;
int main(){
    string T, P;
    int ans[100000];
    while(getline(cin, P)){
        getline(cin, T);
        int tot = 0;
        int match_pos = T.find(P, 0);
        while(match_pos != -1){
            ans[++tot] = match_pos;
            match_pos = T.find(P, match_pos+1);
        }
        for(int i=1;i<=tot;i++){
            printf("%d%c",ans[i],i==tot?'\n':' ');
        }
    }
    return 0;
} 