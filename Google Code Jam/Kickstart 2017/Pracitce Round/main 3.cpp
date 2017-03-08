#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

int char_occur(string s) {
    int count[255];
    for (int i = 0; i < 255; i++)
        count[i] = 0; // Assign the counter variable to Zero

    int len = s.length();
    for (int i = 0; i < len; i++)
        if (s[i] >= 'A' && s[i]<='Z')
            count[s[i]]++; // Add the counter for the corresponding ASCII character

    int uniqueCount = 0;
    for (int i = 0; i < 255; i++) {
        if (count[i] > 0) {
            uniqueCount++; // Holds the unique number of characters
        }
    }
    return uniqueCount;
}

int main() {
    int t;

    freopen("Desktop/Google Kickstart/A-large-practice.in","r",stdin);
    freopen("Desktop/Google Kickstart/ans.out","w",stdout);

    cin>>t;
    for (int n = 1; n <= t; ++n) {
        int no;
        string* names;
        string temp;
        int* dis;
        int in=0;
        int fl=0;

        cin>>no;
        getline(cin, temp);
        names = new string[no];
        dis = new int[no];
        for (int i = 0; i <= no-1; ++i) {
            getline(cin,names[i]);
        }


        for (int j = 0; j < no; ++j) {
            dis[j]=char_occur(names[j]);
        }

        int max = dis[0];
        for (int k = 1; k < no; ++k) {
            if (dis[k]>max){
                max = dis[k];
                in = k;
            }
        }

        int count = 0;
        cout<<"Case #"<<n<<": ";
        for (int l = 0; l < no; ++l) {
            if (dis[l]==max){
                count++;
            }
        }
        if (count>1){
            temp = names[in];
            for (int i = 0; i < no; ++i) {
                if (dis[i]==max && names[i]<temp){
                    temp = names[i];
                    fl = 1;
                }
            }
            if (fl==0){
                cout<<names[in]<<endl;
            }
            else{
                cout<<temp<<endl;
            }
        }
        else{
            cout<<names[in]<<endl;
        }
        delete[](names);
        delete[](dis);
    }
    return 0;
}
